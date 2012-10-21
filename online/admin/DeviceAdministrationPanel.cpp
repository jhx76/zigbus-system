#include "DeviceAdministrationPanel.h"
#include "ui_DeviceAdministrationPanel.h"


DeviceAdministrationPanel::DeviceAdministrationPanel(QList<Module>* moduleList, QueryBean *queryBean, QWidget *parent)
    : QWidget(parent), ui(new Ui::DeviceAdministrationPanel)
{
    ui->setupUi(this);
    ui->newModuleTool->setIcon(QIcon("./images/module.png"));
    ui->newDeviceTool->setIcon(QIcon("./images/device.png"));
    ui->deleteSelectedTool->setIcon(QIcon("./images/delete.png"));
    ui->modifySelectedTool->setIcon(QIcon("./images/modify.png"));


    displayedWidget = NULL;
    this->moduleList = moduleList;
    this->queryBean = queryBean;
    model = new QStandardItemModel();
    try {
        initialize();
    }
    catch(const QString& s) {
        qDebug() << s;
    }
    connect(ui->modifySelectedTool, SIGNAL(clicked()), this, SLOT(onModifySelectedToolClick()));
    connect(ui->deleteSelectedTool, SIGNAL(clicked()), this, SLOT(onDeleteSelectedToolClick()));
    connect(ui->newDeviceTool, SIGNAL(clicked()), this, SLOT(onNewDeviceToolClick()));
    connect(ui->newModuleTool, SIGNAL(clicked()), this, SLOT(onNewModuleToolClick()));
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(onItemSelection(QModelIndex)));
}

DeviceAdministrationPanel::~DeviceAdministrationPanel()
{
    delete ui;
    delete model;
    queryBean = NULL;
    if(displayedWidget != NULL) {
        displayedWidget->setVisible(false);
        delete displayedWidget;
    }
}

void DeviceAdministrationPanel::initialize() {
    if(this->moduleList == NULL)
        throw QString("exception: NullPointerException");
    model->clear();

    for(int i = 0; i < moduleList->count(); i++) {
        Module* tmpModule = &(moduleList->operator [](i));
        ModuleTreeItem* moduleItem = new ModuleTreeItem(tmpModule);
        model->appendRow(moduleItem);
        for(int i2 = 0; i2 < tmpModule->deviceCount(); i2++) {
            try {
                Device* device = &(tmpModule->elementAt(i2));
                if(device == NULL)
                    throw QString("exception: NullPointerException");
                DeviceTreeItem* deviceItem = new DeviceTreeItem(device);
                moduleItem->appendRow(deviceItem);
            }
            catch(const QString& s) {
                qDebug() << s;
                continue;
            }
        }
    }
    ui->treeView->setModel(model);
}

void DeviceAdministrationPanel::onItemSelection(QModelIndex indexElementSelectionne) {

    try {
        QStandardItem* selectedItem = model->itemFromIndex(indexElementSelectionne);
        if(selectedItem == NULL)
            throw QString("exception: NullPointerException");

        if(ModuleTreeItem* moduleItem = dynamic_cast<ModuleTreeItem*>(selectedItem)) {
            qDebug() << "module Item event";
        }
        else if(DeviceTreeItem* deviceItem = dynamic_cast<DeviceTreeItem*>(selectedItem)) {
            qDebug() << "device item event";
        }
        else {
            ui->modifySelectedTool->setEnabled(false);
            ui->deleteSelectedTool->setEnabled(false);
            throw QString("exception: Unable to convert 'QStandardItem' into our precessing type...");
        }
        ui->modifySelectedTool->setEnabled(true);
        ui->deleteSelectedTool->setEnabled(true);
    }
    catch(const QString& exception) {
        qDebug() << exception;
    }
}

void DeviceAdministrationPanel::onDeleteSelectedToolClick() {
    QMessageBox msgBox;
    msgBox.setText("L'objet va etre supprime ...");
    msgBox.setInformativeText("Continuer ?");
    msgBox.setStandardButtons(QMessageBox::Discard | QMessageBox::Ok);
    int ret = msgBox.exec();

    QStandardItem* selectedItem = NULL;
    ModuleTreeItem* moduleItem = NULL;
    DeviceTreeItem* deviceItem = NULL;

    QMessageBox messageBox2;

    switch(ret) {
    case QMessageBox::Ok:
        selectedItem = model->itemFromIndex(ui->treeView->currentIndex());
        if(moduleItem = dynamic_cast<ModuleTreeItem*>(selectedItem)) {
            if(moduleItem->getPtrModule()->deviceCount() > 0) {
                messageBox2.setText("Le module selectionne contient des appareils...");
                messageBox2.setInformativeText("Vous devez supprimer les éléments enfants avant de supprimer le module !");
                messageBox2.setStandardButtons(QMessageBox::Discard);
                messageBox2.exec();
            }
            else {
                try {
                    if(queryBean->deleteModule(*(moduleItem->getPtrModule())) > 0) {

                        messageBox2.setText("L'objet a bien ete supprime !");
                        messageBox2.setStandardButtons(QMessageBox::Ok);
                        messageBox2.exec();
                        initialize();
                    }
                    else {
                        messageBox2.setText("Une erreur est survenue, l'objet n'a pas ete supprime !");
                        messageBox2.setStandardButtons(QMessageBox::Ok);
                        messageBox2.exec();
                    }
                }
                catch(const error::SqlException& exception) {
                    qDebug() << exception.toString();
                }
            }
        }
        else if(deviceItem = dynamic_cast<DeviceTreeItem*>(selectedItem)) {
            try {
                if(queryBean->deleteDevice(*(deviceItem->getPtrDevice())) > 0) {
                    Module* module = deviceItem->getPtrDevice()->getPtrModule();
                    for(int i = 0; i < module->deviceCount(); i++) {
                        if(module->elementAt(i) == *(deviceItem->getPtrDevice())) {
                            module->removeAt(i);
                        }
                    }
                    messageBox2.setText("L'objet a bien ete supprime");
                    messageBox2.setStandardButtons(QMessageBox::Ok);
                    messageBox2.exec();
                    initialize();
                }
                else {
                    messageBox2.setText("Une erreur est survenue, l'objet n'a pas ete supprime !");
                    messageBox2.setStandardButtons(QMessageBox::Ok);
                    messageBox2.exec();
                }
            }
            catch(const error::SqlException& exception) {
                qDebug() << exception.toString();
            }
        }
        else {
            qDebug() << "error: system found an error that shouldn't be reached normally...";
        }
        break;
    case QMessageBox::Cancel:
        //Nothing to do
        break;
    default:
      ;  //should never be reached
    };
}

void DeviceAdministrationPanel::onModifySelectedToolClick() {
    try {

        QStandardItem* selectedItem = model->itemFromIndex(ui->treeView->currentIndex());
        if(selectedItem == NULL)
            throw QString("exception: NullPointerException");


        if(ModuleTreeItem* moduleItem = dynamic_cast<ModuleTreeItem*>(selectedItem)) {
            if(displayedWidget != NULL) {
                displayedWidget->setVisible(false);
                delete displayedWidget;
                displayedWidget = NULL;
            }
            ModuleEditionPanel* editionPanel = new ModuleEditionPanel(moduleItem->getPtrModule(), queryBean);
            displayedWidget = (QWidget*)editionPanel;
            ui->widgetLayout->addWidget(displayedWidget);
            displayedWidget->setVisible(true);
            connect(editionPanel, SIGNAL(um_panel_closed()), this, SLOT(panelIsClosed()));
            connect(editionPanel, SIGNAL(um_refresh()), this, SLOT(initialize()));
        }
        else if(DeviceTreeItem* deviceItem = dynamic_cast<DeviceTreeItem*>(selectedItem)) {
            if(displayedWidget != NULL) {
                displayedWidget->setVisible(false);
                delete displayedWidget;
                displayedWidget = NULL;
            }
            DeviceEditionPanel* editionPanel = new DeviceEditionPanel(deviceItem->getPtrDevice(), moduleList, queryBean);
            displayedWidget = (QWidget*) editionPanel;
            ui->widgetLayout->addWidget(displayedWidget);
            displayedWidget->setVisible(true);
            connect(editionPanel, SIGNAL(um_refresh()), this, SLOT(initialize()));
            connect(editionPanel, SIGNAL(um_panel_closed()), this, SLOT(panelIsClosed()));
        }
        else {
            throw QString("exception: Unable to convert 'QStandardItem' into our precessing type...");
        }
    }
    catch(const QString& exception) {
        qDebug() << exception;
    }
}

void DeviceAdministrationPanel::onNewDeviceToolClick() {
    DeviceCreationDialog* dialog = new DeviceCreationDialog(moduleList, queryBean);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setVisible(true);
    connect(dialog, SIGNAL(accepted()), this, SLOT(initialize()));
}

void DeviceAdministrationPanel::onNewModuleToolClick() {

}







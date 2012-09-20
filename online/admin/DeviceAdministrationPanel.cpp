#include "DeviceAdministrationPanel.h"
#include "ui_DeviceAdministrationPanel.h"

DeviceAdministrationPanel::DeviceAdministrationPanel(QList<Module>* moduleList, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceAdministrationPanel)
{
    ui->setupUi(this);
    this->moduleList = moduleList;
    model = new QStandardItemModel();
    try {
        initialize();
    }
    catch(const QString& s) {
        qDebug() << s;
    }
}

DeviceAdministrationPanel::~DeviceAdministrationPanel()
{
    delete ui;
    delete model;
}

void DeviceAdministrationPanel::initialize() {
    if(this->moduleList == NULL)
        throw QString("err null pointer");
    for(int i = 0; i < moduleList->count(); i++) {
        Module* tmpModule = &(moduleList->operator [](i));
        ModuleTreeItem* moduleItem = new ModuleTreeItem(tmpModule);
        model->appendRow(moduleItem);

        for(int i = 0; i < tmpModule->deviceCount(); i++) {
            try {
                Device* device = &(tmpModule->elementAt(i));
                if(device == NULL)
                    throw QString("err null pointer");

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

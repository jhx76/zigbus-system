#include "ModuleEditionPanel.h"
#include "ui_ModuleEditionPanel.h"

ModuleEditionPanel::ModuleEditionPanel(QWidget *parent) : QWidget(parent), ui(new Ui::ModuleEditionPanel)
{
    ui->setupUi(this);
    module = NULL;
    queryBean = NULL;
}

ModuleEditionPanel::ModuleEditionPanel(Module *ptrModule, QueryBean* queryBean, QWidget *parent)
    : QWidget(parent), ui(new Ui::ModuleEditionPanel)
{
    ui->setupUi(this);
    module = ptrModule;
    tmpModule = *ptrModule;
    this->queryBean = queryBean;
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButtonClick()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(onSaveButtonClick()));
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(onQuitButtonClick()));
    try {
        initialize();
    }
    catch(const error::SqlException &exception) {
        qDebug() << exception.toString();
    }
}

ModuleEditionPanel::~ModuleEditionPanel()
{
    delete ui;
    module = NULL; //On ne delete pas l'object car il ne nous appartient pas.
    queryBean = NULL;
}


void ModuleEditionPanel::initialize() {
    this->setAttribute(Qt::WA_DeleteOnClose);
    if(queryBean != NULL) {
        this->zigbusNetworkList = queryBean->getAllZigbusNetworks();
        ui->zigbusNetworkCombo->clear();
        for(int i = 0; i < zigbusNetworkList.count(); i++) {
            ui->zigbusNetworkCombo->addItem(zigbusNetworkList.at(i).getLabel());
            if(zigbusNetworkList.at(i).getLabel() == tmpModule.getZigbusNetworkId())
                ui->zigbusNetworkCombo->setCurrentIndex(i);
        }
    }
    ui->nbPinNumericEdit->setValue(tmpModule.getNumericIOCount());
    ui->nbPinAnalogicEdit->setValue(tmpModule.getAnalogIOCount());
}

void ModuleEditionPanel::onSaveButtonClick() {
    tmpModule.setLabel(ui->moduleIdEdit->text());
    tmpModule.setNumericIOCount(ui->nbPinNumericEdit->value());
    tmpModule.setAnalogIOCount(ui->nbPinAnalogicEdit->value());
    tmpModule.setZigbusNetworkId(ui->zigbusNetworkCombo->currentText());

    queryBean->updateModule(*module, tmpModule);

    module->setAnalogIOCount(tmpModule.getAnalogIOCount());
    module->setNumericIOCount(tmpModule.getNumericIOCount());
    module->setLabel(tmpModule.getLabel());
    module->setZigbusNetworkId(tmpModule.getZigbusNetworkId());
    emit um_refresh();
}

void ModuleEditionPanel::onQuitButtonClick() {
    emit um_panel_closed();
    this->close();
}

void ModuleEditionPanel::onCancelButtonClick() {
    tmpModule = *module;
    initialize();
}

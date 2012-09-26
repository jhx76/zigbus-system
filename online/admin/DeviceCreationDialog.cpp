#include "DeviceCreationDialog.h"
#include "ui_DeviceCreationDialog.h"

DeviceCreationDialog::DeviceCreationDialog(QList<Module> *moduleList, QueryBean* queryBean, QWidget *parent)
    : QDialog(parent), ui(new Ui::DeviceCreationDialog)
{
    ui->setupUi(this);
    this->queryBean = queryBean;
    this->moduleList = moduleList;

    try {
        initialize();
    }
    catch(const error::SqlException& exception) {
        qDebug() << exception.toString();
    }
}

DeviceCreationDialog::~DeviceCreationDialog()
{
    delete ui;
    queryBean = NULL;
}

void DeviceCreationDialog::initialize() {
    locationList = queryBean->getAllLocations();
    hardwareTypeList = queryBean->getAllHardwareTypes();
    symbolicTypeList = queryBean->getAllSymbolicTypes();
    symbolicNetworkList = queryBean->getAllSymbolicNetworks();
    zigbusNetworkList = queryBean->getAllZigbusNetworks();
    for(int i = 0; i < locationList.count(); i++)
        ui->locationComboBox->addItem(locationList[i].getLabel());
    for(int i = 0; i < symbolicTypeList.count(); i++)
        ui->typeComboBox->addItem(symbolicTypeList[i].getLabel());
    for(int i = 0; i < symbolicNetworkList.count(); i++)
        ui->vendorComboBox->addItem(symbolicNetworkList[i].getLabel());
    for(int i = 0; i < hardwareTypeList.count(); i++)
        ui->pinTypeComboBox->addItem(hardwareTypeList[i].getLabel());
    for(int i = 0; i < moduleList->count(); i++)
        ui->moduleComboBox->addItem(moduleList->at(i).getLabel());
}

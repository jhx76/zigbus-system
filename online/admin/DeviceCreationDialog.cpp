#include "DeviceCreationDialog.h"
#include "ui_DeviceCreationDialog.h"

DeviceCreationDialog::DeviceCreationDialog(QList<Module> *moduleList, QueryBean* queryBean, QWidget *parent)
    : QDialog(parent), ui(new Ui::DeviceCreationDialog)
{
    ui->setupUi(this);
    try {
        this->queryBean = queryBean;
        this->moduleList = moduleList;
        initialize();
    }
    catch(const error::SqlException& exception) {
        qDebug() << exception.toString();
    }
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveAndAccept()));
    connect(ui->moduleComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onModuleSelectionChanged(QString)));
    connect(ui->pin1RadioNumeric, SIGNAL(toggled(bool)), this, SLOT(onPin1RadioChanged(bool)));
    connect(ui->optionPinGroupBox, SIGNAL(toggled(bool)), ui->pin2RadioNumeric, SLOT(setChecked(bool)));
    connect(ui->optionPinGroupBox, SIGNAL(toggled(bool)), this, SLOT(onPin2RadioChanged(bool)));
    connect(ui->pin2RadioNumeric, SIGNAL(toggled(bool)), this, SLOT(onPin2RadioChanged(bool)));
    connect(ui->pinTypeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onHardwareTypeSelectionChanged(QString)));
    ui->optionPinGroupBox->setChecked(false);
    ui->pin1RadioNumeric->setChecked(true);
    ui->pin2RadioNumeric->setChecked(true);
}

DeviceCreationDialog::~DeviceCreationDialog()
{
    moduleList = NULL;
    queryBean = NULL;
    delete ui;
}

void DeviceCreationDialog::initialize() {
    locationList = queryBean->getAllLocations();
    hardwareTypeList = queryBean->getAllHardwareTypes();
    hardwareSubtypeList = queryBean->getAllHardwareSubtypes();
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

    ui->pinSubTypeComboBox->clear();
    for(int i = 0; i < hardwareSubtypeList.count(); i++) {
        if(hardwareSubtypeList.at(i).getCorrespondingType() == ui->pinTypeComboBox->currentText()) {
            ui->pinSubTypeComboBox->addItem(hardwareSubtypeList.at(i).getSubtype());
        }
    }
}

void DeviceCreationDialog::saveAndAccept() {
    for(int i = 0; i < moduleList->count(); i++) {
        if(moduleList->at(i).getLabel() == ui->moduleComboBox->currentText()) {
            Module* tmpModule = &(moduleList->operator [](i));
            Device device;
            device.setPtrModule(tmpModule);
            device.setPinId(ui->pin1ComboBox->currentText());
            device.setInstance(ui->instanceLinEdit->text().trimmed());
            device.setLocation(ui->locationComboBox->currentText());
            device.setPinType(ui->pinTypeComboBox->currentText());
            if(!ui->pinSubTypeComboBox->currentText().isEmpty())
                device.setPinSubType(ui->pinSubTypeComboBox->currentText());
            if(ui->optionPinGroupBox->isChecked())
                device.setOptionalId(ui->pin2ComboBox->currentText());
            else
                device.setOptionalId("");
            device.setVendor(ui->vendorComboBox->currentText());
            device.setType(ui->typeComboBox->currentText());
            tmpModule->append(device);
            try {
                queryBean->insertDevice(device);
            }
            catch(const error::SqlException& exception) {
                qDebug() << exception.toString();
            }

            accept();
            return;
        }
    }
    QMessageBox messageBox;
    messageBox.setText("La déclaration de l'appareil a échoué !");
    messageBox.exec();
}

void DeviceCreationDialog::onModuleSelectionChanged(QString moduleLabel) {
    for(int i = 0; i < moduleList->count(); i++) {
        Module* tmpModule = &(moduleList->operator[](i));
        if(tmpModule->getLabel() == moduleLabel) {
            displayPinsForMainSelection(tmpModule);
        }
    }
}

void DeviceCreationDialog::displayPinsForMainSelection(Module* module) {
    ui->pin1ComboBox->clear();
    ui->pin2ComboBox->clear();
    for(int i = 0; i < (ui->pin1RadioNumeric->isChecked() ? module->getNumericIOCount() : module->getAnalogIOCount()); i++) {
        QString s = (ui->pin1RadioNumeric->isChecked() ? "S" : "A");
        s += QString::number(i);
        ui->pin1ComboBox->addItem(s);
    }

    for(int i = 0; i < (ui->pin2RadioNumeric->isChecked() ? module->getNumericIOCount() : module->getAnalogIOCount()); i++) {
        QString s = (ui->pin2RadioNumeric->isChecked() ? "S" : "A");
        s += QString::number(i);
        ui->pin2ComboBox->addItem(s);
    }
}

void DeviceCreationDialog::onPin1RadioChanged(bool) {
    onModuleSelectionChanged(ui->moduleComboBox->currentText());
}

void DeviceCreationDialog::onPin2RadioChanged(bool) {
    onModuleSelectionChanged(ui->moduleComboBox->currentText());
}

void DeviceCreationDialog::onHardwareTypeSelectionChanged(QString str) {
    ui->pinSubTypeComboBox->clear();
    for(int i = 0; i < hardwareSubtypeList.count(); i++) {
        if(hardwareSubtypeList.at(i).getCorrespondingType() == str) {
            ui->pinSubTypeComboBox->addItem(hardwareSubtypeList.at(i).getSubtype());
        }
    }
}

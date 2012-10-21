#include "DeviceEditionPanel.h"
#include "ui_DeviceEditionPanel.h"

DeviceEditionPanel::DeviceEditionPanel(QWidget *parent) : QWidget(parent), ui(new Ui::DeviceEditionPanel)
{
    ui->setupUi(this);
    this->deviceInEdition = NULL;
    moduleList = NULL;
    queryBean = NULL;
    QObject::connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(onSaveDevice()));
}

DeviceEditionPanel::DeviceEditionPanel(Device* deviceToEdit, QList<Module>* moduleList, QueryBean* queryBean, QWidget* parent) : QWidget(parent), ui(new Ui::DeviceEditionPanel)
{
    ui->setupUi(this);
    this->queryBean = queryBean;
    this->deviceInEdition = deviceToEdit;
    tmpDevice = *deviceInEdition;
    this->moduleList = moduleList;
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(onSaveDevice()));
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(onCloseButtonClick()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButtonClick()));
    try {
        initialize();
    }
    catch(const error::SqlException& exception) {
        qDebug() << exception.toString();
    }
}

DeviceEditionPanel::~DeviceEditionPanel()
{
    delete ui;
    queryBean = NULL;
    deviceInEdition = NULL;
}

void DeviceEditionPanel::initialize() {


    if(moduleList != NULL) {
        ui->moduleComboBox->clear();
        for(int i = 0; i < moduleList->count(); i++) {
            Module* tmpModule = &(moduleList->operator [](i));
            ui->moduleComboBox->addItem(tmpModule->getLabel());
            if(tmpDevice.getPtrModule()->getLabel() == tmpModule->getLabel()) {
                ui->moduleComboBox->setCurrentIndex(i);
            }
        }
    }

    if(queryBean != NULL) {
        locationList = queryBean->getAllLocations();
        typeList = queryBean->getAllSymbolicTypes();
        vendorList = queryBean->getAllSymbolicNetworks();
        zigbusNetworkList = queryBean->getAllZigbusNetworks();
        hardwareTypeList = queryBean->getAllHardwareTypes();
    }

    ui->locationComboBox->clear();
    for(int i = 0; i < locationList.count(); i++) {
        ui->locationComboBox->addItem(locationList.at(i).getLabel());
        if(tmpDevice.getLocation() == locationList.at(i).getLabel())
            ui->locationComboBox->setCurrentIndex(i);
    }

    ui->typeComboBox->clear();
    for(int i = 0; i < typeList.count(); i++) {
        ui->typeComboBox->addItem(typeList.at(i).getLabel());
        if(tmpDevice.getType() == typeList.at(i).getLabel())
            ui->typeComboBox->setCurrentIndex(i);
    }

    ui->vendorComboBox->clear();
    for(int i = 0; i < vendorList.count(); i++) {
        ui->vendorComboBox->addItem(vendorList.at(i).getLabel());
        if(tmpDevice.getVendor() == vendorList.at(i).getLabel())
            ui->vendorComboBox->setCurrentIndex(i);
    }

    ui->pinTypeComboBox->clear();
    for(int i = 0; i < hardwareTypeList.count(); i++) {
        ui->pinTypeComboBox->addItem(hardwareTypeList.at(i).getLabel());
        if(tmpDevice.getPinType() == hardwareTypeList.at(i).getLabel())
            ui->pinTypeComboBox->setCurrentIndex(i);
    }

    connect(ui->pin1RadioNumeric, SIGNAL(toggled(bool)), this, SLOT(onPin1RadioNumericSelected(bool)));
    connect(ui->pin2RadioNumeric, SIGNAL(toggled(bool)), this, SLOT(onPin2RadioNumericSelected(bool)));
    connect(ui->moduleComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onModuleSelectionChanged(QString)));

    if(tmpDevice.getPinId().contains("S"))
        ui->pin1RadioNumeric->setChecked(true);
    else
        ui->pin1RadioAnalogic->setChecked(true);

    if(!tmpDevice.getOptionalId().isEmpty()) {
        ui->optionPinGroupBox->setChecked(true);
        if(tmpDevice.getOptionalId().contains("S"))
            ui->pin2RadioNumeric->setChecked(true);
        else
            ui->pin2RadioAnalogic->setChecked(true);
    }
    else {
        ui->optionPinGroupBox->setChecked(false);
        ui->pin2RadioNumeric->setChecked(true);
    }

    refreshPinCombos();
}

void DeviceEditionPanel::onSaveDevice() {

    tmpDevice.setLocation(ui->locationComboBox->currentText());
    tmpDevice.setType(ui->typeComboBox->currentText());
    tmpDevice.setPinId(ui->pin1ComboBox->currentText());
    if(ui->optionPinGroupBox->isChecked())
        tmpDevice.setOptionalId(ui->pin2ComboBox->currentText());
    else
        tmpDevice.setOptionalId("");
    tmpDevice.setPinType(ui->pinTypeComboBox->currentText());
    tmpDevice.setInstance(ui->instanceLinEdit->text().trimmed());
    tmpDevice.setVendor(ui->vendorComboBox->currentText());

    try {
        qDebug() << QString::number(queryBean->updateDevice(*deviceInEdition, tmpDevice)) << " rows updated !";
    }
    catch(const error::SqlException& exception) {
        qDebug() << exception.toString();
    }

    Module* actualModule = deviceInEdition->getPtrModule();
    for(int i = 0; i < actualModule->deviceCount(); i++) {
        if(deviceInEdition == &(actualModule->elementAt(i))) {
            deviceInEdition = NULL;
            actualModule->removeAt(i);
        }
    }

    tmpDevice.getPtrModule()->append(tmpDevice);
    emit um_refresh();
}

void DeviceEditionPanel::refreshPinCombos() {
    if(deviceInEdition->getPtrModule() != NULL) {
        ui->pin1ComboBox->clear();
        for(int i = 0; i < (ui->pin1RadioNumeric->isChecked() ? deviceInEdition->getPtrModule()->getNumericIOCount()
                            : deviceInEdition->getPtrModule()->getAnalogIOCount()); i++) {
            QString s = (ui->pin1RadioNumeric->isChecked() ? "S" : "A");
            s += QString::number(i);
            ui->pin1ComboBox->addItem(s);
            if(s == deviceInEdition->getPinId()) ui->pin1ComboBox->setCurrentIndex(i);
        }

        ui->pin2ComboBox->clear();
        if(deviceInEdition->getOptionalId().contains("A")) ui->pin2RadioAnalogic->setChecked(true);
        else ui->pin2RadioNumeric->setChecked(true);
        for(int i = 0; i < (ui->pin2RadioNumeric->isChecked() ? deviceInEdition->getPtrModule()->getNumericIOCount()
                            : deviceInEdition->getPtrModule()->getAnalogIOCount()); i++) {
            QString s = (ui->pin2RadioNumeric->isChecked()? "S" : "A");
            s += QString::number(i);
            /// @todo device support for second Pin (heater, servo, pwm, etc...)
            if(!deviceInEdition->getOptionalId().isEmpty() &&
                    s == deviceInEdition->getOptionalId())
            {
                ui->optionPinGroupBox->setChecked(true);
                    ui->pin2ComboBox->setCurrentIndex(i);
            }
        }
    }
}

void DeviceEditionPanel::onModuleSelectionChanged(QString s) {
    for(int i = 0; i < moduleList->count(); i++) {
        qDebug() << "module selection changed !";
        if(s == moduleList->at(i).getLabel())
            tmpDevice.setPtrModule(&(moduleList->operator [](i)));
    }
    refreshPinCombos();
}

void DeviceEditionPanel::onPin1RadioNumericSelected(bool numeric) {
    refreshPinCombos();
}

void DeviceEditionPanel::onPin1SelectionChanged(QString selected) {
    tmpDevice.setPinId(selected);
}

void DeviceEditionPanel::onPin2RadioNumericSelected(bool numeric) {
    refreshPinCombos();
}

void DeviceEditionPanel::onPin2SelectionChanged(QString selected) {
    if(ui->optionPinGroupBox->isChecked())
        tmpDevice.setOptionalId(selected);
    else
        tmpDevice.setOptionalId("");
}

void DeviceEditionPanel::onCloseButtonClick() {
    emit um_panel_closed();
    this->close();
}

void DeviceEditionPanel::onCancelButtonClick() {
    this->initialize();
}


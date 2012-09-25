#include "DeviceEditionPanel.h"
#include "ui_DeviceEditionPanel.h"

DeviceEditionPanel::DeviceEditionPanel(QWidget *parent) : QWidget(parent), ui(new Ui::DeviceEditionPanel)
{
    ui->setupUi(this);
    this->deviceInEdition = NULL;
    QObject::connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(onSaveDevice()));
}

DeviceEditionPanel::DeviceEditionPanel(Device* deviceToEdit, QWidget* parent) : QWidget(parent), ui(new Ui::DeviceEditionPanel)
{
    ui->setupUi(this);
    this->deviceInEdition = deviceToEdit;
    QObject::connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(onSaveDevice()));
}

DeviceEditionPanel::~DeviceEditionPanel()
{
    delete ui;
    deviceInEdition = NULL; // On ne delete pas l'object en edition car il ne nous appartient pas
}

void DeviceEditionPanel::onSaveDevice() {
    emit this->um_save_device(deviceInEdition);
}




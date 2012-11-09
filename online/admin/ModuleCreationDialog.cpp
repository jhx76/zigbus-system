#include "ModuleCreationDialog.h"
#include "ui_ModuleCreationDialog.h"

ModuleCreationDialog::ModuleCreationDialog(QueryBean* queryBean, QList<Module>* moduleList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModuleCreationDialog)
{
    ui->setupUi(this);
    this->queryBean = queryBean;
    this->moduleList = moduleList;
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveAndAccept()));
    initialize();
}

ModuleCreationDialog::~ModuleCreationDialog() {
    delete ui;
}

void ModuleCreationDialog::initialize() {
    try {
        this->setAttribute(Qt::WA_DeleteOnClose);
        if(queryBean != NULL) {
            this->zigbusNetworkList = queryBean->getAllZigbusNetworks();
            ui->zigbusNetworkCombo->clear();
            for(int i = 0; i < zigbusNetworkList.count(); i++)
                ui->zigbusNetworkCombo->addItem(zigbusNetworkList.at(i).getLabel());
        }
    }
    catch(const error::SqlException& exception) {
        qDebug() << exception.toString();
    }
}

void ModuleCreationDialog::saveAndAccept() {
    try {
        Module tmpModule;
        tmpModule.setLabel(ui->moduleIdEdit->text().trimmed());
        bool ok;
        int nbAnalogic = ui->nbPinAnalogicEdit->text().toInt(&ok);
        if(!ok) {
            qDebug() << "error: unable to convert nbPinAnalogic '"<<ui->nbPinAnalogicEdit->text()<<"' into integer";
            return;
        }
        tmpModule.setAnalogIOCount(nbAnalogic);

        int nbNumeric = ui->nbPinNumericEdit->text().toInt(&ok);
        if(!ok) {
            qDebug() << "error: unable to convert nbPinNumeric '"<<ui->nbPinNumericEdit->text()<<"' into integer";
            return;
        }
        tmpModule.setNumericIOCount(nbNumeric);
        tmpModule.setZigbusNetworkId(ui->zigbusNetworkCombo->currentText());
        moduleList->append(tmpModule);
        queryBean->insertModule(tmpModule);
        accept();
        return;
    }
    catch(const error::SqlException& exception) {
        qDebug() << exception.toString();
    }
}

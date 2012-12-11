#include "LocationCreationDialog.h"
#include "ui_LocationCreationDialog.h"

LocationCreationDialog::LocationCreationDialog(QueryBean* queryBean, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LocationCreationDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Create Location");
    this->queryBean = queryBean;
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveAndAccept()));
}

LocationCreationDialog::~LocationCreationDialog()
{
    delete ui;
    queryBean = NULL;
}

void LocationCreationDialog::initialize() {
    try {
        this->setAttribute(Qt::WA_DeleteOnClose);
        if(queryBean != NULL) {
            this->locationList = queryBean->getAllLocations();
        }
    }
    catch(const error::SqlException& exception) {
        qDebug() << exception.toString();
    }
}

void LocationCreationDialog::saveAndAccept() {
    if(!ui->labelEdit->text().trimmed().isEmpty()) {
        newLocation.setLabel(ui->labelEdit->text().trimmed());
        newLocation.setDescription(ui->descriptionEdit->toPlainText().trimmed());
        newLocation.setId(-1);
        //On vérifie bien que l'objet n'a pas deja ete créé:
        for(int i = 0; i < locationList.count(); i++) {
            qDebug() << "compare with " << locationList[i].getLabel();
            if(locationList[i].getLabel().trimmed().toUpper() == newLocation.getLabel().trimmed().toUpper()) {
                QMessageBox msgBox;
                msgBox.setText("Impossible de continuer ! Une location portant ce nom existe déjà.");
                msgBox.exec();
                return;
            }
        }
        queryBean->insertLocation(newLocation);
        this->accept();
    }
}

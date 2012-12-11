#include "LocationManagementDialog.h"
#include "ui_LocationManagementDialog.h"

LocationManagementDialog::LocationManagementDialog(QueryBean* queryBean, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LocationManagementDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Edit locations");
    this->queryBean = queryBean;
    ui->locationListView->setModel(&locationModel);
    ui->locationListView->setSelectionMode(QAbstractItemView::SingleSelection);
    initialize();

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(onAddButtonClick()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(onRemoveButtonClick()));
    connect(ui->modifyButton, SIGNAL(clicked()), this, SLOT(onEditButtonClick()));
}

LocationManagementDialog::~LocationManagementDialog()
{
    delete ui;
}

void LocationManagementDialog::initialize() {
    try {
        if(queryBean != NULL) {
            locationList.clear();
            stringList.clear();
            this->locationList = queryBean->getAllLocations();
            for(int i = 0; i < locationList.count(); i++) {
                stringList << locationList[i].getLabel();
            }
            locationModel.setStringList(stringList);
        }
    }
    catch(const error::SqlException& exception) {
        qDebug() << exception.toString();
    }
    catch(const error::NullPointerException& exception) {
        qDebug() << exception.toString();
    }
}

void LocationManagementDialog::onAddButtonClick() {
    LocationCreationDialog* dialog = new LocationCreationDialog(queryBean, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    connect(dialog, SIGNAL(accepted()), this, SLOT(initialize()));
    dialog->show();
}

void LocationManagementDialog::onRemoveButtonClick() {
    QModelIndex selectedIndex = ui->locationListView->currentIndex();
    QVariant selectedVariant = locationModel.data(selectedIndex, Qt::DisplayRole);
    QString selectedLabel = selectedVariant.toString();
    QMessageBox messageBox;
    messageBox.setText("The location \""+selectedLabel+"\" will be removed.");
    messageBox.setInformativeText("Are you sure you want to suppress this location ?");
    messageBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    int ret = messageBox.exec();
    switch(ret) {
    case QMessageBox::Cancel:
        //nothing todo
        break;

    case QMessageBox::Ok:
        for(int i = 0; i < locationList.count(); i++) {
            if(locationList[i].getLabel() == selectedLabel) {
                //C'est l'index i qu'il faut retirer
                //Suppression de la base + recharge des données
                queryBean->deleteLocation(locationList[i]);
                initialize();
                return;
            }
        }
        break;
    default: ;
    }
}

void LocationManagementDialog::onEditButtonClick() {

}

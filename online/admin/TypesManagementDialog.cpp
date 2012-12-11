#include "TypesManagementDialog.h"
#include "ui_TypesManagementDialog.h"

TypesManagementDialog::TypesManagementDialog(QueryBean* queryBean, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TypesManagementDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Edit Types");
    this->queryBean = queryBean;
    ui->typeListView->setModel(&labelListModel);
    ui->typeListView->setSelectionMode(QAbstractItemView::SingleSelection);
    initialize();

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(onAddButtonClick()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(onRemoveButtonClick()));
    connect(ui->modifyButton, SIGNAL(clicked()), this, SLOT(onEditButtonClick()));
}

TypesManagementDialog::~TypesManagementDialog() {
    delete ui;
}

void TypesManagementDialog::initialize() {
    try {
        if(queryBean != NULL) {
            typeList.clear();
            labelList.clear();
            typeList = queryBean->getAllSymbolicTypes();
            for(int i = 0; i < typeList.count(); i++) {
                this->labelList << typeList[i].getLabel();
            }
            labelListModel.setStringList(labelList);
        }
    }
    catch(const error::SqlException& exception) {
        qDebug() << exception.toString();
    }
    catch(const error::NullPointerException& exception) {
        qDebug() << exception.toString();
    }
}

void TypesManagementDialog::onAddButtonClick() {
    TypeCreationDialog* dialog = new TypeCreationDialog("Create Type", queryBean, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    connect(dialog, SIGNAL(accepted()), this, SLOT(initialize()));
    dialog->show();
}

void TypesManagementDialog::onRemoveButtonClick() {
    QModelIndex selectedIndex = ui->typeListView->currentIndex();
    QVariant selectedVariant = this->labelListModel.data(selectedIndex, Qt::DisplayRole);
    QString selectedLabel = selectedVariant.toString();
    QMessageBox messageBox;
    messageBox.setText("The type \""+selectedLabel+"\" will be removed.");
    messageBox.setInformativeText("Are you sure you want to suppress this type ?");
    messageBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    int ret = messageBox.exec();
    switch(ret) {
    case QMessageBox::Cancel:
        //nothing todo
        break;

    case QMessageBox::Ok:
        for(int i = 0; i < typeList.count(); i++) {
            if(typeList[i].getLabel() == selectedLabel) {
                queryBean->deleteSymbolicTypeById(typeList[i].getId());
                initialize();
                return;
            }
        }
        break;
    default: ;
    }
}

void TypesManagementDialog::onEditButtonClick() {

}

#include "TypeCreationDialog.h"
#include "ui_TypeCreationDialog.h"

TypeCreationDialog::TypeCreationDialog(const QString& windowTitle, QueryBean* queryBean, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TypeCreationDialog)
{
    ui->setupUi(this);
    setWindowTitle(windowTitle);
    this->queryBean = queryBean;
    initialize();

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveAndAccept()));
}

TypeCreationDialog::~TypeCreationDialog()
{
    delete ui;
}

void TypeCreationDialog::initialize() {
    try {
        if(queryBean != NULL) {
            typeList = queryBean->getAllSymbolicTypes();
        }
    }
    catch(const error::SqlException& exception) {
        qDebug() << exception.toString();
    }
}

void TypeCreationDialog::saveAndAccept() {
    if(!ui->labelEdit->text().trimmed().isEmpty()) {
        newType.setLabel(ui->labelEdit->text().trimmed());
        newType.setDescription(ui->descriptionEdit->toPlainText().trimmed());
        newType.setId(-1);
        //On vérifie bien que l'objet n'a pas deja ete créé:
        for(int i = 0; i < typeList.count(); i++) {
            if(typeList[i].getLabel().trimmed().toUpper() == newType.getLabel().trimmed().toUpper()) {
                QMessageBox msgBox;
                msgBox.setText("Impossible de continuer ! Ce type existe déjà.");
                msgBox.exec();
                return;
            }
        }
        queryBean->insertSymbolicType(newType);
        this->accept();
    }
}

#include "DatabaseConnectionDialog.h"
#include "ui_DatabaseConnectionDialog.h"

DatabaseConnectionDialog::DatabaseConnectionDialog(QWidget *parent) : QDialog(parent), ui(new Ui::DatabaseConnectionDialog)
{
    ui->setupUi(this);
    try {
        defaultProperties = DatabaseProperties("./config/admin.xml");
        //currentProperties = defaultProperties;
        currentProperties = new DatabaseProperties(defaultProperties);
        if(!currentProperties) {
            throw error::NullPointerException("DatabaseProperties::currentProperties", AT);
        }
        refreshDisplayedValues();
    }
    catch(const QString& exception) {
        qDebug() << exception;
    }
    catch(const error::NullPointerException& exception) {
        qDebug() << exception.toString();
    }
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(validDatabaseAndAccept()));
    connect(ui->hostEdit, SIGNAL(textChanged(QString)), this, SLOT(onHostValueChanged(QString)));
    connect(ui->portEdit, SIGNAL(textChanged(QString)), this, SLOT(onPortEditValueChanged(QString)));
    connect(ui->passwordEdit, SIGNAL(textChanged(QString)), this, SLOT(onPasswordChanged(QString)));
    connect(ui->userEdit, SIGNAL(textChanged(QString)), this, SLOT(onUserNameChanged(QString)));
    connect(ui->databaseNameEdit, SIGNAL(textChanged(QString)), SLOT(onDatabaseNameChanged(QString)));
    connect(this, SIGNAL(propertiesValueChanged()), this, SLOT(onPropertiesValueChanged()));
}

DatabaseConnectionDialog::~DatabaseConnectionDialog()
{
    delete ui;
    currentProperties = NULL;
}

void DatabaseConnectionDialog::onDefaultPropertiesChecked(bool checked) {
    if(checked) {
        *currentProperties = defaultProperties;
        refreshDisplayedValues();
    }
}

void DatabaseConnectionDialog::refreshDisplayedValues() {
    ui->portEdit->setText(QString::number(currentProperties->getHostPort()));
    ui->hostEdit->setText(currentProperties->getHostAddress());
    ui->databaseNameEdit->setText(currentProperties->getDatabaseName());
    ui->userEdit->setText(currentProperties->getUserName());
    ui->passwordEdit->setText(currentProperties->getPassword());
}

void DatabaseConnectionDialog::onPortEditValueChanged(QString newValue) {
    try {
        bool ok;
        int value = ui->portEdit->text().toInt(&ok);
        if(!ok)
            throw QString("Unable to translate'"+newValue+"' into integer...");
        currentProperties->setHostPort(value);
        emit propertiesValueChanged();
    }
    catch(const QString& exception) {
        qDebug() << exception;
        ui->passwordEdit->setText(QString::number(currentProperties->getHostPort()));
    }
}

void DatabaseConnectionDialog::onDatabaseNameChanged(QString databaseName) {
    currentProperties->setDatabaseName(databaseName);
    emit propertiesValueChanged();
}

void DatabaseConnectionDialog::onHostValueChanged(QString host) {
    currentProperties->setHostAddress(host);
    emit propertiesValueChanged();
}

void DatabaseConnectionDialog::onPasswordChanged(QString password) {
    currentProperties->setPassword(password);
    emit propertiesValueChanged();
}

void DatabaseConnectionDialog::onUserNameChanged(QString userName) {
    currentProperties->setUserName(userName);
    emit propertiesValueChanged();
}

void DatabaseConnectionDialog::onPropertiesValueChanged() {
    ui->defaultCheckBox->setChecked(false);
    refreshDisplayedValues();
}

void DatabaseConnectionDialog::validDatabaseAndAccept() {
    try {
        QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
        database.setHostName(currentProperties->getHostAddress());
        if(database.hostName().isEmpty())
            throw QString("hostName cannot be empty !");
        database.setDatabaseName(currentProperties->getDatabaseName());
        if(database.databaseName().isEmpty())
            throw QString("databaseName cannot be empty !");
        database.setUserName(currentProperties->getUserName());
        if(database.userName().isEmpty())
            throw QString("userName cannot be empty !");
        database.setPassword(currentProperties->getPassword());
        if(!database.open())
            throw QString("unable to reach the database...");
        else
            qDebug() << "database properties OK. Ready to be sent !";
        database.close();
        emit this->propertiesValidated(currentProperties);
        qDebug() << "properties sent !";
        //this->accept();
        this->close();
    }
    catch(const QString& exception) {
        QMessageBox msgBox;
        msgBox.setText(exception);
        msgBox.setInformativeText("Check the connection information");
        msgBox.setStandardButtons(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch(ret) {
            case QMessageBox::Ok:
                ui->passwordEdit->setText("");
                currentProperties->setPassword("");
                break;
            default:
                ;
        }
    }
}

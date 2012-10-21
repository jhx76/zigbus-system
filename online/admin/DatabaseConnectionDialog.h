#ifndef DATABASECONNECTIONDIALOG_H
#define DATABASECONNECTIONDIALOG_H

#include <QDialog>
#include <QFile>
#include <QSqlDatabase>
#include <QMessageBox>

#include <core/DatabaseProperties.h>
#include <core/Error.h>

namespace Ui {
    class DatabaseConnectionDialog;
}

class DatabaseConnectionDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::DatabaseConnectionDialog *ui;
    DatabaseProperties defaultProperties;
    DatabaseProperties *currentProperties;

public:
    explicit DatabaseConnectionDialog(QWidget *parent = 0);
    ~DatabaseConnectionDialog();
    const DatabaseProperties& getDefaultProperties() const { return defaultProperties; }
    void setDefaultProperties(const DatabaseProperties& properties) { this->defaultProperties = properties; }
    const DatabaseProperties& getCurrentProperties() const { return *currentProperties; }
    void setCurrentProperties(const DatabaseProperties& properties) { *(this->currentProperties) = properties; }



public slots:
    void onDefaultPropertiesChecked(bool checked);
    void onPortEditValueChanged(QString);
    void onHostValueChanged(QString);
    void onDatabaseNameChanged(QString);
    void onUserNameChanged(QString);
    void onPasswordChanged(QString);
    void onPropertiesValueChanged();

    void refreshDisplayedValues();
    void validDatabaseAndAccept();

signals:
    void propertiesValueChanged();
    void propertiesValidated(DatabaseProperties *properties);


};

#endif // DATABASECONNECTIONDIALOG_H

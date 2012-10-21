#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QList>
#include <QString>
#include <QDebug>
#include <QVariant>

#include <core/QueryBean.h>

#include <DatabaseConnectionDialog.h>
#include <DeviceAdministrationPanel.h>
#include <DeviceCreationDialog.h>

#include <core/Module.h>
#include <core/Device.h>

namespace Ui {
    class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT
private:
    QueryBean *queryBean;

    Ui::AdminWindow *ui;
    QSqlDatabase database;
    QList<Module> moduleList;
    QWidget* currentPanel;

public:
    explicit AdminWindow(QWidget *parent = 0);

    virtual ~AdminWindow();

    void initialize();

public slots:
    void OnBtDeviceAdminClick();

    void OnNewModuleTriggered();

    void OnNewDeviceTriggered();

    void connectDatabase(DatabaseProperties *properties);

};

#endif // ADMINWINDOW_H

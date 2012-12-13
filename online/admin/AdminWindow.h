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

#include <DatabaseConnectionDialog.h>
#include <DeviceAdministrationPanel.h>
#include <DeviceCreationDialog.h>
#include <LocationManagementDialog.h>
#include <TypesManagementDialog.h>

#include <core/Module.h>
#include <core/Device.h>
#include <core/QueryBean.h>
#include <core/ApplicationInformation.h>


#define _EVOLUTION \
    "01/12/2012|1.0.0.0|Admin Creation\n" \
    "01/12/2012|1.0.0.1|add tooltips\n" \
    "01/12/2012|1.0.1.0|enable locations and types Management\n" \

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
    ApplicationInformation *zAppInfo;

public:
    explicit AdminWindow(QWidget *parent = 0);
    virtual ~AdminWindow();
    void initialize();

public slots:
    void OnBtDeviceAdminClick();
    void OnNewModuleTriggered();
    void OnNewDeviceTriggered();
    void OnEditLocationTriggered();
    void connectDatabase(DatabaseProperties *properties);
    void OnEditTypesTriggered();
};

#endif // ADMINWINDOW_H

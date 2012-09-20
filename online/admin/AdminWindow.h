#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QList>
#include <QString>
#include <QDebug>
#include <QVariant>

#include <DeviceAdministrationPanel.h>

#include <core/Module.h>
#include <core/Device.h>

namespace Ui {
    class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::AdminWindow *ui;
    QSqlDatabase database;
    QList<Module> moduleList;

public:
    explicit AdminWindow(QWidget *parent = 0);

    ~AdminWindow();

    void initialize();

public slots:
    void OnBtDeviceAdminClick();


};

#endif // ADMINWINDOW_H

#ifndef DEVICEADMINISTRATIONPANEL_H
#define DEVICEADMINISTRATIONPANEL_H

#include <QWidget>
#include <QList>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QDebug>

#include <core/Device.h>
#include <core/Module.h>
#include <core/ModuleTreeItem.h>
#include <core/DeviceTreeItem.h>


namespace Ui {
    class DeviceAdministrationPanel;
}

class DeviceAdministrationPanel : public QWidget
{
    Q_OBJECT
private:
    Ui::DeviceAdministrationPanel *ui;
    QList<Module>* moduleList;

    QStandardItemModel* model;

public:
    explicit DeviceAdministrationPanel(QList<Module>* moduleList, QWidget *parent = 0);
    ~DeviceAdministrationPanel();
    void initialize();

};

#endif // DEVICEADMINISTRATIONPANEL_H

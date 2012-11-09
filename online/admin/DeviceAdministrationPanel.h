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
#include <core/QueryBean.h>

#include <core/model/HardwareTypeModel.h>
#include <core/model/LocationModel.h>
#include <core/model/SymbolicNetworkModel.h>
#include <core/model/SymbolicTypeModel.h>
#include <core/model/ZigbusNetworkModel.h>

#include <DeviceEditionPanel.h>
#include <ModuleEditionPanel.h>
#include <DeviceCreationDialog.h>
#include <ModuleCreationDialog.h>

#include <QMessageBox>

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

    QueryBean *queryBean;

    QWidget* displayedWidget;

public:
    /*explicit*/ DeviceAdministrationPanel(QList<Module>* moduleList, QueryBean* queryBean, QWidget *parent = 0);

    ~DeviceAdministrationPanel();

public slots:
    void onItemSelection(QModelIndex);

    void initialize();

    void panelIsClosed() { this->displayedWidget = NULL; }

    void onModifySelectedToolClick();

    void onDeleteSelectedToolClick();

    void onNewModuleToolClick();

    void onNewDeviceToolClick();
};

#endif // DEVICEADMINISTRATIONPANEL_H

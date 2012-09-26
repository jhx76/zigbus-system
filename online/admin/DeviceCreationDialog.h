#ifndef DEVICECREATIONDIALOG_H
#define DEVICECREATIONDIALOG_H

#include <QDialog>
#include <QList>
#include <QDebug>

#include <core/Error.h>
#include <core/Module.h>
#include <core/Device.h>
#include <core/QueryBean.h>

#include <core/model/HardwareTypeModel.h>
#include <core/model/LocationModel.h>
#include <core/model/SymbolicNetworkModel.h>
#include <core/model/SymbolicTypeModel.h>
#include <core/model/ZigbusNetworkModel.h>

namespace Ui {
    class DeviceCreationDialog;
}

class DeviceCreationDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::DeviceCreationDialog *ui;

    QList<Module> *moduleList;

    QueryBean* queryBean;

    QList<LocationModel> locationList;

    QList<HardwareTypeModel> hardwareTypeList;

    QList<SymbolicTypeModel> symbolicTypeList;

    QList<SymbolicNetworkModel> symbolicNetworkList;

    QList<ZigbusNetworkModel> zigbusNetworkList;

public:
    explicit DeviceCreationDialog(QList<Module> *moduleList = NULL, QueryBean* queryBean = NULL, QWidget *parent = 0);

    virtual ~DeviceCreationDialog();

    void initialize();

    QList<Module>* getPtrModuleList() { return moduleList; }

    void setPtrModuleList(QList<Module>* ptr) { this->moduleList = ptr; }



};

#endif // DEVICECREATIONDIALOG_H

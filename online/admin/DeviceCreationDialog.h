#ifndef DEVICECREATIONDIALOG_H
#define DEVICECREATIONDIALOG_H

#include <QDialog>
#include <QList>
#include <QDebug>
#include <QMessageBox>

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

    void displayPinsForMainSelection(Module* module);


public:
    explicit DeviceCreationDialog(QList<Module> *moduleList = NULL, QueryBean* queryBean = NULL, QWidget *parent = 0);

    ~DeviceCreationDialog();

    void initialize();

    QList<Module>* getPtrModuleList() { return moduleList; }

    void setPtrModuleList(QList<Module>* ptr) { this->moduleList = ptr; }

public slots:
    void saveAndAccept();

    void onModuleSelectionChanged(QString moduleLabel);

    void onPin2RadioChanged(bool);

    void onPin1RadioChanged(bool);

};

#endif // DEVICECREATIONDIALOG_H

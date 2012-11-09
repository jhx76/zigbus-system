#ifndef DEVICEEDITIONPANEL_H
#define DEVICEEDITIONPANEL_H

#include <QWidget>
#include <QList>
#include <QDebug>

#include <core/Device.h>
#include <core/QueryBean.h>
#include <core/Error.h>

#include <core/model/HardwareTypeModel.h>
#include <core/model/LocationModel.h>
#include <core/model/SymbolicNetworkModel.h>
#include <core/model/SymbolicTypeModel.h>
#include <core/model/ZigbusNetworkModel.h>

namespace Ui {
    class DeviceEditionPanel;
}

class DeviceEditionPanel : public QWidget
{
    Q_OBJECT
private:
    Ui::DeviceEditionPanel *ui;

    QueryBean* queryBean;

    Device* deviceInEdition;

    Device tmpDevice;

    QList<Module>* moduleList;

    QList<LocationModel> locationList;

    QList<SymbolicTypeModel> typeList;

    QList<SymbolicNetworkModel> vendorList;

    QList<ZigbusNetworkModel> zigbusNetworkList;

    QList<HardwareTypeModel> hardwareTypeList;

    QList<HardwareSubTypeModel> hardwareSubtypeList;

public:
    DeviceEditionPanel(QWidget *parent = 0);

    DeviceEditionPanel(Device *deviceToEdit, QList<Module>* moduleList, QueryBean* queryBean, QWidget *parent = 0);

    ~DeviceEditionPanel();

    void initialize();

public slots:
    void onSaveDevice();

    void onModuleSelectionChanged(QString);

    void refreshPinCombos();

    void onHardwareTypeSelectionChanged(QString);

    void onPin1SelectionChanged(QString);

    void onPin1RadioNumericSelected(bool);

    void onPin2SelectionChanged(QString);

    void onPin2RadioNumericSelected(bool);

    void onCancelButtonClick();

    void onCloseButtonClick();

    void onPin2GroupBoxChecked(bool);

signals:
    void um_save_device(Device*);
    void um_panel_closed();
    void um_refresh();
};

#endif // DEVICEEDITIONPANEL_H

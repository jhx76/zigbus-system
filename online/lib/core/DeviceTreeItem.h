#ifndef DEVICETREEITEM_H
#define DEVICETREEITEM_H

#include <QStandardItem>

#include <core/Device.h>


class DeviceTreeItem : public QStandardItem
{
private:
    Device *device;

public:
    DeviceTreeItem();
    DeviceTreeItem(Device* device);
    DeviceTreeItem(const DeviceTreeItem& other);
};

#endif // DEVICETREEITEM_H

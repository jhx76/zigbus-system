#include "DeviceTreeItem.h"

DeviceTreeItem::DeviceTreeItem() : QStandardItem() {
    device = NULL;
}

DeviceTreeItem::DeviceTreeItem(Device* device)
    : QStandardItem(device->getGenericAddress().toString())
{
    this->device = device;
}

DeviceTreeItem::DeviceTreeItem(const DeviceTreeItem &other) : QStandardItem(other) {
    this->device = other.device;
}

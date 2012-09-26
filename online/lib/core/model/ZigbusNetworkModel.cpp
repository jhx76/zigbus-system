#include "ZigbusNetworkModel.h"

ZigbusNetworkModel::ZigbusNetworkModel()
{
    this->label = "";
    this->description = "";
    this->id = -1;
}

ZigbusNetworkModel::ZigbusNetworkModel(const QString &label, const QString &description, int id) {
    this->label = label;
    this->description = description;
    this->id = id;
}

ZigbusNetworkModel::ZigbusNetworkModel(const ZigbusNetworkModel &other) {
    this->label = other.label;
    this->description = other.description;
    this->id = other.id;
}

bool ZigbusNetworkModel::isEqual(const ZigbusNetworkModel &other) const {
    return (this->label == other.label && this->description == other.label && this->id == other.id);
}

ZigbusNetworkModel& ZigbusNetworkModel::operator=(const ZigbusNetworkModel& other) {
    this->label = other.label;
    this->description = other.description;
    this->id = other.id;
    return *this;
}

bool operator==(const ZigbusNetworkModel& a, const ZigbusNetworkModel& b) {
    return a.isEqual(b);
}

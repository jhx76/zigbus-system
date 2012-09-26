#include "HardwareTypeModel.h"


HardwareTypeModel::HardwareTypeModel()
{
    this->label = "";
    this->description = "";
    this->id = -1;
}

HardwareTypeModel::HardwareTypeModel(const QString &label, const QString &description, int id) {
    this->label = label;
    this->description = description;
    this->id = id;
}

HardwareTypeModel::HardwareTypeModel(const HardwareTypeModel &other) {
    this->label = other.label;
    this->description = other.description;
    this->id = other.id;
}

bool HardwareTypeModel::isEqual(const HardwareTypeModel &other) const {
    return (this->label == other.label && this->description == other.label && this->id == other.id);
}

HardwareTypeModel& HardwareTypeModel::operator=(const HardwareTypeModel& other) {
    this->label = other.label;
    this->description = other.description;
    this->id = other.id;
    return *this;
}

bool operator==(const HardwareTypeModel& a, const HardwareTypeModel& b) {
    return a.isEqual(b);
}

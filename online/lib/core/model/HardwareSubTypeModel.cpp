#include "HardwareSubTypeModel.h"

HardwareSubTypeModel::HardwareSubTypeModel()
{
    id = -1;
    subtype = "";
    correspondingType = "";
    description = "";
}

HardwareSubTypeModel::HardwareSubTypeModel(int id, const QString &subtype, const QString &correspondingType, const QString &description)
{
    this->id = id;
    this->subtype = subtype;
    this->correspondingType = correspondingType;
    this->description = description;
}

HardwareSubTypeModel::HardwareSubTypeModel(const HardwareSubTypeModel &other) {
    this->id = other.id;
    this->subtype = other.subtype;
    this->correspondingType = other.correspondingType;
    this->description = other.description;
}

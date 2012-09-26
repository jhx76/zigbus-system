#include "LocationModel.h"

LocationModel::LocationModel()
{
    this->label = "";
    this->description = "";
    this->id = -1;
}

LocationModel::LocationModel(const QString &label, const QString &description, int id) {
    this->label = label;
    this->description = description;
    this->id = id;
}

LocationModel::LocationModel(const LocationModel &other) {
    this->label = other.label;
    this->description = other.description;
    this->id = other.id;
}

bool LocationModel::isEqual(const LocationModel &other) const {
    return (this->label == other.label && this->description == other.label && this->id == other.id);
}

LocationModel& LocationModel::operator=(const LocationModel& other) {
    this->label = other.label;
    this->description = other.description;
    this->id = other.id;
    return *this;
}

bool operator==(const LocationModel& a, const LocationModel& b) {
    return a.isEqual(b);
}

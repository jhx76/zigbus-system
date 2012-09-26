#include "SymbolicTypeModel.h"

SymbolicTypeModel::SymbolicTypeModel()
{
    label = "";
    description = "";
    id = -1;
}

SymbolicTypeModel::SymbolicTypeModel(const QString &label, const QString &description, int id) {
    this->id = id;
    this->label = label;
    this->description = description;
}

SymbolicTypeModel::SymbolicTypeModel(const SymbolicTypeModel &other) {
    this->id = other.id;
    this->label = other.label;
    this->description = other.description;
}

bool SymbolicTypeModel::isEqual(const SymbolicTypeModel &other) const {
    return (this->id == other.id && this->label == other.label && this->description == other.description);
}

bool operator==(const SymbolicTypeModel& a, const SymbolicTypeModel& b) {
    return a.isEqual(b);
}

SymbolicTypeModel& SymbolicTypeModel::operator=(const SymbolicTypeModel& other) {
    this->id = other.id;
    this->label = other.label;
    this->description = other.description;
    return *this;
}

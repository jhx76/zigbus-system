#include "SymbolicNetworkModel.h"

SymbolicNetworkModel::SymbolicNetworkModel()
{
    this->label = "";
    this->description = "";
    this->id = -1;
}

SymbolicNetworkModel::SymbolicNetworkModel(const QString &label, const QString &description, int id) {
    this->label = label;
    this->description = description;
    this->id = id;
}

SymbolicNetworkModel::SymbolicNetworkModel(const SymbolicNetworkModel &other) {
    this->label = other.label;
    this->description = other.description;
    this->id = other.id;
}

bool SymbolicNetworkModel::isEqual(const SymbolicNetworkModel &other) const {
    return (this->label == other.label && this->description == other.label && this->id == other.id);
}

SymbolicNetworkModel& SymbolicNetworkModel::operator=(const SymbolicNetworkModel& other) {
    this->label = other.label;
    this->description = other.description;
    this->id = other.id;
    return *this;
}

bool operator==(const SymbolicNetworkModel& a, const SymbolicNetworkModel& b) {
    return a.isEqual(b);
}

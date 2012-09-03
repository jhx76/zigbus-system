#include "Device.h"

Device::Device()
{
    this->vendor = "";
    this->type = "";
    this->location = "";
    this->instance = "";
    this->pinId = "";
    this->pinType = "";
    this->module = NULL;
}

//----------------------------------------------------------------------------

Device::Device(const QString &vendor, const QString &type, const QString &location, const QString &instance)
{
    this->vendor = vendor;
    this->type = type;
    this->location = location;
    this->instance = instance;
    this->pinId = "";
    this->pinType = "";
    this->module = NULL;
}

//----------------------------------------------------------------------------

Device::Device(const QString &pinType, const QString &pinId) {
    this->vendor = vendor;
    this->type = type;
    this->location = location;
    this->instance = instance;
    this->pinId = pinId;
    this->pinType = pinType;
    this->module = NULL;
}

//----------------------------------------------------------------------------

Device::Device(const Device &other) {
    this->vendor = other.vendor;
    this->type = other.type;
    this->location = other.location;
    this->instance = other.instance;
    this->pinId = other.pinId;
    this->pinType = other.pinType;
    this->module = other.module;
}

//----------------------------------------------------------------------------

bool Device::isEqual(const Device &other) const {
    return (this->vendor == other.vendor && this->type == other.type && this->location == other.location
            && this->instance == other.instance
            && this->pinId == other.pinId && this->pinType == other.pinType);
}

//----------------------------------------------------------------------------

Device& Device::operator =(const Device& other) {
    this->vendor = other.vendor;
    this->type = other.type;
    this->location = other.location;
    this->instance = other.instance;
    this->pinId = other.pinId;
    this->pinType = other.pinType;
    return *this;
}

//----------------------------------------------------------------------------

bool operator==(const Device& a, const Device& b) {
    return a.isEqual(b);
}

//----------------------------------------------------------------------------

QString Device::toString() const {
    QString s = "";
    s += "\t[device]\n";
    s += "\t"+vendor + "." + type + "." + location + (instance.isEmpty() ? "" : ":"+instance) + "\n";
    s += "\tpintype: "+pinType+"\n";
    s += "\tpinid: "+pinId+"\n";
    return s;
}


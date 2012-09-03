#include "GenAddress.h"

GenAddress::GenAddress()
{
}

GenAddress::GenAddress(const QString &vendor, const QString &type, const QString &location, const QString &instance) {
    this->vendor = vendor;
    this->type = type;
    this->location = location;
    this->instance = instance;
}

GenAddress::GenAddress(const GenAddress &other) {
    this->vendor = other.vendor;
    this->type = other.type;
    this->location = other.location;
    this->instance = other.instance;
}

bool GenAddress::isEqual(const GenAddress &other) const {
    return (this->vendor == other.vendor
            && this->type == other.type
            && this->location == other.location
            && this->instance == other.instance);
}

GenAddress& GenAddress::operator =(const GenAddress& other) {
    this->vendor = other.vendor;
    this->type = other.type;
    this->location = other.location;
    this->instance = other.instance;
    return *this;
}

QString GenAddress::toString() const {
    QString rslt = "";
    // <network>/<type>@<location>:<instance>
    rslt += getVendor()+"/"+getType()+"@"+getLocation()+":"+getInstance();
    return rslt;
}

bool operator==(const GenAddress& a, const GenAddress& b) {
    return a.isEqual(b);
}

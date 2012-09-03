#include "AbstractApplication.h"

AbstractApplication::AbstractApplication() {

}

AbstractApplication::AbstractApplication(const QString &vendor, const QString &type, const QString &location, const QString &instance)
{
    address.setVendor(vendor);
    address.setType(type);
    address.setLocation(location);
    address.setInstance(instance);
}

AbstractApplication::AbstractApplication(const GenAddress &address) {
    this->address = address;
}

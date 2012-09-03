#ifndef ABSTRACTAPPLICATION_H
#define ABSTRACTAPPLICATION_H

#include <QString>
#include <com/common/GenAddress.h>

class AbstractApplication
{
private:
    GenAddress address;

public:
    AbstractApplication();

    AbstractApplication(const QString& vendor, const QString& type, const QString& location, const QString& instance = "");

    AbstractApplication(const GenAddress& address);

    const GenAddress& getAddress() const { return address; }

    void setAddress(const GenAddress& address) { this->address = address; }

    virtual void initializeApplication() = 0;
};

#endif // ABSTRACTAPPLICATION_H

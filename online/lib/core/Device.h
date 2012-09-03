#ifndef DEVICE_H
#define DEVICE_H

#include <QString>

class Module;

/**
    @todo Device class documentation
  */
class Device
{
private:
    /**

      */
    QString pinType;

    /**

      */
    QString pinId;

    /**

      */
    QString type;

    /**

      */
    QString vendor;

    /**

      */
    QString location;

    /**

      */
    QString instance;

    /**

      */
    Module* module;


public:
    /**

      */
    Device();

    /**

      */
    Device(const QString& vendor, const QString& type, const QString& location, const QString& instance = "");

    /**

      */
    Device(const QString& pinType, const QString& pinId);

    /**

      */
    Device(const Device& other);

    /**

      */
    bool isEqual(const Device& other) const;

    /**

      */
    Device& operator=(const Device& other);

    /**

      */
    const QString& getType() const { return type; }

    /**

      */
    void setType(const QString& type) { this->type = type; }

    /**

      */
    const QString& getVendor() const { return vendor; }

    /**

      */
    void setVendor(const QString& vendor) { this->vendor = vendor; }

    /**

      */
    const QString& getLocation() const { return location; }

    /**

      */
    void setLocation(const QString &location) { this->location = location; }

    /**

      */
    const QString& getInstance() const { return this->instance; }

    /**

      */
    void setInstance(const QString& instance) { this->instance = instance; }

    /**

      */
    const QString& getPinType() const { return pinType; }

    /**

      */
    void setPinType(const QString& type) { this->pinType = type; }

    /**

      */
    const QString& getPinId() const { return pinId; }

    /**

      */
    void setPinId(const QString& num) { this->pinId = num; }

    /**

      */
    QString toString() const;

    /**

      */
    Module* getPtrModule() { return module; }

    /**

      */
    void setPtrModule(Module* ptr) { this->module = ptr; }
};


bool operator==(const Device& a, const Device& b);

#endif // DEVICE_H

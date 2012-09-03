#ifndef GENADDRESS_H
#define GENADDRESS_H

#include <QString>

/**

  */
class GenAddress
{
private:
    /**

      */
    QString vendor;

    /**

      */
    QString location;

    /**

      */
    QString type;

    /**

      */
    QString instance;

public:
    /**

      */
    GenAddress();

    /**

      */
    GenAddress(const QString& vendor, const QString& type, const QString& location, const QString& instance = "");

    /**

      */
    GenAddress(const GenAddress& other);

    /**

      */
    GenAddress& operator=(const GenAddress& other);

    /**

      */
    bool isEqual(const GenAddress& other) const;

    /**

      */
    QString toString() const;

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
    void setLocation(const QString& location) { this->location = location; }

    /**

      */
    const QString& getType() const { return type; }

    /**

      */
    void setType(const QString& type) { this->type = type; }

    /**

      */
    const QString& getInstance() const { return instance; }

    /**

      */
    void setInstance(const QString& instance) { this->instance = instance; }
};

bool operator==(const GenAddress& a, const GenAddress& b);

#endif // GENADDRESS_H

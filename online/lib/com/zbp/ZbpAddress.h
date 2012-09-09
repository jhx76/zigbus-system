#ifndef ZBPADDRESS_H
#define ZBPADDRESS_H

#include <com/zbp/zigbus.h>
#include <QString>

/**

  */
class ZbpAddress
{
private:
    /**

      */
    int moduleAddress;//2 digits

    /**

      */
    int networkAddress; //4 digits
public:
    /**

      */
    ZbpAddress();

    /**

      */
    ZbpAddress(int inetwork, int iaddress);

    /**

      */
    ZbpAddress(const QString& str);

    /**

      */
    ZbpAddress(const ZbpAddress& other);

    /**

      */
    ZbpAddress& operator=(const ZbpAddress& other);

    /**

      */
    bool isEqual(const ZbpAddress& other) const;


    /**

      */
    QString toTrame() const;

    /**

      */
    int getModuleAddress() const { return moduleAddress; }

    /**

      */
    void setModuleAddress(int address) { moduleAddress= address; }

    /**

      */
    int getNetworkAddress() const { return networkAddress; }

    /**

      */
    void setNetworkAddress(int address) { networkAddress = address; }
};

/**

  */
bool operator==(const ZbpAddress& a, const ZbpAddress& b);
#endif // ZBPADDRESS_H

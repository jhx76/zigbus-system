#ifndef ZBPADDRESS_H
#define ZBPADDRESS_H

#include <com/zbp/zigbus.h>
#include <QString>


/*
    This file is part of Zigbus Home Automation API. 
    Copyright (C) 2012 jhx

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

using namespace zigbus;

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

    /**

      */
    QString mainPin;

    /**

      */
    QString optionalPin;

    /**

      */
    ZigbusDeviceType hardwareType;

    /**

      */
    ZigbusSubType subType;

public:
    /**

      */
    ZbpAddress();

    /**

      */
    ZbpAddress(int inetwork, int iaddress, const QString& mainPin, const QString& optionalPin = "");

    /**

      */
    ZbpAddress(const QString& str, const QString& mainPin = "", const QString& optionalPin = "");

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

    const QString& getMainPin() const { return mainPin; }

    void setMainPin(const QString& pin) { this->mainPin = pin; }

    const QString& getOptionalPin() const { return this->optionalPin; }

    void setOptionalPin(const QString& optionalPin) { this->optionalPin = optionalPin; }

    ZigbusDeviceType getHardwareType() const { return hardwareType; }

    void setHardwareType(ZigbusDeviceType type) { hardwareType = type; }

    ZigbusSubType getSubType() const { return subType; }

    void setSubType(ZigbusSubType stype) { subType = stype; }
};

/**

  */
bool operator==(const ZbpAddress& a, const ZbpAddress& b);
#endif // ZBPADDRESS_H

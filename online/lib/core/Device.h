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

#ifndef DEVICE_H
#define DEVICE_H

#include <QString>
#include <com/common/GenAddress.h>
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
    QString optionalId;

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
    Device(const QString& pinType, const QString& pinId, const QString& optionalId = "");

    /**

      */
    Device(const Device& other);

    /**

      */
    ~Device() {
        module = NULL;
    }

    GenAddress getGenericAddress() const {
        GenAddress a(getVendor(), getType(), getLocation(), getInstance());
        return a;
    }


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
    const QString& getOptionalId() const { return optionalId; }

    /**

      */
    void setOptionalId(const QString& optionalId) { this->optionalId = optionalId; }

    /**

      */
    QString toString() const;

    /**

      */
    Module* getPtrModule() const { return module; }

    /**

      */
    void setPtrModule(Module* ptr) { this->module = ptr; }
};


bool operator==(const Device& a, const Device& b);

#endif // DEVICE_H

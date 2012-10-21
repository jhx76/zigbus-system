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

#ifndef GENADDRESS_H
#define GENADDRESS_H

#include <QString>

/**
exemple address device:
    vendor = zigbus-dev
    type = lampe
    location = salon
    instance = 2
  => zigbus-dev.lampe.salon:2 (xap)

exemple address module:
    vendor = zigbus-dev
    type = module
    location = 00
    instance = 0134
  => zigbus-dev.module.00:0134

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

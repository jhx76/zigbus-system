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

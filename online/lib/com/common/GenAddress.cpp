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
    // <network>.<type>.<location>:<instance>
    return getVendor()+"."+getType()+"."+getLocation()+":"+getInstance();
}

bool operator==(const GenAddress& a, const GenAddress& b) {
    return a.isEqual(b);
}

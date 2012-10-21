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

#include "Device.h"
#include <core/Module.h>
Device::Device()
{
    this->vendor = "";
    this->type = "";
    this->location = "";
    this->instance = "";
    this->pinId = "";
    this->optionalId = "";
    this->pinType = "";
    this->module = NULL;
}

//----------------------------------------------------------------------------

Device::Device(const QString &vendor, const QString &type, const QString &location, const QString &instance)
{
    this->vendor = vendor;
    this->type = type;
    this->location = location;
    this->instance = instance;
    this->pinId = "";
    this->optionalId = "";
    this->pinType = "";
    this->module = NULL;
}

//----------------------------------------------------------------------------

Device::Device(const QString &pinType, const QString &pinId, const QString& optionalId) {
    this->vendor = vendor;
    this->type = type;
    this->location = location;
    this->instance = instance;
    this->pinId = pinId;
    this->optionalId = optionalId;
    this->pinType = pinType;
    this->module = NULL;
}

//----------------------------------------------------------------------------

Device::Device(const Device &other) {
    this->vendor = other.vendor;
    this->type = other.type;
    this->location = other.location;
    this->instance = other.instance;
    this->pinId = other.pinId;
    this->optionalId = other.optionalId;
    this->pinType = other.pinType;
    this->module = other.module;
}

//----------------------------------------------------------------------------

bool Device::isEqual(const Device &other) const {
    return (this->vendor == other.vendor && this->type == other.type && this->location == other.location
            && this->instance == other.instance && this->optionalId == optionalId
            && this->pinId == other.pinId && this->pinType == other.pinType);
}

//----------------------------------------------------------------------------

Device& Device::operator =(const Device& other) {
    this->vendor = other.vendor;
    this->type = other.type;
    this->location = other.location;
    this->instance = other.instance;
    this->pinId = other.pinId;
    this->optionalId = other.optionalId;
    this->pinType = other.pinType;
    this->module = other.module;
    return *this;
}

//----------------------------------------------------------------------------

bool operator==(const Device& a, const Device& b) {
    return a.isEqual(b);
}

//----------------------------------------------------------------------------

QString Device::toString() const {
    QString s = "";
    s += "\t[device]\n";
    s += "\t"+vendor + "." + type + "." + location + (instance.isEmpty() ? "" : ":"+instance) + "\n";
    s+= "\tmodule: "+this->getPtrModule()->getLabel()+"\n";
    s += "\tpintype: "+pinType+"\n";
    s += "\tpinid: "+pinId+"\n";
    s += (optionalId.isEmpty() ? ""
         : "\toptionalId: "+optionalId+"\n");
    return s;
}


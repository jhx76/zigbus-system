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

#include "Module.h"

Module::Module()
{
    this->label = "[nihil]";
    this->numericIOCount = 0;
    this->analogIOCount = 0;
    this->zigbusNetworkId = "00";
}

//----------------------------------------------------------------------------

Module::Module(const QString &label, int analogicIOCount, int numericIOCount, const QString& zigbusNetworkId) {
    this->label = label;
    this->analogIOCount = analogicIOCount;
    this->numericIOCount = numericIOCount;
    this->zigbusNetworkId = zigbusNetworkId;
}

//----------------------------------------------------------------------------

Module::Module(const Module &other) {
    this->label = other.label;
    this->analogIOCount = other.analogIOCount;
    this->numericIOCount = other.numericIOCount;
    this->zigbusNetworkId = other.zigbusNetworkId;
    for(int i = 0; i < other.deviceCount(); i++) {
        Device d(other.deviceList[i]);
        this->append(d);
    }
}

//----------------------------------------------------------------------------

QString Module::toString() const {
    QString s = "";
    s += "label: "+this->label+"\n";
    s += "netid: "+zigbusNetworkId+"\n";
    s += "numeric count: " +QString::number(this->numericIOCount)+"\n";
    s += "analogic count: "+QString::number(this->analogIOCount)+"\n";
    for(int i = 0; i < deviceCount(); i++)
        s += deviceList.at(i).toString();
    return s;
}

/*
    This file is part of Zigbus Home Automation API. 
    More information about this project at <http://www.zigbus.com/>
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

#ifndef MODULE_H
#define MODULE_H

#include <QString>
#include <QList>
#include <QVariant>
#include "Device.h"

/**

  @todo Module class documentation
  */
class Module
{

private:
    /**

      */
    QString label;

    /**

      */
    int analogIOCount;

    /**

      */
    int numericIOCount;

    /**

      */
    QString zigbusNetworkId;

    /**

      */
    QList<Device> deviceList;

public:
    /**

      */
    Module();

    /**

      */
    Module(const QString& label, int analogicIOCount = 10, int numericIOCount = 10, const QString & zigbusNetworkId = "");

    /**

      */
    Module(const Module& other);

    /**

      */
    ~Module() { }

    /**

      */
    void append(const Device& device) {
        this->deviceList.append(device);
    }

    /**

      */
    int deviceCount() const { return deviceList.count(); }

    /**

      */
    void removeAt(int index) { deviceList.removeAt(index); }

    /**

      */
    Device& elementAt(int index) { return deviceList[index]; }

    /**

      */
    const Device& at(int index) { return deviceList.at(index); }

    /**

      */
    const QString& getLabel() const { return label; }

    /**

      */
    void setLabel(const QString& label) { this->label = label; }

    /**

      */
    int getAnalogIOCount() const { return analogIOCount; }

    /**

      */
    void setAnalogIOCount(int count) { this->analogIOCount = count; }

    /**

      */
    int getNumericIOCount() const { return numericIOCount; }

    /**

      */
    void setNumericIOCount(int count) { this->numericIOCount = count; }

    /**

      */
    const QString& getZigbusNetworkId() const { return zigbusNetworkId; }

    /**

      */
    void setZigbusNetworkId(const QString& id) { this->zigbusNetworkId = id; }

    /**

      */
    QString toString() const;

};
Q_DECLARE_METATYPE(Device)
Q_DECLARE_METATYPE(Module)


#endif // MODULE_H

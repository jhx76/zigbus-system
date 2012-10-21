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

#ifndef COMMANDMESSAGE_H
#define COMMANDMESSAGE_H

#include <com/common/GenMessage.h>
#include <QList>

using namespace gen;

/**

exemple config mod00:0134 S4 temperature:

xap-header
{
v=12
hop=1
uid=000134FF
class=xapbsc.command
source=zigbus-dev.controller.cartman
target=zigbus-dev.module.00:134
}
configuration
{
id=S4
type=temperature
stype=DHT11
}


exemple set on lampe 2 salon pendant 1min:
xap-header
{
v=12
hop=1
uid=000134FF
class=xapbsc.command
source=zigbus-dev.controller.cartman
target=zigbus-dev.lampe.salon:2
}
output.state
{
state=ON
time=1
unit=m
}
  */

#define CMD_CONFIGIRATION "configuration"
#define CMD_OUPTUT_STATE "output.state"

class CommandMessage : public GenMessage
{
private:
    /**

      */
    GenAddress target;

    /**

      */
    QString commandType;

    /**

      */
    QList<Param> paramList;

    QString defaultReturn;

public:
    /**

      */
    CommandMessage(const GenAddress& source, const GenAddress& target);

    /**

      */
    CommandMessage(const CommandMessage& other);

    /**

      */
    const QString& getParam(ParamKey key) const;

    /**

      */
    void setParam(ParamKey key, const QString& value);

    /**

      */
    bool contains(ParamKey key) const;

    /**

      */
    gen::Param& elementAt(int i);

    /**

      */
    const gen::Param& at(int i) const;

    /**

      */
    void append(const gen::Param& param);

    /**

      */
    void removeAt(int i);

    /**

      */
    int paramCount() const;

    /**

      */
    bool isEmpty() const;

    /**

      */
    void clear();

    /**

      */
    virtual QString toString() const;

    /**

      */
    const GenAddress& getTarget() const { return target; }

    /**

      */
    void setTarget(const GenAddress& target) { this->target = target; }

    /**

      */
    const QString& getCommandType() const { return commandType; }

    /**

      */
    void setCommandType(const QString& commandType) { this->commandType = commandType; }
};

#endif // COMMANDMESSAGE_H

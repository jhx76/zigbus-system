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

#ifndef EVENTMESSAGE_H
#define EVENTMESSAGE_H

#include <QList>
#include <com/common/GenAddress.h>
#include <com/common/GenMessage.h>

using namespace gen;

/**

  */
class EventMessage : public GenMessage
{
private:
    /**

      */
    QList<Param> paramList;

    QString typeEvent;

public:
    /**

      */
    EventMessage(const GenAddress& source);

    /**

      */
    EventMessage(const EventMessage& other);

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

    const QString& getTypeEvent() const { return typeEvent; }

    void setTypeEvent(const QString& type) { typeEvent = type; }

};

#endif // EVENTMESSAGE_H

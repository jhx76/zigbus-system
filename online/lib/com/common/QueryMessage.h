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

#ifndef QUERYMESSAGE_H
#define QUERYMESSAGE_H

#include <com/common/GenMessage.h>

#include <QList>

using namespace gen;

/**
  @class QueryMessage
  @author jhx
  @date

  @brief
  */
class QueryMessage : public GenMessage
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

    /**

      */
    QString defaultReturn;

public:
    /**

      */
    QueryMessage(const GenAddress& source, const GenAddress& target);

    /**

      */
    QueryMessage(const QueryMessage& other);

    /**

      */
    const GenAddress& getTarget() const { return target; }

    /**

      */
    void setTarget(const GenAddress& target) { this->target = target; }


    /**

      */
    virtual QString toString() const;

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
    const QString& getCommandType() const { return commandType; }

    /**

      */
    void setCommandType(const QString& type) { commandType = type; }


};

#endif // QUERYMESSAGE_H

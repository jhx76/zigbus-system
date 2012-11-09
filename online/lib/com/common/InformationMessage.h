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

#ifndef INFORMATIONMESSAGE_H
#define INFORMATIONMESSAGE_H

#include <com/common/GenMessage.h>
#include <QList>

/**
  @class InformationMessage
  @author jhx
  @date
  @brief InformationMessage class allows you to manage information messages in your application.
  */
class InformationMessage : public GenMessage
{
private:
    /**

      */
    QList<gen::Param> paramList;

    /**

      */
    QString typeInfo;

public:
    /**

      */
    InformationMessage(const GenAddress& source);

    /**

      */
    InformationMessage(const InformationMessage& other);

    /**

      */
    const QString& getParam(gen::ParamKey key) const;

    /**

      */
    void setParam(gen::ParamKey key, const QString& value);

    /**

      */
    bool contains(gen::ParamKey key) const;

    /**

      */
    int paramCount() const;

    /**

      */
    const gen::Param& at(int i) const;

    /**

      */
    gen::Param& elementAt(int i);

    /**

      */
    void append(const gen::Param& param);

    /**

      */
    void removeAt(int i);

    /**

      */
    void clear();

    /**

      */
    bool isEmpty() const;

    /**

      */
    virtual QString toString() const;

    /**

      */
    const QString& getTypeInfo() const { return typeInfo; }

    /**

      */
    void setTypeInfo(const QString& typeInfo) { this->typeInfo = typeInfo; }
};

#endif // INFORMATIONMESSAGE_H

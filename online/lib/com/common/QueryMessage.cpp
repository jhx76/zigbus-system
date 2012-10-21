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

#include "QueryMessage.h"

QueryMessage::QueryMessage(const GenAddress &source, const GenAddress &target) : GenMessage(source, Query) {
    defaultReturn = "";
    this->target = target;
}

QueryMessage::QueryMessage(const QueryMessage &other) : GenMessage(other){
    defaultReturn = "";
    this->target = other.target;
    for(int i = 0; i < other.paramList.count(); i++) {
        paramList[i].key = other.paramList[i].key;
        paramList[i].value = other.paramList[i].value;
    }
}

const QString& QueryMessage::getParam(ParamKey key) const {
    for(int i = 0; i < this->paramList.count(); i++) {
        if(paramList[i].key == key) {
            return paramList[i].value;
        }
    }
    return defaultReturn;
}

void QueryMessage::setParam(ParamKey key, const QString &value) {
    for(int i = 0; i < paramList.count(); i++) {
        if(paramList[i].key == key) {
            paramList[i].value = value;
            return;
        }
    }
    Param tmpParam;
    tmpParam.key = key;
    tmpParam.value = value;
    this->paramList.append(tmpParam);
}

bool QueryMessage::contains(ParamKey key) const {
    for(int i = 0; i < paramList.count(); i++)
      if(paramList[i].key == key)
            return true;
    return false;
}

bool QueryMessage::isEmpty() const {
    return paramList.isEmpty();
}

int QueryMessage::paramCount() const {
    return paramList.count();
}

gen::Param& QueryMessage::elementAt(int i) {
    return paramList[i];
}

const gen::Param& QueryMessage::at(int i) const {
    return paramList.at(i);
}

void QueryMessage::append(const gen::Param &param) {
    paramList.append(param);
}

void QueryMessage::removeAt(int i) {
    paramList.removeAt(i);
}

void QueryMessage::clear() {
    while(!paramList.isEmpty()) {
        paramList.takeFirst();
    }
}
QString QueryMessage::toString() const {
    QString rslt = "";
    rslt += "$QUERY\n";
    rslt += "source="+source.toString()+"\n";
    rslt += "target="+target.toString()+"\n";
    return rslt;
}

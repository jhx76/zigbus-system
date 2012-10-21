
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

#include "InformationMessage.h"

InformationMessage::InformationMessage(const GenAddress& source) : GenMessage(source, GenMessage::Information)
{

}

InformationMessage::InformationMessage(const InformationMessage &other) : GenMessage(other) {
    for(int i = 0; i < other.paramList.count(); i++) {
        paramList.append(other.paramList[i]);
    }
}


const QString& InformationMessage::getParam(gen::ParamKey key) const {
    for(int i = 0; i < paramList.count(); i++) {
        if(paramList.at(i).key == key) {
            return paramList.at(i).value;
        }
    }
}

void InformationMessage::setParam(gen::ParamKey key, const QString &value) {
    for(int i = 0; i < paramList.count(); i++) {
        if(paramList.at(i).key == key) {
            paramList[i].value = value;
            return;
        }
    }
    gen::Param param;
    param.key = key;
    param.value = value;
    paramList.append(param);
}

bool InformationMessage::contains(gen::ParamKey key) const {
    for(int i = 0; i < paramList.count(); i++) {
        if(paramList[i].key == key)
            return true;
    }
    return false;
}


int InformationMessage::paramCount() const {
    return paramList.count();
}

const gen::Param& InformationMessage::at(int i) const {
    return paramList.at(i);
}

gen::Param& InformationMessage::elementAt(int i) {
    return paramList[i];
}

void InformationMessage::append(const gen::Param &param) {
    paramList.append(param);
}

void InformationMessage::removeAt(int i) {
    paramList.removeAt(i);
}

void InformationMessage::clear() {
    while(!paramList.isEmpty()) {
        paramList.takeFirst();
    }
}

bool InformationMessage::isEmpty() const {
    return paramList.isEmpty();
}

QString InformationMessage::toString() const {
    QString rslt = "";
    rslt += "$INFORMATION\n";
    rslt += "source="+source.toString()+"\n";
    for(int i = 0; i < paramList.count(); i++) {
        rslt += paramKeyAsString(paramList.at(i).key)+"="+paramList.at(i).value+"\n";
    }
    return rslt;
}


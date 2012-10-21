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


#include "CommandMessage.h"

CommandMessage::CommandMessage(const GenAddress &source, const GenAddress &target) : GenMessage(source, Command) {
    defaultReturn = "";
    this->target = target;
}

CommandMessage::CommandMessage(const CommandMessage &other) : GenMessage(other){
    defaultReturn = "";
    this->target = other.target;
    for(int i = 0; i < other.paramList.count(); i++) {
        paramList[i].key = other.paramList[i].key;
        paramList[i].value = other.paramList[i].value;
    }
}

const QString& CommandMessage::getParam(ParamKey key) const {
    for(int i = 0; i < this->paramList.count(); i++) {
        if(paramList[i].key == key) {
            return paramList[i].value;
        }
    }
    return defaultReturn;
}

void CommandMessage::setParam(ParamKey key, const QString &value) {
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

bool CommandMessage::contains(ParamKey key) const {
    for(int i = 0; i < paramList.count(); i++)
      if(paramList[i].key == key)
            return true;
    return false;
}

bool CommandMessage::isEmpty() const {
    return paramList.isEmpty();
}

int CommandMessage::paramCount() const {
    return paramList.count();
}

gen::Param& CommandMessage::elementAt(int i) {
    return paramList[i];
}

const gen::Param& CommandMessage::at(int i) const {
    return paramList.at(i);
}

void CommandMessage::append(const gen::Param &param) {
    paramList.append(param);
}

void CommandMessage::removeAt(int i) {
    paramList.removeAt(i);
}

void CommandMessage::clear() {
    while(!paramList.isEmpty()) {
        paramList.takeFirst();
    }
}

QString CommandMessage::toString() const{
    QString rslt = "";
    rslt += "$COMMAND\n";
    rslt += "source="+source.toString()+"\n";
    rslt += "target="+target.toString()+"\n";
    rslt += "cmd="+this->commandType+"\n";
    for(int i = 0; i < paramList.count(); i++) {
        rslt += paramKeyAsString(paramList.at(i).key);
        rslt += "=";
        rslt += paramList.at(i).value;
        rslt +="\n";
    }

    return rslt;
}

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

#include "EventMessage.h"

EventMessage::EventMessage(const GenAddress &source) : GenMessage(source, GenMessage::Event) {
    typeEvent = "";
}

EventMessage::EventMessage(const EventMessage &other) : GenMessage(other) {
    typeEvent = other.typeEvent;
}


const QString& EventMessage::getParam(ParamKey key) const {
    for(int i = 0; i < paramList.count(); i++) {
        if(paramList.at(i).key == key) {
            return paramList.at(i).value;
        }
    }
    return "";
}

void EventMessage::setParam(ParamKey key, const QString &value) {
    for(int i = 0; i < paramList.count(); i++) {
        if(paramList.at(i).key == key ) {
            paramList[i].value = value;
            return;
        }
    }
    Param param;
    param.key = key;
    param.value = value;
    paramList.append(param);

}

bool EventMessage::contains(ParamKey key) const {
    for(int i = 0; i < paramList.count(); i++) {
        if(paramList.at(i).key == key) {
            return true;
        }
    }
    return false;
}

Param& EventMessage::elementAt(int i) {
    return paramList[i];
}

const Param& EventMessage::at(int i) const {
    return paramList.at(i);
}

int EventMessage::paramCount() const  {
    return paramList.count();
}

void EventMessage::append(const gen::Param &param) {
    if(!this->contains(param.key))
        paramList.append(param);
    else
        qDebug() << "param already exists in the message";
}

void EventMessage::removeAt(int i) {
    paramList.removeAt(i);
}

void EventMessage::clear() {
    while(!paramList.isEmpty())
        paramList.takeFirst();
}

bool EventMessage::isEmpty() const {
    return paramList.isEmpty();
}

QString EventMessage::toString() const {
    QString rslt = "";
    rslt += "$EVENT\n";
    rslt += "type="+typeEvent+"\n";
    rslt += "source="+source.toString()+"\n";
    for(int i = 0; i < paramList.count(); i++) {
        rslt += paramKeyAsString(paramList.at(i).key)+"="+paramList.at(i).value+"\n";
    }
    return rslt;
}


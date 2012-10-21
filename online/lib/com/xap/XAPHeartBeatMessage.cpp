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

#include "XAPHeartBeatMessage.h"

XAPHeartBeatMessage::XAPHeartBeatMessage(const QString &xapsource, const QString &uid, int hop, const QString &version) :
    XAPMessage("xap-hbeat.alive", xapsource, "", uid, hop, version)
{
    getHeader().setBlockname("xap-hbeat");
    getHeader().append("interval", "");
    getHeader().append("port", "");
}

//----------------------------------------------------------------------------

XAPHeartBeatMessage::XAPHeartBeatMessage(const XAPHeartBeatMessage &other) :
    XAPMessage(other)
{
    getHeader().setBlockname("xap-hbeat");
}

//----------------------------------------------------------------------------

XAPHeartBeatMessage::~XAPHeartBeatMessage() {

}

//----------------------------------------------------------------------------

QString XAPHeartBeatMessage::toString() const {
    QString result = "";
    result += this->header->toString();
    return result;
}

//----------------------------------------------------------------------------

void XAPHeartBeatMessage::setPort(int i) {
    port = i;
    int index = getHeader().indexOf("port");
    if(index == -1)
        getHeader().append("port", QString::number(port));
    else
        getHeader().elementAt(index).setValue(QString::number(port));
}

//----------------------------------------------------------------------------

void XAPHeartBeatMessage::setInterval(int i) {
    interval = i;
    int index = getHeader().indexOf("interval");
    if(index == 0)
        getHeader().append("interval", QString::number(interval));
    else
        getHeader().elementAt(index).setValue(QString::number(interval));

}

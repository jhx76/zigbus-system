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


#include "HeartBeatMessage.h"

HeartBeatMessage::HeartBeatMessage(const GenAddress& source) : GenMessage(source, GenMessage::HeartBeat)
{
    port = -1;
    pid = -1;
    interval = -1;
}



HeartBeatMessage::HeartBeatMessage(const HeartBeatMessage &other) : GenMessage(other)
{
    this->port = other.port;
    this->pid = other.pid;
    this->interval = other.interval;
}

HeartBeatMessage::HeartBeatMessage(const GenAddress &source, int port, int interval, int pid)
    : GenMessage(source, GenMessage::HeartBeat)
{
    this->port = port;
    this->pid = pid;
    this->interval = interval;
}

QString HeartBeatMessage::toString() const {
    QString rslt = "";
    rslt += "$HEARTBEAT\n";
    rslt += "source="+source.toString()+"\n";
    rslt += "interval="+QString::number(interval)+"\n";
    rslt += "port="+QString::number(port)+"\n";
    rslt += "pid="+QString::number(pid)+"\n";
    return rslt;
}

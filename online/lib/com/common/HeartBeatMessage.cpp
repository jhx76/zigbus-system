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

QString HeartBeatMessage::toString() {
    QString rslt = "";
    rslt += "$HEARTBEAT\n";
    rslt += "source="+source.toString()+"\n";
    rslt += "interval="+QString::number(interval)+"\n";
    rslt += "port="+QString::number(port)+"\n";
    rslt += "pid="+QString::number(pid)+"\n";
    return rslt;
}

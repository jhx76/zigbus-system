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

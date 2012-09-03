#include "GenMessageFactory.h"

GenMessage* GenMessageFactory::createMessage(ZbpMessage &message) {
    return NULL;
}

//------------------------------------------------------------

GenMessage* GenMessageFactory::createMessage(XAPMessage &message) {
    if(message.getVersion() == "12") {
        if(message.getClass() == "xapbsc.cmd") {
            return createCommandMessage(message);
        }
        else if(message.getClass() == "xapbsc.info") {
            return createInformationMessage(message);
        }
        else if(message.getClass() == "xapbsc.event") {
            return createEventMessage(message);
        }
        else if(message.getClass() == "xapbsc.query") {
            return createQueryMessage(message);
        }
        /*else if(message.getClass() == "zb.ping") {
            return createPingMessage(message);
        }
        else if(message.getClass() == "zb.pingresult") {
            return createPingResultMessage(message);
        }
        else if(message.getClass() == "zb.initialize") {
            return createInitializationMessage(message);
        }
        else if(message.getClass() == "zb.configure") {
            return createConfigturationMessage(message);
        }*/
        else if(message.getClass() == "xap-hbeat.alive") {
            return createHeartBeatMessage(message);
        }
        else
            throw error::SysException("error: unknown xapclass ("+message.getClass()+")");
    }
    else
        throw error::SysException("error: bad version (" + message.getVersion() + ")");
    return NULL;
}

//------------------------------------------------------------

CommandMessage* GenMessageFactory::createCommandMessage(ZbpMessage &message) {
    return NULL;
}

//------------------------------------------------------------

CommandMessage* GenMessageFactory::createCommandMessage(XAPMessage &message) {
    GenAddress source;
    GenAddress target;
    CommandMessage* rsltMessage = NULL;
    try {
        source = GenAddress(message.getXAPSource().getVendor(),
                          message.getXAPSource().getType(),
                          message.getXAPSource().getLocation(),
                          message.getXAPSource().getInstance());
        target = GenAddress(message.getXAPTarget().getVendor(),
                          message.getXAPTarget().getType(),
                          message.getXAPTarget().getLocation(),
                          message.getXAPTarget().getInstance());
        rsltMessage = new CommandMessage(source, target);
    }
    catch(const error::SysException& exception) {
        qDebug() << exception.getMessage();
    }

    for(int i = 0; i < message.count(); i++) {

        if(message.at(i).getBlockname() == "cmd") {

            for(int i2 = 0; i2 < message.at(i).count(); i2++) {
                XAPNameValuePair nvpair = message.at(i).at(i2);
                if(nvpair.getName() == "state") {
                    if(nvpair.getValue() == "on")
                        rsltMessage->setParam(gen::state, "on");
                    else if(nvpair.getValue() == "off")
                        rsltMessage->setParam(gen::state, "off");
                }
                else if(nvpair.getName() == "time") {
                    rsltMessage->setParam(gen::time, nvpair.getValue());
                    for(int i3 = 0; i3 < message.at(i).count(); i3++) {
                        XAPNameValuePair nvunit = message.at(i).at(i3);
                        if(nvunit.getName() == "unit")
                            rsltMessage->setParam(gen::unit, nvunit.getValue());
                    }
                }
                else if(nvpair.getName() == "text") {
                    rsltMessage->setParam(gen::text, nvpair.getValue());
                }
                else if(nvpair.getName() == "level"){
                    rsltMessage->setParam(gen::level, nvpair.getValue());
                }
                else if(nvpair.getName() == "displaytext") {
                    rsltMessage->setParam(gen::displaytext, nvpair.getValue());
                }
                else {

                }
            }
        }
    }
    return rsltMessage;
}

//------------------------------------------------------------

QueryMessage* GenMessageFactory::createQueryMessage(XAPMessage &message) {

    GenAddress source;
    GenAddress target;
    QueryMessage* rsltMessage = NULL;
    try {
        source = GenAddress(message.getXAPSource().getVendor(),
                          message.getXAPSource().getType(),
                          message.getXAPSource().getLocation(),
                          message.getXAPSource().getInstance());
        target = GenAddress(message.getXAPTarget().getVendor(),
                          message.getXAPTarget().getType(),
                          message.getXAPTarget().getLocation(),
                          message.getXAPTarget().getInstance());
        rsltMessage = new QueryMessage(source, target);
    }
    catch(const error::SysException& exception) {
        qDebug() << exception.getMessage();
    }
    return rsltMessage;
}

//------------------------------------------------------------

QueryMessage* GenMessageFactory::createQueryMessage(ZbpMessage &message) {
    return NULL;
}

//------------------------------------------------------------

InformationMessage* GenMessageFactory::createInformationMessage(XAPMessage &message) {
    GenAddress source;
    InformationMessage* rsltMessage = NULL;
    try {
        source = GenAddress(message.getXAPSource().getVendor(),
                      message.getXAPSource().getType(),
                      message.getXAPSource().getLocation(),
                      message.getXAPSource().getInstance());
        rsltMessage = new InformationMessage(source);
    }
    catch(const error::SysException& e) {
        qDebug() << e.getMessage();
    }

    for(int i = 0; i < message.count(); i++) {

        if(message.at(i).getBlockname() == "info") {

            for(int i2 = 0; i2 < message.at(i).count(); i2++) {
                XAPNameValuePair nvpair = message.at(i).at(i2);
                if(nvpair.getName() == "state") {
                    if(nvpair.getValue() == "on")
                        rsltMessage->setParam(gen::state, "on");
                    else if(nvpair.getValue() == "off")
                        rsltMessage->setParam(gen::state, "off");
                }
                else if(nvpair.getName() == "time") {
                    rsltMessage->setParam(gen::time, nvpair.getValue());
                    for(int i3 = 0; i3 < message.at(i).count(); i3++) {
                        XAPNameValuePair nvunit = message.at(i).at(i3);
                        if(nvunit.getName() == "unit")
                            rsltMessage->setParam(gen::unit, nvunit.getValue());
                    }
                }
                else if(nvpair.getName() == "text") {
                    rsltMessage->setParam(gen::text, nvpair.getValue());
                }
                else if(nvpair.getName() == "level"){
                    rsltMessage->setParam(gen::level, nvpair.getValue());
                }
                else if(nvpair.getName() == "displaytext") {
                    rsltMessage->setParam(gen::displaytext, nvpair.getValue());
                }
                else {

                }
            }
        }
    }
    return rsltMessage;
}

//------------------------------------------------------------

InformationMessage* GenMessageFactory::createInformationMessage(ZbpMessage &message) {


    return NULL;
}

//------------------------------------------------------------

EventMessage* GenMessageFactory::createEventMessage(XAPMessage &message) {
    GenAddress source;
    EventMessage* rsltMessage = NULL;
    try {
        source = GenAddress(message.getXAPSource().getVendor(),
                      message.getXAPSource().getType(),
                      message.getXAPSource().getLocation(),
                      message.getXAPSource().getInstance());
        rsltMessage = new EventMessage(source);
    }
    catch(const error::SysException& e) {
        qDebug() << e.getMessage();
    }

    for(int i = 0; i < message.count(); i++) {
        if(message.at(i).getBlockname() == "event") {
            for(int i2 = 0; i2 < message.at(i).count(); i2++) {
                XAPNameValuePair nvpair = message.at(i).at(i2);
                if(nvpair.getName() == "state") {
                    if(nvpair.getValue() == "on")
                        rsltMessage->setParam(gen::state, "on");
                    else if(nvpair.getValue() == "off")
                        rsltMessage->setParam(gen::state, "off");
                }
                else if(nvpair.getName() == "time") {
                    rsltMessage->setParam(gen::time, nvpair.getValue());
                    for(int i3 = 0; i3 < message.at(i).count(); i3++) {
                        XAPNameValuePair nvunit = message.at(i).at(i3);
                        if(nvunit.getName() == "unit")
                            rsltMessage->setParam(gen::unit, nvunit.getValue());
                    }
                }
                else if(nvpair.getName() == "text") {
                    rsltMessage->setParam(gen::text, nvpair.getValue());
                }
                else if(nvpair.getName() == "level"){
                    rsltMessage->setParam(gen::level, nvpair.getValue());
                }
                else if(nvpair.getName() == "displaytext") {
                    rsltMessage->setParam(gen::displaytext, nvpair.getValue());
                }
                else {

                }
            }
        }
    }
    return rsltMessage;
}

//------------------------------------------------------------

EventMessage* GenMessageFactory::createEventMessage(ZbpMessage &message) {
    return NULL;
}

//-------------------------------------------------------------

HeartBeatMessage* GenMessageFactory::createHeartBeatMessage(XAPMessage &message) {
    GenAddress source;
    HeartBeatMessage* rsltMessage = NULL;
    try {
        bool ok;
        source = GenAddress(message.getXAPSource().getVendor(),
                      message.getXAPSource().getType(),
                      message.getXAPSource().getLocation(),
                      message.getXAPSource().getInstance());
        int port = -1, pid = -1, interval = -1;
        QString tmp = message.valueOf("xap-hbeat", "port");
        if(!tmp.isEmpty())
            port = tmp.toInt(&ok);
        if(!ok) {
            port = -1;
        }
        tmp = message.valueOf("xap-hbeat", "interval");
        if(!tmp.isEmpty())
            interval = tmp.toInt(&ok);
        if(!ok) {
            interval = -1;
        }
        tmp = message.valueOf("xap-hbeat", "pid");
        if(!tmp.isEmpty())
            pid = tmp.toInt(&ok);
        if(!ok) {
            pid = -1;
        }
        rsltMessage = new HeartBeatMessage(source, port, interval, pid);
    }
    catch(const error::SysException& e) {
        qDebug() << e.getMessage();
    }
    return rsltMessage;
}

//-------------------------------------------------------------

HeartBeatMessage* GenMessageFactory::createHeartBeatMessage(ZbpMessage &message) {
    return NULL;
}

//-------------------------------------------------------------

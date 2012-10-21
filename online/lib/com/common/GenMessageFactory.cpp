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

#include "GenMessageFactory.h"
SingleDAT* GenMessageFactory::deviceAddressTranslator = NULL;

GenMessage* GenMessageFactory::createMessage(ZbpMessage &message) {
    if(deviceAddressTranslator != NULL) {
        if(message.getOrder() == zigbus::order_INITIALIZE)
            return createEventMessage(message);
        else
            return createInformationMessage(message);
    }
    else
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

        if(message.at(i).getBlockname() == "output.state") {
            rsltMessage->setCommandType(message.at(i).getBlockname());
            for(int i2 = 0; i2 < message.at(i).count(); i2++) {
                XAPNameValuePair nvpair = message.at(i).at(i2);
                if(nvpair.getName() == "state") {
                    if(nvpair.getValue() == "on")
                        rsltMessage->setParam(gen::state, "on");
                    else if(nvpair.getValue() == "off")
                        rsltMessage->setParam(gen::state, "off");
                    else if(nvpair.getValue() == "toogle")
                        rsltMessage->setParam(gen::state, "toogle");
                    else
                        rsltMessage->setParam(gen::state, nvpair.getValue());
                }
                else if(nvpair.getName() == "time")
                    rsltMessage->setParam(gen::time, nvpair.getValue());
                else if(nvpair.getName() == "unit")
                    rsltMessage->setParam(gen::unit, nvpair.getValue());
                else if(nvpair.getName() == "text")
                    rsltMessage->setParam(gen::text, nvpair.getValue());
                else if(nvpair.getName() == "level")
                    rsltMessage->setParam(gen::level, nvpair.getValue());
                else if(nvpair.getName() == "displaytext")
                    rsltMessage->setParam(gen::displaytext, nvpair.getValue());
                else if(nvpair.getName() == "position")
                    rsltMessage->setParam(gen::position, nvpair.getValue());
                else {
                    qDebug() << "unknown parameter : " + nvpair.getName()+"...";
                }
            }
        }
        else if(message.at(i).getBlockname() == "configuration") {
            rsltMessage->setCommandType(message.at(i).getBlockname());
            for(int i2 = 0; i2 < message.at(i).count(); i2++) {
                XAPNameValuePair nvpair = message.at(i).at(i2);
                if(nvpair.getName() == "id" || nvpair.getName() == "alter+" || nvpair.getName() == "idcmd") {
                    rsltMessage->setParam(gen::id, nvpair.getValue());
                }
                else if(nvpair.getName() == "id2" || nvpair.getName() == "alter-" || nvpair.getName() == "idpuis") {
                    rsltMessage->setParam(gen::id2, nvpair.getValue());
                }
                else if(nvpair.getName() == "type") {
                    rsltMessage->setParam(gen::type, nvpair.getValue());
                }
                else if(nvpair.getName() == "stype") {
                    rsltMessage->setParam(gen::stype, nvpair.getValue());
                }
                else if(nvpair.getName() == "ref") {
                    rsltMessage->setParam(gen::ref, nvpair.getValue());
                }
                else if(nvpair.getName() == "state") {
                    rsltMessage->setParam(gen::state, nvpair.getValue());
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
        for(int i = 0; i < message.count(); i++) {
            if(message.elementAt(i).getBlockname() == "request") {
                for(int i2 = 0; i2 < message.elementAt(i).count(); i2++) {
                    XAPNameValuePair& nvpair = message.elementAt(i).elementAt(i2);
                    if(nvpair.getName() == "stype") {
                        rsltMessage->setParam(gen::stype, nvpair.getValue());
                    }

                }

            }
        }

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

    if(message.getOrder() == zigbus::order_INITIALIZE) {
        EventMessage* resultMessage = NULL;
        try {
            GenAddress address = deviceAddressTranslator->find(message.getTargetAddress());
            resultMessage = new EventMessage(address);
            resultMessage->setParam(gen::state, "on");
            resultMessage->setTypeEvent("init");
            return resultMessage;
        }
        catch(const QString& exception) {
            qDebug() << exception;
            if(resultMessage != NULL)
                delete resultMessage;
            return NULL;
        }
    }
    else
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

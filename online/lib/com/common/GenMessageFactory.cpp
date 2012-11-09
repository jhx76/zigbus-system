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
#include <com/zbp/zigbus.h>

SingleDAT* GenMessageFactory::deviceAddressTranslator = NULL;

GenMessage* GenMessageFactory::createMessage(ZbpMessage &message) {
    try {
    if(deviceAddressTranslator != NULL) {
        if(message.getOrder() == zigbus::order_INITIALIZE)
            return createEventMessage(message);
        else if(message.getOrder() == order_ACK || message.getOrder() == order_TEMPERATURE
                || message.getOrder() == order_PING || message.getOrder() == order_STATUS
                || message.getOrder() == order_COUNT || message.getOrder() == order_REALEASE)
        {
            return createInformationMessage(message);
        }
    }
    return NULL;
     }
    catch(const QString& exception) {
        qDebug() << exception;
    }
}

//------------------------------------------------------------

GenMessage* GenMessageFactory::createMessage(XAPMessage &message) {
    try {
    if(message.getVersion() == "12") {
        if(message.getClass().toLower() == "xapbsc.cmd") {
            return createCommandMessage(message);
        }
        else if(message.getClass().toLower() == "xapbsc.info") {
            return createInformationMessage(message);
        }
        else if(message.getClass().toLower() == "xapbsc.event") {
            return createEventMessage(message);
        }
        else if(message.getClass().toLower() == "xapbsc.query") {
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
        else if(message.getClass().toLower() == "xap-hbeat.alive") {
            return createHeartBeatMessage(message);
        }
        else
            throw error::SysException("error: unknown xapclass ("+message.getClass()+")");
    }
    else
        throw error::SysException("error: bad version (" + message.getVersion() + ")");
    }
    catch(const error::SysException& exception) {
        qDebug() << exception.toString();
    }
    catch(const QString& exception) {
        qDebug() << exception;
    }

    return NULL;
}

//------------------------------------------------------------

CommandMessage* GenMessageFactory::createCommandMessage(ZbpMessage &message) {
    //pas possible que les devices envoient des commandes!!
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
                    else if(nvpair.getName() == "func")
                        rsltMessage->setParam(gen::func, nvpair.getValue());
                    else {
                        qDebug() << "unknown parameter : " + nvpair.getName()+"...";
                    }
                }
            }
            else if(message.at(i).getBlockname() == "configuration") {
                rsltMessage->setCommandType(message.at(i).getBlockname());
                for(int i2 = 0; i2 < message.at(i).count(); i2++) {
                    XAPNameValuePair nvpair = message.at(i).at(i2);
                    if(nvpair.getName() == "id")
                        rsltMessage->setParam(gen::id, nvpair.getValue());
                    else if(nvpair.getName() == "id2")
                        rsltMessage->setParam(gen::id2, nvpair.getValue());
                    else if(nvpair.getName() == "alter-")
                        rsltMessage->setParam(gen::alterm, nvpair.getValue());
                    else if(nvpair.getName() == "alter+")
                        rsltMessage->setParam(gen::alterp, nvpair.getValue());
                    else if(nvpair.getName() == "idpuis")
                        rsltMessage->setParam(gen::idpuis, nvpair.getValue());
                    else if(nvpair.getName() == "idcmd")
                        rsltMessage->setParam(gen::idcmd, nvpair.getValue());
                    else if(nvpair.getName() == "type")
                        rsltMessage->setParam(gen::type, nvpair.getValue());
                    else if(nvpair.getName() == "stype")
                        rsltMessage->setParam(gen::stype, nvpair.getValue());
                    else if(nvpair.getName() == "ref")
                        rsltMessage->setParam(gen::ref, nvpair.getValue());
                    else if(nvpair.getName() == "state")
                        rsltMessage->setParam(gen::state, nvpair.getValue());
                }
            }
        }
    }
    catch(const error::SysException& exception) {
        qDebug() << exception.getMessage();
        if(rsltMessage) {
            delete rsltMessage;
            rsltMessage = NULL;
        }
    }
    catch(const QString& exception) {
        qDebug() << exception;
        if(rsltMessage) {
            delete rsltMessage;
            rsltMessage = NULL;
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
        if(rsltMessage != NULL) {
            delete rsltMessage;
            rsltMessage = NULL;
        }
    }
    catch(const QString& exception) {
        qDebug() << exception;
        if(rsltMessage != NULL) {
            delete rsltMessage;
            rsltMessage = NULL;
        }
    }

    return rsltMessage;
}

//------------------------------------------------------------

QueryMessage* GenMessageFactory::createQueryMessage(ZbpMessage &message) {
    // Pas possible que les devices envoient des requetes
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


        for(int i = 0; i < message.count(); i++) {

            if(message.at(i).getBlockname() == "input.state" || "output.state") {

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
    }
    catch(const error::SysException& e) {
        qDebug() << e.getMessage();
        if(rsltMessage != NULL) {
            delete rsltMessage;
            rsltMessage = NULL;
        }
    }
    catch(const QString& exception) {
        qDebug() << exception;
        if(rsltMessage != NULL) {
            delete rsltMessage;
            rsltMessage = NULL;
        }
    }
    return rsltMessage;
}

//------------------------------------------------------------

InformationMessage* GenMessageFactory::createInformationMessage(ZbpMessage &message) {
    InformationMessage* infoMessage = NULL;

    try {
        if(message.getOrder() == order_STATUS) {

        }
        else if(message.getOrder() == order_PING) {

        }
        else if(message.getOrder() == order_TEMPERATURE) {
            if(message.getBits(ZIGBUS_SUBTYPE_ENCODESIZE, ZIGBUS_QR_ENCODESIZE) == 1) {

                GenAddress source = deviceAddressTranslator->find(message.getTargetAddress());
                infoMessage = new InformationMessage(source);
                infoMessage->setTypeInfo("input.state");
                ZigbusSubType subtype = message.getTargetAddress().getSubType();
                QString strtype = zigbus::convertSubTypeToStr(subtype);
                if(strtype.isEmpty())
                    throw QString(AT+"error: temperature subType is 'undef'");
                infoMessage->setParam(gen::stype, strtype);
                QString strtemp = QString::number(
                            message.getBits(ZIGBUS_SUBTYPE_ENCODESIZE + ZIGBUS_QR_ENCODESIZE + ZIGBUS_PINID_ENCODESIZE
                                            , ZIGBUS_TEMPERATURE_ENCODESIZE));
                infoMessage->setParam(gen::temp, strtemp);
                infoMessage->setParam(gen::unit, "C");
                QString strhygro = QString::number(
                            message.getBits(ZIGBUS_SUBTYPE_ENCODESIZE + ZIGBUS_QR_ENCODESIZE + ZIGBUS_PINID_ENCODESIZE + ZIGBUS_TEMPERATURE_ENCODESIZE
                                            , ZIGBUS_HYGRO_ENCODESIZE));
                infoMessage->setParam(gen::hygro, strhygro+"/100");
            }
            else
                throw QString(AT+"error: a device sent a temperature query");
        }
        else if(message.getOrder() == order_COUNT) {

        }
        else if(message.getOrder() == order_ACK) {
            GenAddress source = deviceAddressTranslator->find(message.getTargetAddress());
            infoMessage = new InformationMessage(source);
            ZigbusOrder ackorder = (ZigbusOrder)message.getBits(0, ZIGBUS_ORDER_ENCODSIZE);
            if(ackorder == order_CONFIGURE) {
                infoMessage->setTypeInfo("ack.configuration");
                ZigbusDeviceType type = (ZigbusDeviceType)message.getBits(ZIGBUS_ORDER_ENCODSIZE, ZIGBUS_TYPE_ENCODSIZE);
                infoMessage->setParam(gen::type, convertDeviceType(type));
                if(type == type_NUMERIC_OUTPUT) {
                    QString strState = (message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_TYPE_ENCODSIZE
                                                        , ZIGBUS_NUMERIC_INISTATE_ENCODESIZE) == 0
                                        ? "off" : "on");
                    infoMessage->setParam(gen::state, strState);
                    QString pinID = zigbus::convertDevicePinId(message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_TYPE_ENCODSIZE
                                                                               + ZIGBUS_NUMERIC_INISTATE_ENCODESIZE
                                                                               , ZIGBUS_PINID_ENCODESIZE));
                    infoMessage->setParam(gen::id, pinID);
                }
                else if(type == type_NUMERIC_INPUT) {
                    QString pinID = zigbus::convertDevicePinId(message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_TYPE_ENCODSIZE
                                                                               , ZIGBUS_PINID_ENCODESIZE));
                    infoMessage->setParam(gen::id, pinID);
                }
                else if(type == type_PWM_OUTPUT) {
                    QString strState = (message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_TYPE_ENCODSIZE
                                                        , ZIGBUS_PWM_INISTATE_ENCODESIZE) == 0
                                        ? "OFF" : "ON");
                    infoMessage->setParam(gen::state, strState);
                    QString pinID = zigbus::convertDevicePinId(message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_TYPE_ENCODSIZE + ZIGBUS_PWM_INISTATE_ENCODESIZE
                                                                               , ZIGBUS_PINID_ENCODESIZE));
                    infoMessage->setParam(gen::id, pinID);
                }
                else if(type == type_ANALOGIC_INPUT) {
                    QString strRef = zigbus::convertAnalogicReference(
                                (ZigbusAnalogicReference)message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_TYPE_ENCODSIZE,
                                                                         ZIGBUS_ANALOGIC_REFERENCE_ENCODESIZE));
                    infoMessage->setParam(gen::ref, strRef);
                    QString pinID = zigbus::convertDevicePinId(message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_TYPE_ENCODSIZE + ZIGBUS_ANALOGIC_REFERENCE_ENCODESIZE
                                                                               , ZIGBUS_PINID_ENCODESIZE));
                    infoMessage->setParam(gen::id, pinID);
                }
                else if(type == type_LAMPE) {

                }
                else if(type == type_HEATER) {
                    QString pinID1 = zigbus::convertDevicePinId(
                                message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_TYPE_ENCODSIZE
                                                , ZIGBUS_PINID_ENCODESIZE));
                    infoMessage->setParam(gen::alterp, pinID1);
                    QString pinID2 = zigbus::convertDevicePinId(
                                message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_TYPE_ENCODSIZE + ZIGBUS_PINID_ENCODESIZE
                                                , ZIGBUS_PINID_ENCODESIZE));
                    infoMessage->setParam(gen::alterm, pinID2);
                }
                else if(type == type_TEMPERATURE) {
                    QString subtype = zigbus::convertSubTypeToStr((ZigbusSubType)message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_TYPE_ENCODSIZE
                                                                                                 , ZIGBUS_SUBTYPE_ENCODESIZE));
                    infoMessage->setParam(gen::stype, subtype);
                    QString pinID = zigbus::convertDevicePinId(message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_TYPE_ENCODSIZE
                                                                               + ZIGBUS_SUBTYPE_ENCODESIZE
                                                                               , ZIGBUS_PINID_ENCODESIZE));
                    infoMessage->setParam(gen::id, pinID);
                }
                else if(type == type_SERVO) {
                    QString pinID1 = zigbus::convertDevicePinId(
                                message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_TYPE_ENCODSIZE
                                                , ZIGBUS_PINID_ENCODESIZE));
                    infoMessage->setParam(gen::idcmd, pinID1);
                    QString pinID2 = zigbus::convertDevicePinId(
                                message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_TYPE_ENCODSIZE + ZIGBUS_PINID_ENCODESIZE
                                                , ZIGBUS_PINID_ENCODESIZE));
                    infoMessage->setParam(gen::idpuis, pinID2);
                }
                else if(type == type_TOKEN) {

                }
                else if(type == type_REMOTE) {

                }
                else if(type == type_SERIAL) {

                }
                else
                    throw QString(AT+"error: unknown type");


            }
            else {
                infoMessage->setTypeInfo("ack.command");
                if(ackorder == order_ON) {
                    infoMessage->setParam(gen::state, "ON");
                    int itime = message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_ADTYPE_ENCODESIZE + ZIGBUS_PINID_ENCODESIZE,
                                                ZIGBUS_TIME_ENCODESIZE);
                    if(itime > 0) {
                        infoMessage->setParam(gen::time, QString::number(itime));
                        int iunit = message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_ADTYPE_ENCODESIZE + ZIGBUS_PINID_ENCODESIZE + ZIGBUS_TIME_ENCODESIZE
                                                    , ZIGBUS_TIMEUNIT_ENCODESIZE);
                        infoMessage->setParam(gen::unit, (iunit == 0 ? "sec" : "min"));
                    }
                }
                else if(ackorder == order_OFF ) {
                    infoMessage->setParam(gen::state, "OFF");
                    int itime = message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_ADTYPE_ENCODESIZE + ZIGBUS_PINID_ENCODESIZE,
                                                ZIGBUS_TIME_ENCODESIZE);
                    if(itime > 0) {
                        infoMessage->setParam(gen::time, QString::number(itime));
                        int iunit = message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_ADTYPE_ENCODESIZE + ZIGBUS_PINID_ENCODESIZE + ZIGBUS_TIME_ENCODESIZE
                                                    , ZIGBUS_TIMEUNIT_ENCODESIZE);
                        infoMessage->setParam(gen::unit, (iunit == 0 ? "sec" : "min"));
                    }
                }
                else if(ackorder == order_TOOGLE) {
                    infoMessage->setParam(gen::state, "TOOGLE");
                    int itime = message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_ADTYPE_ENCODESIZE + ZIGBUS_PINID_ENCODESIZE,
                                                ZIGBUS_TIME_ENCODESIZE);
                    if(itime > 0) {
                        infoMessage->setParam(gen::time, QString::number(itime));
                        int iunit = message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_ADTYPE_ENCODESIZE + ZIGBUS_PINID_ENCODESIZE + ZIGBUS_TIME_ENCODESIZE
                                                    , ZIGBUS_TIMEUNIT_ENCODESIZE);
                        infoMessage->setParam(gen::unit, (iunit == 0 ? "sec" : "min"));
                    }
                }
                else if(ackorder == order_SERVO) {
                    int iposition = message.getBits(ZIGBUS_ORDER_ENCODSIZE, ZIGBUS_RADPOSITION_ENCODESIZE);
                    infoMessage->setParam(gen::position, QString::number(iposition));
                }
                else if(ackorder == order_TEXT) {

                }
                else if(ackorder == order_PWM) {
                    int ilevel = message.getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_PINID_ENCODESIZE,
                                                 ZIGBUS_PWM_ORDER_ENCODESIZE);
                    if(ilevel > 0) infoMessage->setParam(gen::state, "ON");
                    else infoMessage->setParam(gen::state, "OFF");
                    infoMessage->setParam(gen::level, QString::number(ilevel)+"/512");
                }
                else if(ackorder == order_HEATER) {
                    ZigbusHeaterFunction ifunc = (ZigbusHeaterFunction)message.getBits(ZIGBUS_ORDER_ENCODSIZE, ZIGBUS_HEATER_FUNC_ENCODESIZE);
                    infoMessage->setParam(gen::func, zigbus::convertHeaterFunction(ifunc));
                }
            }


        }
        else if(message.getOrder() == order_REALEASE) {

        }

    }
    catch(const QString& str) {
        qDebug() << str;
        if(infoMessage) {
            delete infoMessage;
            infoMessage = NULL;
        }
    }
    return infoMessage;
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
    }
    catch(const error::SysException& e) {
        qDebug() << e.getMessage();
    }
    catch(const QString& exception) {
        qDebug() << exception;
    }
    return rsltMessage;
}

//------------------------------------------------------------

EventMessage* GenMessageFactory::createEventMessage(ZbpMessage &message) {
    EventMessage* resultMessage = NULL;
    try {
        if(message.getOrder() == zigbus::order_INITIALIZE) {
            GenAddress address = deviceAddressTranslator->find(message.getTargetAddress());
            resultMessage = new EventMessage(address);
            resultMessage->setParam(gen::state, "on");
            resultMessage->setTypeEvent("init");
            return resultMessage;
        }
        else
            return NULL;
    }
    catch(const QString& exception) {
        qDebug() << exception;
        if(resultMessage != NULL)
            delete resultMessage;
        return NULL;
    }
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
    catch(const QString& exception) {
        qDebug() << exception;
    }

    return rsltMessage;
}

//-------------------------------------------------------------

HeartBeatMessage* GenMessageFactory::createHeartBeatMessage(ZbpMessage &message) {
    return NULL;
}

//-------------------------------------------------------------

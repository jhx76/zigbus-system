/*
    This file is part of Zigbus Home Automation API.

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


#include "ZbpNetwork.h"

ZbpNetwork::ZbpNetwork(SingleDAT* deviceAddressTranslator, QObject* parent) : GenNetwork("zigbus", parent)
{
    this->deviceAddressTranslator = deviceAddressTranslator;
    if(this->deviceAddressTranslator == NULL)
        error::NullPointerException("deviceAddressTranslator null pointer", AT, true);
    modem = NULL;
}

ZbpNetwork::ZbpNetwork(SingleDAT* deviceAddressTranslator, const ZbpNetworkProperties& properties, QObject* parent) : GenNetwork("zigbus", parent)
{
    this->properties = properties;
    this->deviceAddressTranslator = deviceAddressTranslator;
    if(this->deviceAddressTranslator == NULL)
        error::NullPointerException("deviceAddressTranslator null pointer", AT, true);
    modem = NULL;
}

void ZbpNetwork::initialize(const QString& str) {
    if(QFile::exists(properties.getFileName())) {
        modem = new QextSerialPort(properties.getFileName());
        modem->setBaudRate(BAUD115200);
        modem->setDataBits(DATA_8);
        modem->setFlowControl(FLOW_OFF);
        modem->setParity(PAR_NONE);
        modem->setStopBits(STOP_1);
        //modem->setTextModeEnabled(true);
        //modem->setQueryMode(QextSerialPort::EventDriven);
        modem->setTimeout(1);
        connect(modem, SIGNAL(readyRead()), this, SLOT(onDataAvaible()));
    }
    else
        throw error::InitializationException(properties.getFileName()+" doesn't exist", AT, true);
}

/*
void ZbpNetwork::run() {
    if(!startListening())
        emit this->quitApplication();
    exec();
}
*/


bool ZbpNetwork::startListening() {
    bool running = modem->open(QIODevice::ReadWrite);
    if(running)
        qDebug() << "Listening Zigbus network on "+modem->portName();
    else {
        qDebug() << AT << " error: " << modem->errorString();
        qDebug() << "Bridge isn't listening zigbus network ...";
    }
    return running;
}

bool ZbpNetwork::isListening() {
    return modem->isOpen();
}

void ZbpNetwork::stopListening() {
    if(modem)
        modem->close();
}


void ZbpNetwork::sendMessage(GenMessage* message) {
    ZbpMessage zbpmsg = convertAndFreeMemory(message);

    if(!zbpmsg.toTrame().contains("-")) {
        qDebug() << "send: " << zbpmsg.toTrame();
        if(modem && modem->isOpen()) {
            modem->write(zbpmsg.toTrame().toLocal8Bit());
        }
    }
}

zigbus::ZigbusDeviceType ZbpNetwork::convertDeviceType(const QString &strType) {
    if(strType == "temperature") return zigbus::type_TEMPERATURE;
    else if(strType == "heater") return zigbus::type_HEATER;
    else if(strType == "lamp") return zigbus::type_LAMPE;
    else if(strType == "numeric_input") return zigbus::type_NUMERIC_INPUT;
    else if(strType == "numeric_output") return zigbus::type_NUMERIC_OUTPUT;
    else if(strType == "analogic_input") return zigbus::type_ANALOGIC_INPUT;
    else if(strType == "pwm") return zigbus::type_PWM_OUTPUT;
    else if(strType == "remote") return zigbus::type_REMOTE;
    else if(strType == "serial") return zigbus::type_SERIAL;
    else if(strType == "servo") return zigbus::type_SERVO;
    else if(strType == "token") return zigbus::type_TOKEN;
    else return zigbus::type_UNDEF;
}

zigbus::ZigbusSubType ZbpNetwork::convertSubType(const QString &strSubType) {
    if(strSubType == "LM35DZ") return zigbus::stype_LM35DZ;
    else if(strSubType == "DHT11") return zigbus::stype_DHT11;
    else return zigbus::stype_UNDEF;
}

int ZbpNetwork::convertDevicePinId(const QString &strPinId) {
    bool ok;
    int rslt = strPinId.mid(1).toInt(&ok);
    if(!ok) throw QString();
    if(strPinId.mid(0, 1) == "S")
        return rslt;
    else if(strPinId.mid(0, 1) == "A")
        return rslt+100;
    else throw QString(AT+"error: unknown pin id");
}

ZbpMessage ZbpNetwork::convertAndFreeMemory(GenMessage *genericMessage) {
    ZbpMessage resultMessage;
    if(genericMessage == NULL)
        throw error::NullPointerException("genericMessage null pointer", AT, false);

    CommandMessage* commandMessage = NULL;
    EventMessage* eventMessage = NULL;
    InformationMessage* informationMessage = NULL;
    QueryMessage* queryMessage = NULL;
    ZbpAddress address;

    switch(genericMessage->getTypeMessage()) {
    //################################
    // CONVERSION D'UNE COMMANDE
    //################################
    /*
      Peut donner une trame :
      - ON/OFF/TOOGLE
      - MOTEUR
      - PWM
      - CHAUFFAGE
      - CONFIGURE
      - SERVO
      - SERIE
      - TEXT
      - PORTAIL
    */
    case GenMessage::Command:
        commandMessage = (CommandMessage*)genericMessage;
        if(commandMessage) {
            try {
                int bindex = 0;

                if(commandMessage->getCommandType() == "output.state") {
                    address = this->deviceAddressTranslator->find(commandMessage->getTarget());
                    //qDebug() << address.toTrame();
                    if(address.getHardwareType() == zigbus::type_NUMERIC_OUTPUT) {
                        if(commandMessage->contains(gen::state)) {
                            if(commandMessage->getParam(gen::state).toUpper() == "ON") {
                                resultMessage.setOrder(zigbus::order_ON);
                            }
                            else if(commandMessage->getParam(gen::state).toUpper() == "OFF") {
                                resultMessage.setOrder(zigbus::order_OFF);
                            }
                            else if(commandMessage->getParam(gen::state).toUpper() == "TOOGLE") {
                                resultMessage.setOrder(zigbus::order_TOOGLE);
                            }
                            resultMessage.setBits(bindex, ZIGBUS_ADTYPE_ENCODESIZE, 0);
                            bindex += ZIGBUS_ADTYPE_ENCODESIZE;
                        }
                        else
                            throw QString("error: unknown order");

                        resultMessage.setBits(bindex, ZIGBUS_PINID_ENCODESIZE, convertDevicePinId(address.getMainPin()));
                        bindex += ZIGBUS_PINID_ENCODESIZE;

                        if(commandMessage->contains(gen::time) && commandMessage->contains(gen::unit)) {
                            if( commandMessage->getParam(gen::unit) == "min")
                                resultMessage.setBits(bindex, ZIGBUS_TIMEUNIT_ENCODESIZE, 1);
                            else if(commandMessage->getParam(gen::unit) == "sec")
                                resultMessage.setBits(bindex, ZIGBUS_TIMEUNIT_ENCODESIZE, 0);
                            else
                                throw QString("error: unknown time unit");
                            bindex += ZIGBUS_TIMEUNIT_ENCODESIZE;
                            resultMessage.setBits(bindex, ZIGBUS_TIME_ENCODESIZE,
                                                  commandMessage->getParam(gen::time).toInt());
                            bindex += ZIGBUS_TIME_ENCODESIZE;
                        }

                        resultMessage.setTargetAddress(address);
                    }
                    else if(address.getHardwareType() == zigbus::type_PWM_OUTPUT) {
                        resultMessage.setOrder(zigbus::order_PWM);
                        resultMessage.setBits(bindex, ZIGBUS_PINID_ENCODESIZE,
                                              convertDevicePinId(address.getMainPin()));
                        bindex += ZIGBUS_PINID_ENCODESIZE;
                        if(commandMessage->contains(gen::level)) {
                            QString strlevel = commandMessage->getParam(gen::level);
                            if(strlevel.contains("/")) {
                                int denominateur = strlevel.mid(strlevel.indexOf("/")).toInt();
                                int value = strlevel.mid(0, strlevel.indexOf("/")-1).toInt();
                                resultMessage.setBits(bindex, ZIGBUS_PWM_ORDER_ENCODESIZE, ((value*512)/denominateur));
                            }
                            resultMessage.setBits(bindex, ZIGBUS_PWM_ORDER_ENCODESIZE,
                                                  commandMessage->getParam(gen::level).toInt());
                            bindex += ZIGBUS_PWM_ORDER_ENCODESIZE;
                        }
                        resultMessage.setTargetAddress(address);
                    }
                    else if(address.getHardwareType() == zigbus::type_SERVO) {
                        bool ok;
                        int position = commandMessage->getParam(gen::position).toInt(&ok);
                        if(!ok)
                            throw QString(AT + "\nerror: unable to convert param(position) to 'integer'");
                        resultMessage.setOrder(zigbus::order_SERVO);
                        resultMessage.setBits(bindex, ZIGBUS_RADPOSITION_ENCODESIZE, position);
                        bindex += ZIGBUS_RADPOSITION_ENCODESIZE;
                        resultMessage.setBits(bindex, ZIGBUS_PINID_ENCODESIZE,
                                              convertDevicePinId(address.getMainPin())); //Sortie Commande
                        bindex += ZIGBUS_PINID_ENCODESIZE;
                        resultMessage.setBits(bindex, ZIGBUS_PINID_ENCODESIZE,
                                              convertDevicePinId(address.getOptionalPin())); //Sortie Puissance
                        bindex += ZIGBUS_PINID_ENCODESIZE;
                        resultMessage.setTargetAddress(address);
                    }
                    else if(address.getHardwareType() == zigbus::type_HEATER) {
                        resultMessage.setOrder(zigbus::order_HEATER);
                        if(commandMessage->contains(gen::func)
                                && zigbus::convertHeaterFunction(commandMessage->getParam(gen::func)) != zigbus::hfunc_UNDEF)
                        {
                            resultMessage.setBits(bindex, ZIGBUS_HEATER_FUNC_ENCODESIZE,
                                                  zigbus::convertHeaterFunction(commandMessage->getParam(gen::func)));
                            bindex += ZIGBUS_HEATER_FUNC_ENCODESIZE;
                        }
                        else throw QString(AT+"error: unknown heater function");
                        resultMessage.setBits(bindex, ZIGBUS_PINID_ENCODESIZE,
                                              convertDevicePinId(address.getMainPin()));
                        bindex += ZIGBUS_PINID_ENCODESIZE;
                        resultMessage.setBits(bindex, ZIGBUS_PINID_ENCODESIZE,
                                              convertDevicePinId(address.getOptionalPin()));
                        bindex += ZIGBUS_PINID_ENCODESIZE;
                        resultMessage.setTargetAddress(address);
                    }
                }
                else if(commandMessage->getCommandType() == "configuration") {
                    QString strId = "", strId2 = "";
                    if(commandMessage->contains(gen::id)) strId = commandMessage->getParam(gen::id);
                    else if(commandMessage->contains(gen::idcmd)) strId = commandMessage->getParam(gen::idcmd);
                    else if(commandMessage->contains(gen::alterp)) strId = commandMessage->getParam(gen::alterp);
                    else
                        throw QString("error: unknown pin type");

                    if(commandMessage->contains(gen::id2)) strId2 = commandMessage->getParam(gen::id2);
                    else if(commandMessage->contains(gen::idpuis)) strId2 = commandMessage->getParam(gen::idpuis);
                    else if(commandMessage->contains(gen::alterm)) strId2 = commandMessage->getParam(gen::alterm);

                    address = this->deviceAddressTranslator->find(commandMessage->getTarget(),
                                                                  strId,
                                                                  strId2,
                                                                  commandMessage->getParam(gen::type));

                    resultMessage.setOrder(zigbus::order_CONFIGURE);
                    zigbus::ZigbusDeviceType zbtype = convertDeviceType(commandMessage->getParam(gen::type));
                    if(zbtype != zigbus::type_UNDEF) {
                        resultMessage.setBits(bindex, ZIGBUS_TYPE_ENCODSIZE, zbtype);
                        bindex += ZIGBUS_TYPE_ENCODSIZE;

                        if(zbtype == zigbus::type_TEMPERATURE) {
                            if(commandMessage->contains(gen::stype)) {
                                zigbus::ZigbusSubType zbstype = convertSubType(commandMessage->getParam(gen::stype));
                                if(zbstype != zigbus::stype_UNDEF) {
                                    resultMessage.setBits(bindex, ZIGBUS_SUBTYPE_ENCODESIZE, zbstype);
                                    bindex += ZIGBUS_SUBTYPE_ENCODESIZE;
                                }
                                else {
                                    throw QString("undef subtype");
                                }
                            }
                            resultMessage.setTargetAddress(address);
                            resultMessage.setBits(bindex, ZIGBUS_PINID_ENCODESIZE, convertDevicePinId(address.getMainPin()));
                            bindex += ZIGBUS_PINID_ENCODESIZE;
                        }

                        else if(zbtype == zigbus::type_HEATER) {
                            resultMessage.setTargetAddress(address);
                            //config sortie ALTER+
                            resultMessage.setBits(bindex, ZIGBUS_PINID_ENCODESIZE, convertDevicePinId(address.getMainPin()));
                            bindex += ZIGBUS_PINID_ENCODESIZE;
                            //config sortie ALTER-
                            resultMessage.setBits(bindex, ZIGBUS_PINID_ENCODESIZE, convertDevicePinId(address.getOptionalPin()));
                            bindex += ZIGBUS_PINID_ENCODESIZE;
                        }

                        else if(zbtype == zigbus::type_LAMPE) {
                            throw QString("error: type_LAMP isn't implemented in this version");
                        }

                        else if(zbtype == zigbus::type_NUMERIC_INPUT) {
                            resultMessage.setTargetAddress(address);
                            resultMessage.setBits(bindex, ZIGBUS_PINID_ENCODESIZE, convertDevicePinId(address.getMainPin()));
                            bindex += ZIGBUS_PINID_ENCODESIZE;
                        }
                        else if(zbtype == zigbus::type_NUMERIC_OUTPUT) {
                            if(commandMessage->contains(gen::state)) {
                                if(commandMessage->getParam(gen::state).toUpper() == "ON") {
                                    resultMessage.setBits(bindex, ZIGBUS_NUMERIC_INISTATE_ENCODESIZE, 1);
                                    bindex += ZIGBUS_NUMERIC_INISTATE_ENCODESIZE;
                                }
                                else if(commandMessage->getParam(gen::state).toUpper() == "OFF") {
                                    resultMessage.setBits(bindex, ZIGBUS_NUMERIC_INISTATE_ENCODESIZE, 0);
                                    bindex += ZIGBUS_NUMERIC_INISTATE_ENCODESIZE;
                                }
                                else
                                    throw QString("error: unknown numeric_output inistate");
                            }
                            else
                                throw QString("error: unknown numeric_output inistate");
                            resultMessage.setTargetAddress(address);
                            resultMessage.setBits(bindex, ZIGBUS_PINID_ENCODESIZE, convertDevicePinId(address.getMainPin()));
                            bindex += ZIGBUS_PINID_ENCODESIZE;

                        }
                        else if(zbtype == zigbus::type_ANALOGIC_INPUT) {
                            if(commandMessage->contains(gen::ref)) {
                                QString analogReference = commandMessage->getParam(gen::ref);
                                if(analogReference.toUpper() == "DEFAULT") {
                                    resultMessage.setBits(bindex, ZIGBUS_ANALOGIC_REFERENCE_ENCODESIZE, zigbus::aref_DEFAULT);
                                    bindex += ZIGBUS_ANALOGIC_REFERENCE_ENCODESIZE;
                                }
                                else if(analogReference.toUpper() == "INTERNAL") {
                                    resultMessage.setBits(bindex, ZIGBUS_ANALOGIC_REFERENCE_ENCODESIZE, zigbus::aref_INTERNAL);
                                    bindex += ZIGBUS_ANALOGIC_REFERENCE_ENCODESIZE;
                                }
                                else if(analogReference.toUpper() == "INTERNAL1V1") {
                                    resultMessage.setBits(bindex, ZIGBUS_ANALOGIC_REFERENCE_ENCODESIZE, zigbus::aref_INTERNAL1V1);
                                    bindex += ZIGBUS_ANALOGIC_REFERENCE_ENCODESIZE;
                                }
                                else if(analogReference.toUpper() == "INTERNAL2V56") {
                                    resultMessage.setBits(bindex, ZIGBUS_ANALOGIC_REFERENCE_ENCODESIZE, zigbus::aref_INTERNAL2V56);
                                    bindex += ZIGBUS_ANALOGIC_REFERENCE_ENCODESIZE;
                                }
                                else if(analogReference.toUpper() == "EXTERNAL") {
                                    resultMessage.setBits(bindex, ZIGBUS_ANALOGIC_REFERENCE_ENCODESIZE, zigbus::aref_EXTERNAL);
                                    bindex += ZIGBUS_ANALOGIC_REFERENCE_ENCODESIZE;
                                }
                                else {
                                    throw QString("error: unknown heater reference");
                                }
                                resultMessage.setTargetAddress(address);
                                resultMessage.setBits(bindex, ZIGBUS_PINID_ENCODESIZE, convertDevicePinId(address.getMainPin()));
                                bindex += ZIGBUS_PINID_ENCODESIZE;
                            }
                        }
                        else if(zbtype == zigbus::type_PWM_OUTPUT) {
                            if(commandMessage->contains(state)) {
                                if(commandMessage->getParam(state).toUpper() == "ON") {
                                    resultMessage.setBits(bindex, ZIGBUS_PWM_INISTATE_ENCODESIZE, 1);
                                    bindex += ZIGBUS_PWM_INISTATE_ENCODESIZE;
                                }
                                else if(commandMessage->getParam(state).toUpper() == "OFF") {
                                    resultMessage.setBits(bindex, ZIGBUS_PINID_ENCODESIZE, 0);
                                    bindex += ZIGBUS_PWM_INISTATE_ENCODESIZE;
                                }
                                else
                                    throw QString("error: uknown pwm inistate");
                            }
                            resultMessage.setTargetAddress(address);
                            resultMessage.setBits(bindex, ZIGBUS_PINID_ENCODESIZE, convertDevicePinId(address.getMainPin()));
                            bindex += ZIGBUS_PINID_ENCODESIZE;
                        }
                        else if(zbtype == zigbus::type_REMOTE) {
                            throw QString("error: type_REMOTE isn't implemented in this version");
                        }
                        else if(zbtype == zigbus::type_SERIAL) {
                            throw QString("error: type_SERIAL isn't implemented in this version");
                        }
                        else if(zbtype == zigbus::type_SERVO) {
                            resultMessage.setBits(bindex, ZIGBUS_PINID_ENCODESIZE, convertDevicePinId(address.getMainPin()));
                            bindex += ZIGBUS_PINID_ENCODESIZE;
                            resultMessage.setBits(bindex, ZIGBUS_PINID_ENCODESIZE, convertDevicePinId(address.getOptionalPin()));
                            bindex += ZIGBUS_PINID_ENCODESIZE;
                            resultMessage.setTargetAddress(address);
                        }
                        else if(zbtype == zigbus::type_TOKEN) {
                            throw QString("error: type_TOKEN isn't implemented in this version");
                        }
                    }
                    else {
                        throw QString("error: unknown device type");
                    }
                }
                else {

                }
            }
            catch(const QString& e) {
                qDebug() << e;
            }
        }
        break;
        //################################
        // CONVERSION D'UNE REQUETE
        //################################
        /*
          - STATE (QUERY)
          - TEMPERATURE (QUERY)
          - VERSION (QUERY)
          */
    case GenMessage::Query:
        try {
        //queryMessage = (QueryMessage*)genericMessage;
        queryMessage = dynamic_cast<QueryMessage*>(genericMessage);
        if(!queryMessage)
            throw error::NullPointerException("query message null pointer", AT);
        int bindex = 0;
        address = deviceAddressTranslator->find(queryMessage->getTarget());
        if(address.getHardwareType() == zigbus::type_TEMPERATURE) {
            resultMessage.setOrder(zigbus::order_TEMPERATURE);
            ZigbusSubType stype = convertSubType(queryMessage->getParam(gen::stype).toUpper());
            if(stype != zigbus::stype_UNDEF) {
                resultMessage.setBits(bindex, ZIGBUS_SUBTYPE_ENCODESIZE, stype);
                bindex += ZIGBUS_SUBTYPE_ENCODESIZE;
            }
            else
                throw QString("error: unknow temperature sensor type");
            resultMessage.setBits(bindex, 1, 0); //query
            bindex++;
            resultMessage.setBits(bindex, ZIGBUS_PINID_ENCODESIZE,
                                  convertDevicePinId(address.getMainPin()));
            bindex += ZIGBUS_PINID_ENCODESIZE;
            resultMessage.setTargetAddress(address);
        }
    }
    catch(const error::NullPointerException& exception) {
        qDebug() << exception.toString();
    }
    catch(const QString& e) {
        qDebug() << e;
    }


    break;

    //################################
    // CONVERSION D'UN PING
    //################################
    /*
          - PING
          */
    /* case GenMessage::Ping:
        PingMessage* pingMessage = (PingMessage*)genericMessage;

        break;*/

    default:
        //throw TranslationException();
        ;
    };

    //Free the memory
    if(genericMessage) delete genericMessage;
    return resultMessage;
}

void ZbpNetwork::onDataAvaible() {
    try {
        waitingData += modem->readAll();
        QString trame;
        while(waitingData.contains("\n")) {
            trame = waitingData.mid(0, waitingData.indexOf("\n")-1);
            waitingData = waitingData.mid(waitingData.indexOf("\n")+1);
        }
        if(!trame.isEmpty()) {
            if(trame.contains("\n"))
                trame.remove("\n");
            ZbpMessage zigbusMessage(trame);
            GenMessage* genericMessage = GenMessageFactory::createMessage(zigbusMessage);
            if(genericMessage != NULL)
                emit this->messageReceived(genericMessage, "zigbus");
        }
    }
    catch(const QString& exception) {
        qDebug() << exception;
    }
}

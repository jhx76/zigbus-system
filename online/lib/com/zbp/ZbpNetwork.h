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

#ifndef ZBPNETWORK_H
#define ZBPNETWORK_H
#include <core/SingleDAT.h>
#include <core/Error.h>

#include <QDebug>

#include <com/common/GenNetwork.h>
#include <com/common/CommandMessage.h>
#include <com/common/EventMessage.h>
#include <com/common/QueryMessage.h>
#include <com/common/InformationMessage.h>

#include <com/zbp/zigbus.h>
#include <com/zbp/ZbpMessage.h>
#include <com/zbp/ZbpAddress.h>
#include <com/zbp/ZbpNetworkProperties.h>
#include <com/serial/qextserialport.h>

#include <com/common/GenMessageFactory.h>

class ZbpNetwork : public GenNetwork
{
    Q_OBJECT
private:
    SingleDAT* deviceAddressTranslator;

    ZbpNetworkProperties properties;

    QextSerialPort* modem;

    /**

      */
    ZbpMessage convertAndFreeMemory(GenMessage* message);

public:
    /**

      */
    ZbpNetwork(SingleDAT* deviceAddressTranslator, QObject* parent = 0);

    /**

      */
    ZbpNetwork(SingleDAT* deviceAddressTranslator, const ZbpNetworkProperties& properties, QObject* parent = 0);

    ~ZbpNetwork() {
        if(modem) {
            modem->close();
            delete modem;
        }
    }

    void run();

    /**

      */
    virtual void initialize(const QString& str = "");

    /**

      */
    virtual bool startListening();

    /**

      */
    virtual bool isListening();

    /**

      */
    virtual void stopListening();

    /**

      */
    static zigbus::ZigbusDeviceType convertDeviceType(const QString& strType);

    static zigbus::ZigbusSubType convertSubType(const QString& strSubType);

    static int convertDevicePinId(const QString& strPinId);

    void test() {
        //QString s = "0000011F"; //trame init module 0001
        QString s = "0000021F"; //trame init module 0002
        ZbpMessage trame(s);
        emit toDisplay("message received: "+trame.toTrame());
        GenMessage* message = GenMessageFactory::createMessage(trame);
        if(message != NULL)
            emit this->messageReceived(message, "zigbus");
    }

public slots:
    /**

      */
    virtual void sendMessage(GenMessage* message);

    /**

      */
    void onDataAvaible();

signals:
    void toDisplay(QString);
};

#endif // ZBPNETWORK_H

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

#include <com/common/GenMessageFactory.h>

#include <qextserialport.h>

class ZbpNetwork : public GenNetwork
{
    Q_OBJECT
private:
    SingleDAT* deviceAddressTranslator;

    ZbpNetworkProperties properties;

    ZbpMessage convertAndFreeMemory(GenMessage* message);

    QextSerialPort* modem;

    QString waitingData;

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

   // virtual void run();

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
        //QString s = "0000021F"; //trame init module 0002

        //   H64%    8C°    S1    R  DHT11  temp
        // 1000000 001000 0000001 1   001   01011
        //QString s = "0000011008032B";

        //Trame ACK.configure temp DHT11 M01 S1
        //QString s = "00000149FDD";

        //Trame ACK.configure numeric_output M01 S2 (OFF)
        //QString s = "000001207DD";

        //Trame ACK.configure lave-vaisselle (numeric_output) M02 S3 (OFF)
        //QString s = "000002307DD";

        //Trame ACK.configure heater M01 A2 S4
        //QString s = "0000011331BDD";

        //Trame ACK.configure pwm M01 S5 (OFF)
        //QString s = "00000150FDD";

        //Trame ACK.configure Servo M01 S9/S10
        //QString s = "000001284A3DD";

        //Trame ACK.command OFF M01 S2
        //QString s = "000001101D";

        //Trame ACK.command ON M01 S2
        //QString s = "000001103D";

        //Trame ACK.command SERVO pos(18) M01 S9/S10
        //QString s = "0000011424487D";

        //Trame ACK.command PWM (50/212) M01 S5
        //QString s = "0000016414BD";

        //Trame ACK.command HEATER eco M01 A2/S4
        //QString s = "0000014CC8DD";

        QString s = "";
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

    void quitApplication();
};

#endif // ZBPNETWORK_H

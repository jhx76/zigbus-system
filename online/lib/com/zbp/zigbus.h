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

#ifndef ZIGBUS_H
#define ZIGBUS_H

#include <core/SysUtils.h>

#define ZIGBUS_TYPE_ENCODSIZE                   5
#define ZIGBUS_ORDER_ENCODSIZE                  5
#define ZIGBUS_SUBTYPE_ENCODESIZE               3
#define ZIGBUS_PINID_ENCODESIZE                 7
#define ZIGBUS_QR_ENCODESIZE                    1
#define ZIGBUS_NUMERIC_INISTATE_ENCODESIZE      1
#define ZIGBUS_ANALOGIC_REFERENCE_ENCODESIZE    3
#define ZIGBUS_PWM_INISTATE_ENCODESIZE          1
#define ZIGBUS_ADTYPE_ENCODESIZE                1
#define ZIGBUS_TIMEUNIT_ENCODESIZE              1
#define ZIGBUS_TIME_ENCODESIZE                  6
#define ZIGBUS_PWM_ORDER_ENCODESIZE             10
#define ZIGBUS_HEATER_FUNC_ENCODESIZE           3
#define ZIGBUS_RADPOSITION_ENCODESIZE           8
#define ZIGBUS_TEMPERATURE_ENCODESIZE           6
#define ZIGBUS_HYGRO_ENCODESIZE                 7
#include <QString>
/**

  */
namespace zigbus
{


/**
Champ codé sur 5bits.

<table>
<tr><td>0</td><td>00000</td><td>OFF (0%)</td></tr>
<tr><td>1</td><td>00001</td><td>ON (100%)</td></tr>
<tr><td>2</td><td>00010</td><td>Bascule</td></tr>
<tr><td>3</td><td>00011</td><td>Servo</td></tr>
<tr><td>4</td><td>00100</td><td>Texte</td></tr>
<tr><td>5</td><td>00101</td><td>PWM</td></tr>
<tr><td>6</td><td>00110</td><td>Chauffage</td></tr>
<tr><td>7</td><td>00111</td><td>Etat</td></tr>
<tr><td>8</td><td>01000</td><td>Serie</td></tr>
<tr><td>9</td><td>01001</td><td>Remote</td></tr>
<tr><td>10</td><td>01010</td><td>Ping</td></tr>
<tr><td>11</td><td>01011</td><td>Temperature</td></tr>
<tr><td>…</td></tr>
<tr><td>30</td><td>11110</td><td>Configure</td></tr>
<tr><td>31</td><td>11111</td><td>Init</td></tr>
</table>

  */
typedef enum ZIGBUS_ORDER {
    order_OFF = 0x00,
    order_ON = 0x01,
    order_TOOGLE = 0x02,
    order_SERVO = 0x03,
    order_TEXT = 0x04,
    order_PWM = 0x05,
    order_HEATER = 0x06,
    order_STATUS = 0x07,
    order_SERIAL = 0x08,
    order_REMOTE = 0x09,
    order_PING = 0x0A,
    order_TEMPERATURE = 0x0B,
    order_GATE = 0x0C,
    order_MOTOR = 0x0D,
    order_TIE = 0x0E,
            //...
    order_REBOOT = 0x1A,
    order_COUNT = 0x1B,
    order_REALEASE = 0x1C,
    order_ACK = 0x1D,
    order_CONFIGURE = 0x1E,
    order_INITIALIZE = 0x1F
} ZigbusOrder;


/**
  Codé sur 5bits
Undef                   0	00000
Sortie Num		1	00001
Entree Num		2	00010
Sortie PWM		3	00011
Entree Analogique	4	00100
Lampe			5	00101
Chauffage		6	00110
Temperature		7	00111
Servo			8	01000
Token			9	01001
Remote			10	01010
Serie			11	01011
  */
typedef enum ZIGBUS_DEVICE_TYPE {
    type_UNDEF = 0x00,
    type_NUMERIC_OUTPUT = 0x01,
    type_NUMERIC_INPUT = 0x02,
    type_PWM_OUTPUT = 0x03,
    type_ANALOGIC_INPUT = 0x04,
    type_LAMPE = 0x05,
    type_HEATER = 0x06,
    type_TEMPERATURE = 0x07,
    type_SERVO = 0x08,
    type_TOKEN = 0x09,
    type_REMOTE = 0x0A,
    type_SERIAL = 0x0B
    //type_GATE = 0x0C
} ZigbusDeviceType;

/**

  */
typedef enum ZIGBUS_SUB_TYPE {
    stype_UNDEF = 0x00,
    stype_DHT11 = 0x01,
    stype_LM35DZ = 0x02
} ZigbusSubType;

typedef enum ZIGBUS_ANALOGIC_REFERENCE {
    aref_DEFAULT = 0x00,
    aref_INTERNAL = 0x01,
    aref_INTERNAL1V1 = 0x02,
    aref_INTERNAL2V56 = 0x03,
    aref_EXTERNAL = 0x04
} ZigbusAnalogicReference;

QString convertAnalogicReference(ZigbusAnalogicReference ref);

ZigbusAnalogicReference convertAnalogicReference(const QString& str);

typedef enum ZIGBUS_HEATER_FUNCTION {
    hfunc_UNDEF = 0x00,
    hfunc_STOP = 0x01,
    hfunc_ECO = 0x02,
    hfunc_CONFORT2 = 0x05,
    hfunc_CONFORT1 = 0x06,
    hfunc_CONFORT = 0x07
} ZigbusHeaterFunction;

ZigbusHeaterFunction convertHeaterFunction(const QString& strFunc);

QString convertHeaterFunction(ZigbusHeaterFunction func);

ZigbusDeviceType convertDeviceType(const QString& strType);

QString convertDeviceType(ZigbusDeviceType type);

ZigbusSubType convertStrToSubType(const QString& str);

QString convertSubTypeToStr(ZigbusSubType stype);

int convertDevicePinId(const QString& strPinId);

QString convertDevicePinId(int id);

}




#endif // ZIGBUS_H

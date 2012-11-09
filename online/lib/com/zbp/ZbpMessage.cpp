#include "ZbpMessage.h"

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


ZbpMessage::ZbpMessage() {

}

ZbpMessage::ZbpMessage(const QString &arg) {
    bool convertionOK = false;
    QString src = arg.mid(6);
    QString strAddress = arg.mid(0, 6); //2digits réseau + 4digits address
    this->targetAddress = ZbpAddress(strAddress); // Adresse du module

    int value = src.toInt(&convertionOK, 16);
    if(!convertionOK)
        throw QString();

    int nbBitsRequired = 0;
    while(getPossibleMax(nbBitsRequired) < value)
        nbBitsRequired++;

    QBitArray completeArray(nbBitsRequired, false); /* temporary bit tab: order + body */
    for(int i = 0; i < completeArray.size(); i++)
        completeArray[i] = value & (1 << i);

    order = (ZigbusOrder)getBits(0, ZIGBUS_ORDER_ENCODSIZE, &completeArray);
    ZigbusDeviceType type;

    //RESIZE BODY IF NECESSARY
    int bodySize = 0;
    switch(order)
    {
    case order_OFF:
        bodySize += 1;
        if(getBits(ZIGBUS_ORDER_ENCODSIZE, 1, &completeArray) == 0) bodySize += 7; /* direct */
        else bodySize += 5; /* typed */
        bodySize += 6 /* time value */ + 1 /* unité */;
        break;

    case order_ON:
        bodySize += 1;
        if(getBits(ZIGBUS_ORDER_ENCODSIZE, 1, &completeArray) == 0) bodySize += 7; /* direct */
        else bodySize += 5; /* typed */
        bodySize += 6 /* time value */ + 1 /* unité */;
        break;

    case order_TOOGLE:
        bodySize += 1;
        if(getBits(ZIGBUS_ORDER_ENCODSIZE, 1, &completeArray) == 0) bodySize += 7; /* direct */
        else bodySize += 5; /* typed */
        bodySize += 6 /* time value */ + 1 /* unité */;
        break;

    case order_SERVO:
        bodySize += 8/* Position */;
        bodySize += 14; /* 2sorties (commande/puissance) */
        break;

    case order_TEXT:
        throw QString();
        break;

    case order_PWM:
        throw QString();
        break;

    case order_HEATER:
        bodySize += 3 /* Fonction */;
        bodySize += 14 /* Alter+ et Alter- */;
        break;

    case order_STATUS:
        /* Pas de body dans ce cas, l'ordre se suffit a lui-meme */
        break;

    case order_SERIAL:
        bodySize += 3; /* P.Serie */
        bodySize += 5; /* chaine texte */
        break;

    case order_REMOTE:
        throw QString();
        break;

    case order_PING:
        throw QString();
        break;

    case order_TEMPERATURE:
        bodySize += 3; /* type capteur */
        bodySize += 1; /* Q/R */
        if(getBits(8, 1, &completeArray) == 0)
            bodySize += 7; /* si c'est une query, on spécifie juste la sortie concernée */
        else /* Si c'est une réponse */
            bodySize += 20; /* cf. spec zbp */
        break;

    case order_GATE:

        break;

    case order_MOTOR:
        break;

    case order_TIE:
        break;

    case order_REBOOT:
        break;

    case order_COUNT:
        break;

    case order_REALEASE:
        break;

    case order_ACK:
        bodySize += ZIGBUS_ORDER_ENCODSIZE;

        {//Des accolades juste pour dépiler les variables
            ZigbusOrder order = (ZigbusOrder)getBits(ZIGBUS_ORDER_ENCODSIZE, ZIGBUS_ORDER_ENCODSIZE, &completeArray);
            if(order == order_OFF || order == order_ON || order == order_TOOGLE) {
                bodySize += 1;
                if(getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_ORDER_ENCODSIZE, 1, &completeArray) == 0) bodySize += 7; /* direct */
                else bodySize += 5; /* typed */
                bodySize += 6 /* time value */ + 1 /* unité */;
            }
            else if(order == order_SERVO) {
                bodySize += ZIGBUS_RADPOSITION_ENCODESIZE;
                bodySize += (ZIGBUS_PINID_ENCODESIZE * 2);
            }
            else if(order == order_TEXT) {

            }
            else if(order == order_PWM) {
                bodySize += ZIGBUS_PINID_ENCODESIZE;
                bodySize += ZIGBUS_PWM_ORDER_ENCODESIZE;
            }
            else if(order == order_HEATER) {
                bodySize += ZIGBUS_HEATER_FUNC_ENCODESIZE;
                bodySize += (2*ZIGBUS_PINID_ENCODESIZE);
            }
            else if(order == order_SERIAL) {

            }
            else if(order == order_REMOTE) {

            }
            else if(order == order_GATE) {

            }
            else if(order == order_MOTOR) {

            }
            else if(order == order_TIE) {

            }
            else if(order == order_REBOOT) {

            }
            else if(order == order_CONFIGURE) {
                bodySize += ZIGBUS_TYPE_ENCODSIZE;
                type = (ZigbusDeviceType)getBits(ZIGBUS_ORDER_ENCODSIZE*2, ZIGBUS_TYPE_ENCODSIZE, &completeArray);
                if(type == type_UNDEF) throw QString(); //GERER ERREUR
                else if(type == type_NUMERIC_OUTPUT) bodySize += 8; //1 sortie sur 7bits + etat sur 1bit (ON ou OFF)
                else if(type == type_NUMERIC_INPUT) bodySize += 7; //1sortie sur 7bits
                else if(type == type_PWM_OUTPUT) bodySize += 8; //1sortie sur 7bits + 1bit d'etat
                else if(type == type_ANALOGIC_INPUT) bodySize += 10; //1sortie sur 7bits + reference sur 3bits
                else if(type == type_LAMPE) throw QString(); //GERE ERREUR
                else if(type == type_HEATER) bodySize += 14; //2 sorties chacune sur 7bits
                else if(type == type_TEMPERATURE) bodySize += 10; //1 sortie sur 7bits + type capteur sur 3bits
                else if(type == type_SERVO) {
                    bodySize += 14; //2sorties sur 7bits (command/puissance)
                }
              //  else if(type == type_GATE) {

              //  }
                else if(type == type_TOKEN) bodySize += 3; //P.Serie sur 3bits
                else if(type == type_REMOTE) bodySize += 3; //interruption sur 3bits
                else if(type == type_SERIAL) bodySize += 9; // 3 champs sur 3bits
            }
        }
        break;

    case order_CONFIGURE:
        bodySize += ZIGBUS_TYPE_ENCODSIZE;
        type = (ZigbusDeviceType)getBits(ZIGBUS_ORDER_ENCODSIZE, ZIGBUS_TYPE_ENCODSIZE, &completeArray);
        if(type == type_UNDEF) throw QString(); //GERER ERREUR
        else if(type == type_NUMERIC_OUTPUT) bodySize += 8; //1 sortie sur 7bits + etat sur 1bit (ON ou OFF)
        else if(type == type_NUMERIC_INPUT) bodySize += 7; //1sortie sur 7bits
        else if(type == type_PWM_OUTPUT) bodySize += 8; //1sortie sur 7bits+1bit d'etat
        else if(type == type_ANALOGIC_INPUT) bodySize += 10; //1sortie sur 7bits + reference sur 3bits
        else if(type == type_LAMPE) throw QString(); //GERE ERREUR
        else if(type == type_HEATER) bodySize += 14; //2 sorties chacune sur 7bits
        else if(type == type_TEMPERATURE) bodySize += 10; //1 sortie sur 7bits + type capteur sur 3bits
        else if(type == type_SERVO) {
            bodySize += 14; //2sorties sur 7bits (command/puissance)
        }
      //  else if(type == type_GATE) {

      //  }
        else if(type == type_TOKEN) bodySize += 3; //P.Serie sur 3bits
        else if(type == type_REMOTE) bodySize += 3; //interruption sur 3bits
        else if(type == type_SERIAL) bodySize += 9; // 3 champs sur 3bits
        break;

    case order_INITIALIZE:
        /* Pas de body dans ce cas, l'ordre se suffit a lui-meme */
        break;

    default:
        ;
    }

    //Construction du message
    body.resize(bodySize);
    for(int i = 0; i < bodySize; i++) {
        if(i+ZIGBUS_ORDER_ENCODSIZE < completeArray.size()) {
            body[i] = completeArray.at(i+ZIGBUS_ORDER_ENCODSIZE);
        }
        else {
            body[i] = false;
        }
    }

    //affectation de l'adresse
    QString displayablePin, displayablePin2;
    int encodedPin, encodedPin2;
    switch(order)
    {
    case order_OFF:
        encodedPin = getBits(0, ZIGBUS_PINID_ENCODESIZE);
        displayablePin = (encodedPin < 100 ? "S"+QString::number(encodedPin) : "A"+QString::number(encodedPin-100));
        targetAddress.setMainPin(displayablePin);
        targetAddress.setHardwareType(type_NUMERIC_OUTPUT);
        break;

    case order_ON:
        encodedPin = getBits(0, ZIGBUS_PINID_ENCODESIZE);
        displayablePin = (encodedPin < 100 ? "S"+QString::number(encodedPin) : "A"+QString::number(encodedPin-100));
        targetAddress.setMainPin(displayablePin);
        targetAddress.setHardwareType(type_NUMERIC_OUTPUT);
        break;

    case order_TOOGLE:
        encodedPin = getBits(0, ZIGBUS_PINID_ENCODESIZE);
        displayablePin = (encodedPin < 100 ? "S"+QString::number(encodedPin) : "A"+QString::number(encodedPin-100));
        targetAddress.setMainPin(displayablePin);
        targetAddress.setHardwareType(type_NUMERIC_OUTPUT);
        break;

    case order_SERVO:
        encodedPin = getBits(0, ZIGBUS_PINID_ENCODESIZE);
        displayablePin = (encodedPin < 100 ? "S"+QString::number(encodedPin) : "A"+QString::number(encodedPin-100));
        targetAddress.setMainPin(displayablePin);
        encodedPin2 = getBits(ZIGBUS_PINID_ENCODESIZE, ZIGBUS_PINID_ENCODESIZE);
        displayablePin2 = (encodedPin2 < 100 ? "S"+QString::number(encodedPin2) : "A"+QString::number(encodedPin2-100));
        targetAddress.setOptionalPin(displayablePin2);
        targetAddress.setHardwareType(type_SERVO);
        break;

    case order_TEXT:
        break;

    case order_PWM:
        encodedPin = getBits(0, ZIGBUS_PINID_ENCODESIZE);
        displayablePin = (encodedPin < 100 ? "S"+QString::number(encodedPin) : "A"+QString::number(encodedPin-100));
        targetAddress.setMainPin(displayablePin);
        targetAddress.setHardwareType(type_PWM_OUTPUT);
        break;

    case order_HEATER:
        encodedPin = getBits(ZIGBUS_HEATER_FUNC_ENCODESIZE, ZIGBUS_PINID_ENCODESIZE);
        displayablePin = (encodedPin < 100 ? "S"+QString::number(encodedPin) : "A"+QString::number(encodedPin-100));
        targetAddress.setMainPin(displayablePin);
        encodedPin2 = getBits(ZIGBUS_HEATER_FUNC_ENCODESIZE+ZIGBUS_PINID_ENCODESIZE, ZIGBUS_PINID_ENCODESIZE);
        displayablePin2 = (encodedPin2 < 100 ? "S"+QString::number(encodedPin2) : "A"+QString::number(encodedPin2-100));
        targetAddress.setOptionalPin(displayablePin2);
        targetAddress.setHardwareType(type_HEATER);
        break;

    case order_STATUS:
        break;

    case order_SERIAL:
        break;

    case order_REMOTE:
        break;

    case order_PING:
        break;

    case order_TEMPERATURE:
        encodedPin = getBits(ZIGBUS_SUBTYPE_ENCODESIZE+ZIGBUS_QR_ENCODESIZE, ZIGBUS_PINID_ENCODESIZE);
        displayablePin = (encodedPin < 100 ? "S"+QString::number(encodedPin) : "A"+QString::number(encodedPin-100));
        targetAddress.setMainPin(displayablePin);
        targetAddress.setHardwareType(type_TEMPERATURE);
        targetAddress.setSubType((ZigbusSubType)getBits(0, ZIGBUS_SUBTYPE_ENCODESIZE));
        break;

    case order_GATE:

        break;

    case order_MOTOR:
        break;

    case order_TIE:
        break;

    case order_REBOOT:
        break;

    case order_COUNT:
        break;

    case order_REALEASE:
        break;

    case order_ACK:
    {//Des accolades juste pour dépiler les variables
        ZigbusOrder order = (ZigbusOrder)getBits(ZIGBUS_ORDER_ENCODSIZE, ZIGBUS_ORDER_ENCODSIZE, &completeArray);
        if(order == order_OFF || order == order_ON || order == order_TOOGLE) {
            encodedPin = getBits(ZIGBUS_ORDER_ENCODSIZE+ZIGBUS_ADTYPE_ENCODESIZE, ZIGBUS_PINID_ENCODESIZE);
            displayablePin = (encodedPin < 100 ? "S"+QString::number(encodedPin) : "A"+QString::number(encodedPin-100));
            targetAddress.setMainPin(displayablePin);
            targetAddress.setHardwareType(type_NUMERIC_OUTPUT);
        }
        else if(order == order_SERVO) {
            encodedPin = getBits(ZIGBUS_ORDER_ENCODSIZE+ZIGBUS_RADPOSITION_ENCODESIZE, ZIGBUS_PINID_ENCODESIZE);
            displayablePin = (encodedPin < 100 ? "S"+QString::number(encodedPin) : "A"+QString::number(encodedPin-100));
            targetAddress.setMainPin(displayablePin);
            encodedPin2 = getBits(ZIGBUS_ORDER_ENCODSIZE+ZIGBUS_PINID_ENCODESIZE+ZIGBUS_RADPOSITION_ENCODESIZE
                                  , ZIGBUS_PINID_ENCODESIZE);
            displayablePin2 = (encodedPin2 < 100 ? "S"+QString::number(encodedPin2) : "A"+QString::number(encodedPin2-100));
            targetAddress.setOptionalPin(displayablePin2);
            targetAddress.setHardwareType(type_SERVO);
        }
        else if(order == order_TEXT) {

        }
        else if(order == order_PWM) {
            encodedPin = getBits(ZIGBUS_ORDER_ENCODSIZE, ZIGBUS_PINID_ENCODESIZE);
            displayablePin = (encodedPin < 100 ? "S"+QString::number(encodedPin) : "A"+QString::number(encodedPin-100));
            targetAddress.setMainPin(displayablePin);
            targetAddress.setHardwareType(type_PWM_OUTPUT);
        }
        else if(order == order_HEATER) {
            encodedPin = getBits(ZIGBUS_ORDER_ENCODSIZE + ZIGBUS_HEATER_FUNC_ENCODESIZE, ZIGBUS_PINID_ENCODESIZE);
            displayablePin = (encodedPin < 100 ? "S"+QString::number(encodedPin) : "A"+QString::number(encodedPin-100));
            targetAddress.setMainPin(displayablePin);
            encodedPin2 = getBits(ZIGBUS_ORDER_ENCODSIZE+ZIGBUS_HEATER_FUNC_ENCODESIZE+ZIGBUS_PINID_ENCODESIZE, ZIGBUS_PINID_ENCODESIZE);
            displayablePin2 = (encodedPin2 < 100 ? "S"+QString::number(encodedPin2) : "A"+QString::number(encodedPin2-100));
            targetAddress.setOptionalPin(displayablePin2);
            targetAddress.setHardwareType(type_HEATER);
        }
        else if(order == order_SERIAL) {

        }
        else if(order == order_REMOTE) {

        }
        else if(order == order_GATE) {

        }
        else if(order == order_MOTOR) {

        }
        else if(order == order_TIE) {

        }
        else if(order == order_REBOOT) {

        }
        else if(order == order_CONFIGURE) {
            bodySize += ZIGBUS_TYPE_ENCODSIZE;
            type = (ZigbusDeviceType)getBits(ZIGBUS_ORDER_ENCODSIZE*2, ZIGBUS_TYPE_ENCODSIZE, &completeArray);
            if(type == type_UNDEF) throw QString(); //GERER ERREUR
            else if(type == type_NUMERIC_OUTPUT) {

            }
            else if(type == type_NUMERIC_INPUT) {

            }
            else if(type == type_PWM_OUTPUT) {

            }
            else if(type == type_ANALOGIC_INPUT) {

            }
            else if(type == type_LAMPE) {

            }
            else if(type == type_HEATER) {

            }
            else if(type == type_TEMPERATURE) {

            }
            else if(type == type_SERVO) {

            }
            else if(type == type_TOKEN) {

            }
            else if(type == type_REMOTE) {

            }
            else if(type == type_SERIAL) {

            }
        }
    }


        break;

    case order_CONFIGURE:
        break;

    case order_INITIALIZE:
        break;
    }


}


ZbpMessage::ZbpMessage(const ZbpMessage &other) {
    this->body = other.body;
    this->targetAddress = other.targetAddress;
    this->order = other.order;

}

int ZbpMessage::getPossibleMax(int nbits) {
    if(nbits == 0) return 1;
    int rslt = 2;
    for(int i = 1; i < nbits; i++)
        rslt *= 2;
    return (rslt-1);
}


void ZbpMessage::setBits(int bIndex, int nbits, int value) {
    /// @todo throwin and catchin exceptions
    //lancement des erreurs venant des paramètres
    if(nbits <= 0)          //si on demande une insertion de 0bits
        throw QString();
    if(value < 0)           //si on demande l'insertion d'une val negative
        throw QString();

    //si la valeur a insérer est plus grande que la capacité demandée
    // valeur max = (2 puissance nbits) - 1
    if(value > getPossibleMax(nbits))
        throw QString();

    //resize du body si nécessaire
    if(body.size() < bIndex+nbits)
        body.resize(bIndex+nbits);

    //Insertion de la valeur demandée
    for(int i = bIndex; i < bIndex+nbits; i++) {
        int l = value & (1 << (i-bIndex));
        body[i] = l;
    }
    qDebug() << "message body is now " << this->displayAsBinary(this->body);
}

int ZbpMessage::getBits(int bIndex, int nbits, QBitArray const* srcArray) const {
    int value = 0;
    if(srcArray == NULL) srcArray = &body;
    QString debug = "";
    for(int i = bIndex+nbits-1; i >= bIndex; i--) {
        value <<= 1;
        value += (int)srcArray->at(i);
        //debug += (srcArray->at(i) ? "1" : "0");
    }
    //qDebug() << debug;
    return value;
}

QString ZbpMessage::toTrame() const {
    QString result = "";
    QString strAddress = this->targetAddress.toTrame();

    QBitArray completeArray(5/*Order*/ + body.size(), false);
    for(int i = 0; i < 5; i++)
        completeArray[i] = order & (1 << i);

    for(int i = 0; i < body.size(); i++)
        completeArray[i+5] = body.at(i);


    int bodyValue = 0;
    for(int i = completeArray.size()-1; i >= 0; i--) {
        bodyValue <<= 1;
        bodyValue += (int)completeArray.at(i);
    }

    result += strAddress;
    result += QString::number(bodyValue, 16);
    return result.toUpper();
}

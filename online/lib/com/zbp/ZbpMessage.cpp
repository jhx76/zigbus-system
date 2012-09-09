#include "ZbpMessage.h"

ZbpMessage::ZbpMessage() {

}

ZbpMessage::ZbpMessage(const QString &arg) {
    bool convertionOK = false;
    int temp;
    QString src = arg.mid(6);
    QString strAddress = arg.mid(0, 6); //2digits réseau + 5digits address
    this->targetAddress = ZbpAddress(strAddress);


    int value = src.toInt(&convertionOK, 16);
    if(!convertionOK)
        throw QString();

    int nbBitsRequired = 0;
    while(getPossibleMax(nbBitsRequired) < value)
        nbBitsRequired++;
    /*
      trame SERVO: should be 27bits
      */
    QBitArray completeArray(nbBitsRequired, false); /* Ordre + body */
    for(int i = 0; i < completeArray.size(); i++)
        completeArray[i] = value & (1 << i);

    /*QString debug = "";
    for(int i = 0; i < completeArray.size(); i++)
        debug += (completeArray[i] ? "1" : "0");
    qDebug() << AT+"complete array : "+debug;*/


    //11000 00100110 1010000 0000000
    order = (ZigbusOrder)getBits(0, ZIGBUS_ORDER_ENCODSIZE, &completeArray);
    ZigbusDeviceType type;


    int bodySize = 0;
    switch(order)
    {
    case order_OFF:
        bodySize += 1;
        if(getBits(ZIGBUS_ORDER_ENCODSIZE, 1, &completeArray) == 0)
            bodySize += 7; /* direct */
        else
            bodySize += 5; /* typed */
        bodySize += 6 /* time value */ + 1 /* unité */;
        break;

    case order_ON:
        bodySize += 1;
        if(getBits(ZIGBUS_ORDER_ENCODSIZE, 1, &completeArray) == 0)
            bodySize += 7; /* direct */
        else
            bodySize += 5; /* typed */
        bodySize += 6 /* time value */ + 1 /* unité */;
        break;

    case order_TOOGLE:
        bodySize += 1;
        if(getBits(ZIGBUS_ORDER_ENCODSIZE, 1, &completeArray) == 0)
            bodySize += 7; /* direct */
        else
            bodySize += 5; /* typed */
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

    case order_STATE:
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

    case order_CONFIGURE:
        bodySize += ZIGBUS_TYPE_ENCODSIZE;
        type = (ZigbusDeviceType)getBits(ZIGBUS_ORDER_ENCODSIZE, ZIGBUS_TYPE_ENCODSIZE, &completeArray);
        if(type == type_UNDEF) throw QString(); //GERER ERREUR
        else if(type == type_NUMERIC_OUTPUT) bodySize += 8; //1 sortie sur 7bits + etat sur 1bit (ON ou OFF)
        else if(type == type_NUMERIC_INPUT) bodySize += 7; //1sortie sur 7bits
        else if(type == type_PWM_OUTPUT) bodySize += 7; //1sortie sur 7bits
        else if(type == type_ANALOGIC_INPUT) bodySize += 10; //1sortie sur 7bits + reference sur 3bits
        else if(type == type_LAMP) throw QString(); //GERE ERREUR
        else if(type == type_HEATER) bodySize += 14; //2 sorties chacune sur 7bits
        else if(type == type_TEMPERATURE) bodySize += 10; //1 sortie sur 7bits + type capteur sur 3bits
        else if(type == type_SERVO) {
            bodySize += 14; //2sorties sur 7bits (command/puissance)
            bodySize += 8; //position (angle)
        }
        else if(type == type_TOKEN) bodySize += 3; //P.Serie sur 3bits
        else if(type == type_REMOTE) bodySize += 3; //interruption sur 3bits
        else if(type == type_SERIAL) bodySize += 9; // 3 champs sur 3bits
        break;

    case order_INITIALIZE:
        /* Pas de body dans ce cas, l'ordre se suffit a lui-meme */
        break;
    }

    body.resize(bodySize);
    for(int i = 0; i < bodySize; i++) {
        if(i+ZIGBUS_ORDER_ENCODSIZE < completeArray.size()) {
            body[i] = completeArray.at(i+ZIGBUS_ORDER_ENCODSIZE);
        }
        else {
            body[i] = false;
        }
    }

/*
    qDebug() << "bodySize => "+QString::number(body.size());
    debug = "";
    for(int i = 0; i < body.size(); i++)
        debug += (body[i] ? "1" : "0");
    qDebug() << AT+"body bin :"+debug;*/
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
    for(int i = bIndex; i < nbits; i++) {
        body[i] = value & (1 << i);
    }
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

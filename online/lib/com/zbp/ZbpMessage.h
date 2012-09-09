#ifndef ZBPMESSAGE_H
#define ZBPMESSAGE_H

#include <com/zbp/zigbus.h>
#include <com/zbp/ZbpAddress.h>
#include <QBitArray>
#include <QString>
#include <QDebug>
#include <core/SysUtils.h>

using namespace zigbus;


/**

  */
class ZbpMessage
{
private:

    /**

      */
    ZigbusOrder order;

    /**

      */
    //ModuleAddress + NetworkAddress
    //placé au début du tableau de bits a la fin de la construction de la trame
    ZbpAddress targetAddress;

    /**

      */
    QBitArray body;


    /**

      */
    static int getPossibleMax(int nbits);

    static QString displayAsHexa(const QBitArray& array) {
        bool ok;
        QString tmp = displayAsBinary(array);
        int itmp = tmp.toInt(&ok, 2);
        if(!ok)
            return "";
        return QString::number(itmp, 16);
    }



    static QString displayAsBinary(const QBitArray& array) {
        QString result = "";
        for(int i = 0; i < array.size(); i++)
            result += (array.at(i) ? "1" : "0");
        return result;
    }

public:
    /**
      Constructeur par défaut
      */
    ZbpMessage();

    /**
        @todo
      */
    ZbpMessage(const QString& src);

    /**
      Constructeur de recopie
      */
    ZbpMessage(const ZbpMessage& other);

    /**

      */
    void setBits(int bIndex, int nbits, int value);

    /**

      */
    int getBits(int bIndex, int nbits, QBitArray const* srcArray = NULL) const;

    /**
        @todo
      */
    QString toTrame() const;

    /**

      */
    ZigbusOrder getOrder() const { return order; }

    /**

      */
    void setOrder(ZigbusOrder order) { this->order = order; }

    /**

      */
    const ZbpAddress& getTargetAddress() const { return targetAddress; }

    /**

      */
    void setTargetAddress(const ZbpAddress& target) { targetAddress = target; }

    /**

      */
    const QBitArray& getBody() const { return body; }

    /**

      */
    void setBody(const QBitArray& array) { body = array; }
};

#endif // ZBPMESSAGE_H

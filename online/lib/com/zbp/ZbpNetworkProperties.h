#ifndef ZBPNETWORKPROPERTIES_H
#define ZBPNETWORKPROPERTIES_H

#include <QString>
#include <QtXmlPatterns>
#include <QXmlQuery>
#include <core/Error.h>
#include <core/SysUtils.h>

class ZbpNetworkProperties
{
private:
    QString baudrate;
    QString fileName;
    QString parity;
    QString flowControl;
    QString dataBit;


public:
    ZbpNetworkProperties();

    ZbpNetworkProperties(const QString& fileName, const QString& baudRate,
                         const QString& parity, const QString& flowControl, const QString& dataBit);

    ZbpNetworkProperties(const QString& xmlFileName);

    ZbpNetworkProperties(const ZbpNetworkProperties& other);

    bool isEqual(const ZbpNetworkProperties& other) const;

    ZbpNetworkProperties& operator=(const ZbpNetworkProperties& other);

    const QString& getBaudRate() const { return baudrate; }

    void setBaudRate(const QString& baudRate) { this->baudrate = baudRate; }

    const QString& getFileName() const { return fileName; }

    void setFileName(const QString& fileName) { this->fileName = fileName; }

    const QString& getParity() const { return parity; }

    void setParity(const QString& parity) { this->parity = parity; }

    const QString& getFlowControl() const { return flowControl; }

    void setFlowControl(const QString& flowControl) { this->flowControl = flowControl; }

    const QString& getDataBit() const { return dataBit; }

    void setDataBit(const QString& databit) { this->dataBit = databit; }
};

#endif // ZBPNETWORKPROPERTIES_H

#include "ZbpNetworkProperties.h"

ZbpNetworkProperties::ZbpNetworkProperties()
{
    this->baudrate = "";
    this->fileName = "";
    this->parity = "";
    this->flowControl = "";
    this->dataBit = "";
}

ZbpNetworkProperties::ZbpNetworkProperties(const QString &fileName, const QString &baudRate,
                                           const QString &parity, const QString &flowControl, const QString &dataBit)
{
    this->fileName = fileName;
    this->baudrate = baudRate;
    this->parity = parity;
    this->flowControl = flowControl;
    this->dataBit = dataBit;
}

ZbpNetworkProperties::ZbpNetworkProperties(const QString &xmlFileName) {

    bool fileExists = QFile::exists(xmlFileName);
    if(!fileExists) {
        throw error::InitializationException(" Configuration file "+xmlFileName+" not found !", AT, true);
    }
    /*
<zbp-network>
    <network-id>1</network-id>  <!-- will be usefull for identifie on which network we want discuss -->
        <tty>                       <!-- Serial I/O parameters for ZBP master module connection -->
            <file>/dev/ttyUSB0</file>
            <baud-rate>9600</baud-rate>
            <parity>none</parity>
            <data-bits>8</data-bits>
            <flow-control>none</flow-control>
        </tty>
    </zbp-network>
</configuration>
      */

    QString xmlResult = "";
    QString url = xmlFileName;

    QXmlQuery query;
    query.bindVariable("url", QXmlItem(QVariant(url)));
    query.setQuery("declare variable $url external;"
                   "doc($url)/configuration/zbp-network/tty/file/text()");
    if (query.isValid()) {
        if (query.evaluateTo(&xmlResult)) {
            if(xmlResult.contains("\n"))
                xmlResult.remove("\n");
            setFileName(xmlResult);
        }
    }
    else
        throw error::InitializationException("XML query failed", AT, true);
    //qDebug() << "[DBInitRead::importDatabaseProperties] invalid query !";

    query.setQuery("declare variable $url external;"
                   "doc($url)/configuration/zbp-network/tty/baud-rate/text()");
    if(query.isValid()) {
        if(query.evaluateTo(&xmlResult)) {
            if(xmlResult.contains("\n"))
                xmlResult.remove("\n");
            setBaudRate(xmlResult);
        }
    }
    else
        throw error::InitializationException("XML query failed", AT, true);

    query.setQuery("declare variable $url external;"
                   "doc($url)/configuration/zbp-network/tty/parity/text()");
    if(query.isValid()) {
        if(query.evaluateTo(&xmlResult)) {
            if(xmlResult.contains("\n"))
                xmlResult.remove("\n");
            setParity(xmlResult);
        }
    }
    else
        throw error::InitializationException("XML query failed", AT, true);

    query.setQuery("declare variable $url external;"
                   "doc($url)/configuration/zbp-network/tty/data-bits/text()");
    if(query.isValid()) {
        if(query.evaluateTo(&xmlResult)) {
            if(xmlResult.contains("\n"))
                xmlResult.remove("\n");
            setDataBit(xmlResult);
        }
    }
    else
        throw error::InitializationException("XML query failed", AT, true);

    query.setQuery("declare variable $url external;"
                   "doc($url)/configuration/zbp-network/tty/flow-control/text()");
    if(query.isValid()) {
        if(query.evaluateTo(&xmlResult)) {
            if(xmlResult.contains("\n"))
                xmlResult.remove("\n");
            setFlowControl(xmlResult);
        }
    }
    else
        throw error::InitializationException("XML query failed", AT, true);

}

ZbpNetworkProperties::ZbpNetworkProperties(const ZbpNetworkProperties &other) {
    this->fileName = other.fileName;
    this->baudrate = other.baudrate;
    this->parity = other.parity;
    this->flowControl = other.flowControl;
    this->dataBit = other.dataBit;
}

ZbpNetworkProperties& ZbpNetworkProperties::operator=(const ZbpNetworkProperties& other) {
    this->fileName = other.fileName;
    this->baudrate = other.baudrate;
    this->parity = other.parity;
    this->flowControl = other.flowControl;
    this->dataBit = other.dataBit;
    return *this;
}

bool ZbpNetworkProperties::isEqual(const ZbpNetworkProperties &other) const {
    return (this->fileName == other.fileName &&
            this->baudrate == other.baudrate &&
            this->parity == other.parity &&
            this->flowControl == other.flowControl &&
            this->dataBit == other.dataBit);
}

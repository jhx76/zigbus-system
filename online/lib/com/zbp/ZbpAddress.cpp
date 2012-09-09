#include "ZbpAddress.h"


ZbpAddress::ZbpAddress() {

}

ZbpAddress::ZbpAddress(int inetwork, int iaddress) {
    this->networkAddress = inetwork;
    this->moduleAddress = iaddress;
}


ZbpAddress::ZbpAddress(const QString &str) {
    QString strModule = str.mid(2);
    QString strNetwork = str.mid(0,2);
    bool conversionOK;
    this->moduleAddress = strModule.toInt(&conversionOK, 10);
    if(!conversionOK)
        throw QString("error");

    this->networkAddress = strNetwork.toInt(&conversionOK, 10);
    if(!conversionOK)
        throw QString("error");
}


ZbpAddress::ZbpAddress(const ZbpAddress& other) {
    this->moduleAddress = other.moduleAddress;
    this->networkAddress = other.networkAddress;
}

ZbpAddress& ZbpAddress::operator =(const ZbpAddress& other) {
    this->moduleAddress = other.moduleAddress;
    this->networkAddress = other.networkAddress;
    return *this;
}

 bool ZbpAddress::isEqual(const ZbpAddress& other) const {
     return (this->moduleAddress == other.moduleAddress &&
             this->networkAddress == other.networkAddress);
 }

 bool operator==(const ZbpAddress& a, const ZbpAddress& b) {
     return a.isEqual(b);
 }

 QString ZbpAddress::toTrame() const {
     QString result = "";
     QString tmp = "";
     QString strAddress = QString::number(moduleAddress, 10);
     if(strAddress.count() < 4) {
         for(int i = 0; i < 4 - strAddress.count(); i++)
             tmp += "0";
         strAddress = tmp+strAddress;
     }
     QString strNetwork = QString::number(networkAddress, 10);
     if(strNetwork.count() < 2) {
         tmp = "";
         for(int i = 0; i < 2 - strNetwork.count(); i++) {
             tmp += "0";
         }
         strNetwork = tmp+strNetwork;
     }
     result += strNetwork;
     result += strAddress;
     return result;
 }




































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

#include "XAPNetworkProperties.h"


//--------------------------------------------------------------------------------------

XAPNetworkProperties::XAPNetworkProperties() {
    this->diffusionAddress = "";
    this->diffusionPort = -1;
    this->appAddress.setVendor("");
    //qDebug()<<"Build XAPNetworkProperties: appAddress.getVendor() = "<<appAddress.getVendor();
}

//--------------------------------------------------------------------------------------

XAPNetworkProperties::XAPNetworkProperties(const QString& fileName) {
    int hbInterval, diffusionPort;
    QString diffusionAddress, xapAddress;
    QString xmlResult;
    QString url = fileName;
    bool enableHeartBeat;
    QXmlQuery query;
    query.bindVariable("url", QXmlItem(QVariant(url)));
    query.setQuery("declare variable $url external;"
                   "doc($url)/configuration/xap-network/heartbeat/text()");
    if (query.isValid() && query.evaluateTo(&xmlResult)) {
            if(xmlResult.contains("\n")) xmlResult.remove("\n");
            bool convertOk;
            hbInterval = xmlResult.toInt(&convertOk);
            if(!convertOk) {
                qDebug() << "[WARNING] "+AT+" xap-network heartbeat interval bad value.";
                qDebug() << "using default interval (60 000 msec)";
                hbInterval = 60000;
            }
    }
    else
        throw error::InitializationException("XML query failed", AT, true);

    query.setQuery("declare variable $url external;"
                   "doc($url)/configuration/xap-network/diffusion-address/text()");
    if(query.isValid() && query.evaluateTo(&xmlResult)) {
            if(xmlResult.contains("\n")) xmlResult.remove("\n");
            diffusionAddress = xmlResult;
    }
    else {
        qDebug() << "[WARNING] "+AT+" diffusion address not found";
        qDebug() << "using default (255.255.255.255)";
        diffusionAddress = "";
    }

    query.setQuery("declare variable $url external;"
                   "doc($url)/configuration/xap-network/diffusion-port/text()");
    if(query.isValid() && query.evaluateTo(&xmlResult)) {
        if(xmlResult.contains("\n")) xmlResult.remove("\n");
        bool convertOk;
        diffusionPort = xmlResult.toInt(&convertOk);
        if(!convertOk) {
            qDebug() << "[WARNING] "+AT+" diffusion port not found";
            qDebug() << "using default (3639)";
            diffusionPort = 3639;
        }
    }
    else {
        qDebug() << "[WARNING] "+AT+" diffusion port not found";
        qDebug() << "using default (3639)";
        diffusionPort = 3639;
    }


    query.setQuery("declare variable $url external;"
                   "doc($url)/configuration/xap-network/xap-address/text()");
    if(query.isValid() && query.evaluateTo(&xmlResult)) {
            if(xmlResult.contains("\n")) xmlResult.remove("\n");
            xapAddress = xmlResult;
    }
    else {
        throw error::InitializationException("xap-address not found...", AT, true);
    }

    query.setQuery("declare variable $url external;"
                   "doc($url)/configuration/xap-network/heartbeat/@enabled");
    if(query.isValid() && query.evaluateTo(&xmlResult)) {
            if(xmlResult.contains("\n"))
                xmlResult.remove("\n");
            enableHeartBeat = (xmlResult != "false");
    }
    else {
        qDebug() << "[WARNING] "+AT+" enable parameter for xap-heartbeat cannot be found...";
        qDebug() << "...using default value (true)";
        enableHeartBeat = true;
    }

    setAppAddress(XAPAddress::fromString(xapAddress));
    setHeartBeatInterval(hbInterval);
    setEnableHeartBeat(enableHeartBeat);
    setDiffusionAddress(diffusionAddress);
    setDiffusionPort(diffusionPort);

    int i = 0;
    i = 1;


}

//--------------------------------------------------------------------------------------

XAPNetworkProperties::XAPNetworkProperties(const QString &diffusionAddress, int diffusionPort) {
    this->diffusionAddress = diffusionAddress;
    this->diffusionPort = diffusionPort;
    this->heartBeatInterval = 0;
    this->enableHeartBeat = false;
}

//--------------------------------------------------------------------------------------

XAPNetworkProperties::XAPNetworkProperties(const XAPNetworkProperties &other) {
    this->appAddress = other.appAddress;
    this->diffusionAddress = other.diffusionAddress;
    this->diffusionPort = other.diffusionPort;
    this->heartBeatInterval = other.heartBeatInterval;
    this->enableHeartBeat = other.enableHeartBeat;
}

//--------------------------------------------------------------------------------------

XAPNetworkProperties& XAPNetworkProperties::operator =(const XAPNetworkProperties& other) {
    this->appAddress = other.appAddress;
    this->diffusionAddress = other.diffusionAddress;
    this->diffusionPort = other.diffusionPort;
    this->heartBeatInterval = other.heartBeatInterval;
    this->enableHeartBeat = other.enableHeartBeat;
    return *this;
}

//--------------------------------------------------------------------------------------

bool XAPNetworkProperties::isEqual(const XAPNetworkProperties &other) const {
    return (this->diffusionAddress == other.diffusionAddress &&
            this->diffusionPort == other.diffusionPort);
}

//--------------------------------------------------------------------------------------

bool operator==(const XAPNetworkProperties& a, const XAPNetworkProperties& b) {
    return a.isEqual(b);
}

//--------------------------------------------------------------------------------------

QString XAPNetworkProperties::toString() const {
    QString str = "[XAP NETWORK PROPERTIES]\n";
    str += "diffusion:"+this->diffusionAddress+":"+this->diffusionPort+"\n";
    str += "heartbeat:";
    str += (enableHeartBeat ? "enabled\n" : "disabled\n");
    return str;
}

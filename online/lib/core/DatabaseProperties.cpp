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

#include "DatabaseProperties.h"

//--------------------------------------------------------------------------------------

DatabaseProperties::DatabaseProperties() {
    databaseName = "";
    hostAddress = "";
    hostPort = -1;
    userName = "";
    password = "";
}

//--------------------------------------------------------------------------------------

DatabaseProperties::DatabaseProperties(const QString &databaseName, const QString &hostAddress, int hostPort, const QString &userName, const QString &password) {
    this->databaseName = databaseName;
    this->hostAddress = hostAddress;
    this->hostPort = hostPort;
    this->userName = userName;
    this->password = password;
}

//--------------------------------------------------------------------------------------

DatabaseProperties::DatabaseProperties(const QString &fileName) {
    QString databaseName, hostAddress, userName, password, xmlResult;
    int hostPort;
    bool fileExists = QFile::exists(fileName);
    if(!fileExists) {
        throw error::InitializationException(" Configuration file not found !", AT, true);
    }

    QString url = fileName;
    QXmlQuery query;
    query.bindVariable("url", QXmlItem(QVariant(url)));
    query.setQuery("declare variable $url external;"
                   "doc($url)/configuration/database/databasename/text()");
    if (query.isValid()) {
        if (query.evaluateTo(&xmlResult)) {
            if(xmlResult.contains("\n"))
                xmlResult.remove("\n");
            databaseName = xmlResult;
        }
    }
    else
        throw error::InitializationException("XML query failed", AT, true);
    //qDebug() << "[DBInitRead::importDatabaseProperties] invalid query !";

    query.setQuery("declare variable $url external;"
                   "doc($url)/configuration/database/hostaddress/text()");
    if (query.isValid()) {
        if (query.evaluateTo(&xmlResult)) {
            if(xmlResult.contains("\n"))
                xmlResult.remove("\n");
            hostAddress = xmlResult;
        }
    }
    else
        throw error::InitializationException("XML query failed", AT, true);
    //qDebug() << "[DBInitRead::importDatabaseProperties] invalid query !";

    query.setQuery("declare variable $url external;"
                   "doc($url)/configuration/database/username/text()");
    if (query.isValid()) {
        if (query.evaluateTo(&xmlResult)) {
            if(xmlResult.contains("\n"))
                xmlResult.remove("\n");
            userName = xmlResult;
        }
    }
    else
        throw error::InitializationException("XML query failed", AT, true);
    //qDebug() << "[DBInitRead::importDatabaseProperties] invalid query !";

    query.setQuery("declare variable $url external;"
                   "doc($url)/configuration/database/password/text()");
    if (query.isValid()) {
        if (query.evaluateTo(&xmlResult)) {
            password = xmlResult;
            if(xmlResult.contains("\n"))
                xmlResult.remove("\n");
        }
    }
    else
        throw error::InitializationException("XML query failed", AT, true);
    //qDebug() << "[DBInitRead::importDatabaseProperties] invalid query !";

    query.setQuery("declare variable $url external;"
                   "doc($url)/configuration/database/hostport/text()");
    if (query.isValid()) {
        if (query.evaluateTo(&xmlResult)) {
            if(xmlResult.contains("\n")) xmlResult.remove("\n");
            bool conversionOK;
            hostPort = xmlResult.toInt(&conversionOK);
            if(!conversionOK)
                throw error::InitializationException("unable to convert hostport from string to integer", AT, true);
            //qDebug() << "[DBInitRead::importDatabaseProperties] error: unable to convert hostport from string to integer";
        }
    }
    else
        throw error::InitializationException("XML query failed", AT, true);
    //qDebug() << "[DBInitRead::importDatabaseProperties] invalid query !";
    this->setDatabaseName(databaseName.trimmed());
    this->setHostAddress(hostAddress.trimmed());
    this->setHostPort(hostPort);
    this->setUserName(userName.trimmed());
    this->setPassword(password.trimmed());
#if defined _ZB_DEBUG_
    qDebug() << toString();
#endif
}

//--------------------------------------------------------------------------------------

DatabaseProperties::DatabaseProperties(const DatabaseProperties &other) {
    this->databaseName = other.databaseName;
    this->hostAddress = other.hostAddress;
    this->hostPort = other.hostPort;
    this->userName = other.userName;
    this->password = other.password;
}

//--------------------------------------------------------------------------------------

DatabaseProperties::~DatabaseProperties() {

}

//--------------------------------------------------------------------------------------

DatabaseProperties& DatabaseProperties::operator=(const DatabaseProperties& other) {
    this->databaseName = other.databaseName;
    this->hostAddress = other.hostAddress;
    this->hostPort = other.hostPort;
    this->userName = other.userName;
    this->password = other.password;
    return *this;
}

//--------------------------------------------------------------------------------------

bool DatabaseProperties::isEqual(const DatabaseProperties &other) const {
    return (this->databaseName == other.databaseName &&
            this->hostAddress == other.hostAddress &&
            this->hostPort == other.hostPort &&
            this->userName == other.userName &&
            this->password == other.password);
}

//--------------------------------------------------------------------------------------

QString DatabaseProperties::toString() const {
    QString str = "[DATABASE PROPERTIES]\n";
    str += "databaseName="+databaseName+"\n";
    str += "host="+hostAddress+":"+QString::number(hostPort)+"\n";
    str += "userName="+userName+"\n";
    str += "password="+password+"\n";
    return str;
}

//--------------------------------------------------------------------------------------

bool operator==(const DatabaseProperties& a, const DatabaseProperties& b) {
    return a.isEqual(b);
}

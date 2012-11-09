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

#include "DBInitRead.h"

//--------------------------------------------------------------------------------------

DBInitRead::DBInitRead(AbstractApplication* owner)
{
    //Valeurs d'init par defaut
    this->configDirectory = "./config/";
    this->configFileName = ""+qApp->applicationName()+".xml";
    this->owner = owner;
    xapProperties.setAppAddress(XAPAddress("", "", "", ""));
}

//--------------------------------------------------------------------------------------

void DBInitRead::importDatabaseProperties(const QString& fileName) {
    dbProperties = DatabaseProperties(fileName);
}

//--------------------------------------------------------------------------------------

void DBInitRead::importXAPNetworkProperties(const QString& fileName) {
    xapProperties = XAPNetworkProperties(fileName);
}


//--------------------------------------------------------------------------------------

void DBInitRead::importZigbusNetworkProperties(const QString& fileName) {
    zbpProperties = ZbpNetworkProperties(fileName);
}

//--------------------------------------------------------------------------------------

void DBInitRead::initialize() {
    importDatabaseProperties(""+configDirectory+configFileName);
    importXAPNetworkProperties(""+configDirectory+configFileName);
    importZigbusNetworkProperties(""+configDirectory+configFileName);
}

//--------------------------------------------------------------------------------------

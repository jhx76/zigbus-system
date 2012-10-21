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

#ifndef QUERYBEAN_H
#define QUERYBEAN_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>
#include <QList>

#include <core/Device.h>
#include <core/Module.h>
#include <core/model/LocationModel.h>
#include <core/model/SymbolicTypeModel.h>
#include <core/model/SymbolicNetworkModel.h>
#include <core/model/HardwareTypeModel.h>
#include <core/model/ZigbusNetworkModel.h>
#include <core/Error.h>
#include <core/SysUtils.h>
#include <core/DatabaseProperties.h>

#include <QDebug>
class QueryBean
{
private:
    QSqlDatabase database;

    DatabaseProperties databaseProperties;

public:
    /**
      @throw SqlException when the database connection raise an error at connection.
      */
    QueryBean(const QString& userName, const QString& password, const QString& databaseName,
              const QString& host, const QString& databaseDriver = "QMYSQL");


    /**

      */
    QueryBean(const DatabaseProperties& databaseProperties);

    /**
      destructeur par defaut
      */
    ~QueryBean();

    /**
      @throw SqlException
      */
    QList<Module> buildModuleList(const QString& networkId = "00");

    /**
      @throw SqlException
      */
    QList<LocationModel> getAllLocations();

    /**
      @throw SqlException
      */
    QList<SymbolicTypeModel> getAllSymbolicTypes();

    /**
      @throw SqlException
      */
    QList<HardwareTypeModel> getAllHardwareTypes();

    /**
      @throw SqlException
      */
    QList<ZigbusNetworkModel> getAllZigbusNetworks();

    /**
      @throw SqlException
      */
    QList<SymbolicNetworkModel> getAllSymbolicNetworks();

    /**

      */
    int insertDevice(const Device& device);

    /**

      */
    int updateDevice(const Device& deviceInEdition, const Device& tmpDevice);

    /**

      */
    int updateModule(const Module& moduleInEdition, const Module& tmpModule);

    /**

      */
    int deleteModule(const Module& moduleToDelete);

    /**

      */
    int deleteDevice(const Device& deviceToDelete);

};

#endif // QUERYBEAN_H

#include "QueryBean.h"


QueryBean::QueryBean(const QString& userName, const QString& password, const QString& databaseName, const QString& host, const QString& driver) {
    database = QSqlDatabase::addDatabase(driver);
    database.setDatabaseName(databaseName);
    database.setHostName(host);
    //database->setPort(port);
    database.setUserName(userName);
    database.setPassword(password);

    if(!database.open())
        throw error::SqlException(database.lastError().text(), AT);
}


QList<Module> QueryBean::buildModuleList(const QString &networkId) {
    QString sModule = "SELECT t_module.moduleid AS label, "
                        "t_module.nbpin_numeric, "
                        "t_module.nbpin_analogic, "
                        "t_module.description, "
                        "t_zigbus_network.network_id "
                        "FROM t_module "
                        "INNER JOIN t_zigbus_network on t_module.et_zigbus_netid = t_zigbus_network.id "
                        "WHERE t_zigbusNetwork = '"+networkId+"'";

    QList<Module> moduleList;
    QSqlQuery moduleQuery(sModule, database);

    while(moduleQuery.next()) {
        Module tmpModule;
        tmpModule.setNumericIOCount(moduleQuery.value(moduleQuery.record().indexOf("nbpin_numeric")).toInt());
        tmpModule.setAnalogIOCount(moduleQuery.value(moduleQuery.record().indexOf("nbpin_analogic")).toInt());
        tmpModule.setLabel(moduleQuery.value(moduleQuery.record().indexOf("label")).toString());
        tmpModule.setZigbusNetworkId(moduleQuery.value(moduleQuery.record().indexOf("network_id")).toString());
        moduleList.append(tmpModule);
    }

    for(int imod = 0; imod < moduleList.count(); imod++) {
        QString sqry =  "SELECT main_pin, optional_pin, t_hardware_type.label AS hardware_type, "
                        "t_symbolic_type.label AS symbolic_type, t_symbolic_network.label AS symbolic_network, "
                        "t_location.label AS location, instance "
                        "FROM t_device "
                        "INNER JOIN t_module ON t_device.et_module = t_module.id "
                        "INNER JOIN t_hardware_type ON t_device.et_hardware_type = t_hardware_type.id "
                        "INNER JOIN t_symbolic_type ON t_device.et_symbolic_type = t_symbolic_type.id "
                        "INNER JOIN t_symbolic_network ON t_device.et_symbolic_network = t_symbolic_network.id "
                        "INNER JOIN t_location ON t_device.et_location = t_location.id "
                        "INNER JOIN t_zigbus_network ON t_module.et_zigbus_netid = t_zigbus_network.id "
                        "WHERE t_zigbus_network.network_id ='"+moduleList[imod].getZigbusNetworkId()+"' "
                        "AND t_module.moduleid = '"+moduleList[imod].getLabel()+"'";

        QSqlQuery queryDevice(sqry);
        while(queryDevice.next()) {
            Device tmpDevice;
            tmpDevice.setVendor(queryDevice.value(queryDevice.record().indexOf("symbolic_network")).toString());
            tmpDevice.setType(queryDevice.value(queryDevice.record().indexOf("symbolic_type")).toString());
            tmpDevice.setLocation(queryDevice.value(queryDevice.record().indexOf("location")).toString());
            tmpDevice.setInstance(queryDevice.value(queryDevice.record().indexOf("instance")).toString());
            tmpDevice.setPinId(queryDevice.value(queryDevice.record().indexOf("main_pin")).toString());
            tmpDevice.setPinType(queryDevice.value(queryDevice.record().indexOf("hardware_type")).toString());
            tmpDevice.setPtrModule(&moduleList[imod]);
            moduleList[imod].append(tmpDevice);

        }
    }
    return moduleList;
}

QList<LocationModel> QueryBean::getAllLocations() {
    QString query = "SELECT id, label, description FROM t_location";
    QSqlQuery sqlQuery(query, database);
    QList<LocationModel> result;
    while(sqlQuery.next()) {
        LocationModel tmpModel;
        bool ok;
        tmpModel.setId(sqlQuery.value(sqlQuery.record().indexOf("id")).toInt(&ok));
        if(!ok)
            throw error::SqlException("unable to convert type of 'variant' to 'integer'", AT);

        if(sqlQuery.value(sqlQuery.record().indexOf("label")).isNull())
            throw error::SqlException("the field t_location.label is null id("+QString::number(tmpModel.getId())+")", AT);
        else
            tmpModel.setLabel(sqlQuery.value(sqlQuery.record().indexOf("label")).toString());

        if(sqlQuery.value(sqlQuery.record().indexOf("description")).isNull())
            tmpModel.setDescription("");
        else
            tmpModel.setDescription(sqlQuery.value(sqlQuery.record().indexOf("description")).toString());
        result.append(tmpModel);
    }
    return result;
}

QList<SymbolicTypeModel> QueryBean::getAllSymbolicTypes() {
    QString s = "SELECT id, label, description FROM t_symbolic_type";
    QSqlQuery query(s, database);
    QList<SymbolicTypeModel> result;
    while(query.next()) {
        SymbolicTypeModel tmpModel;
        bool ok;
        tmpModel.setId(query.value(query.record().indexOf("id")).toInt(&ok));
        if(!ok)
            throw error::SqlException("unable to convert type of 'variant' to 'integer'", AT);

        if(query.value(query.record().indexOf("label")).isNull())
            throw error::SqlException("the field t_location.label is null id("+QString::number(tmpModel.getId())+")", AT);
        else
            tmpModel.setLabel(query.value(query.record().indexOf("label")).toString());

        if(query.value(query.record().indexOf("description")).isNull())
            tmpModel.setDescription("");
        else
            tmpModel.setDescription(query.value(query.record().indexOf("description")).toString());
        result.append(tmpModel);
    }
    return result;
}

QList<HardwareTypeModel> QueryBean::getAllHardwareTypes() {
    QString s = "SELECT id, label, description FROM t_hardware_type";
    QSqlQuery query(s, database);
    QList<HardwareTypeModel> result;

    while(query.next()) {
        HardwareTypeModel tmpModel;
        bool ok;
        tmpModel.setId(query.value(query.record().indexOf("id")).toInt(&ok));
        if(!ok)
            throw error::SqlException("unable to convert type of 'variant' to 'integer'", AT);

        if(query.value(query.record().indexOf("label")).isNull())
            throw error::SqlException("the field t_location.label is null id("+QString::number(tmpModel.getId())+")", AT);
        else
            tmpModel.setLabel(query.value(query.record().indexOf("label")).toString());

        if(query.value(query.record().indexOf("description")).isNull())
            tmpModel.setDescription("");
        else
            tmpModel.setDescription(query.value(query.record().indexOf("description")).toString());
        result.append(tmpModel);
    }
    return result;
}

QList<ZigbusNetworkModel> QueryBean::getAllZigbusNetworks() {
    QString s = "SELECT id, label, description FROM t_zigbus_network";
    QSqlQuery query(s, database);
    QList<ZigbusNetworkModel> result;

    while(query.next()) {
        ZigbusNetworkModel tmpModel;
        bool ok;
        tmpModel.setId(query.value(query.record().indexOf("id")).toInt(&ok));
        if(!ok)
            throw error::SqlException("unable to convert type of 'variant' to 'integer'", AT);

        if(query.value(query.record().indexOf("label")).isNull())
            throw error::SqlException("the field t_location.label is null id("+QString::number(tmpModel.getId())+")", AT);
        else
            tmpModel.setLabel(query.value(query.record().indexOf("label")).toString());

        if(query.value(query.record().indexOf("description")).isNull())
            tmpModel.setDescription("");
        else
            tmpModel.setDescription(query.value(query.record().indexOf("description")).toString());
        result.append(tmpModel);
    }
    return result;

}

QList<SymbolicNetworkModel> QueryBean::getAllSymbolicNetworks() {
    QString s = "SELECT id, label, description FROM t_symbolic_network";
    QSqlQuery query(s, database);
    QList<SymbolicNetworkModel> result;

    while(query.next()) {
        SymbolicNetworkModel tmpModel;
        bool ok;
        tmpModel.setId(query.value(query.record().indexOf("id")).toInt(&ok));
        if(!ok)
            throw error::SqlException("unable to convert type of 'variant' to 'integer'", AT);

        if(query.value(query.record().indexOf("label")).isNull())
            throw error::SqlException("the field t_location.label is null id("+QString::number(tmpModel.getId())+")", AT);
        else
            tmpModel.setLabel(query.value(query.record().indexOf("label")).toString());

        if(query.value(query.record().indexOf("description")).isNull())
            tmpModel.setDescription("");
        else
            tmpModel.setDescription(query.value(query.record().indexOf("description")).toString());
        result.append(tmpModel);
    }
    return result;
}




#include "QueryBean.h"


QueryBean::QueryBean(const QString& userName, const QString& password, const QString& databaseName, const QString& host, const QString& driver) {
    databaseProperties.setDatabaseName(databaseName);
    databaseProperties.setHostAddress(host);
    databaseProperties.setPassword(password);
    databaseProperties.setUserName(userName);

    database = QSqlDatabase::addDatabase(driver);
    database.setDatabaseName(databaseName);
    database.setHostName(host);
    database.setUserName(userName);
    database.setPassword(password);

    if(!database.open())
        throw error::SqlException("opening database", database.lastError().text(), AT);
}

//-----------------------------------------------------------------------

QueryBean::QueryBean(const DatabaseProperties &databaseProperties) {
    this->databaseProperties = databaseProperties;
    database = QSqlDatabase::addDatabase("QMYSQL", "zigbus_admin_connection");
    database.setDatabaseName(databaseProperties.getDatabaseName());
    database.setHostName(databaseProperties.getHostAddress());
    database.setUserName(databaseProperties.getUserName());
    database.setPassword(databaseProperties.getPassword());
    if(!database.open())
        throw error::SqlException("opening database", database.lastError().text(), AT);
}

//-----------------------------------------------------------------------

QueryBean::~QueryBean() {
    database.close();
}

//-----------------------------------------------------------------------

QList<Module> QueryBean::buildModuleList(const QString &networkId) {
    QString sModule = "SELECT t_module.moduleid AS label, "
                        "t_module.nbpin_numeric AS nbpin_numeric, "
                        "t_module.nbpin_analogic AS nbpin_analogic, "
                        "t_module.description AS description, "
                        "t_zigbus_network.label AS network_id "
                        "FROM t_module "
                        "INNER JOIN t_zigbus_network on t_module.et_zigbus_netid = t_zigbus_network.id "
                        "WHERE t_zigbus_network.label = '"+networkId+"'";

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

    qDebug() << QString::number(moduleList.count())+" modules found.";
    for(int imod = 0; imod < moduleList.count(); imod++) {
        QString sqry =  "SELECT main_pin, optional_pin, t_hardware_type.label AS hardware_type, subtype, "
                        "t_symbolic_type.label AS symbolic_type, t_symbolic_network.label AS symbolic_network, "
                        "t_location.label AS location, instance "
                        "FROM t_device "
                        "INNER JOIN t_module ON t_device.et_module = t_module.id "
                        "INNER JOIN t_hardware_type ON t_device.et_hardware_type = t_hardware_type.id "
                        "INNER JOIN t_symbolic_type ON t_device.et_symbolic_type = t_symbolic_type.id "
                        "INNER JOIN t_symbolic_network ON t_device.et_symbolic_network = t_symbolic_network.id "
                        "INNER JOIN t_location ON t_device.et_location = t_location.id "
                        "INNER JOIN t_zigbus_network ON t_module.et_zigbus_netid = t_zigbus_network.id "
                        "WHERE t_zigbus_network.label ='"+moduleList[imod].getZigbusNetworkId()+"' "
                        "AND t_module.moduleid = '"+moduleList[imod].getLabel()+"'";

        QSqlQuery queryDevice(sqry, database);
        while(queryDevice.next()) {
            Device tmpDevice;
            tmpDevice.setVendor(queryDevice.value(queryDevice.record().indexOf("symbolic_network")).toString());
            tmpDevice.setType(queryDevice.value(queryDevice.record().indexOf("symbolic_type")).toString());
            tmpDevice.setLocation(queryDevice.value(queryDevice.record().indexOf("location")).toString());
            tmpDevice.setInstance(queryDevice.value(queryDevice.record().indexOf("instance")).toString());
            tmpDevice.setPinId(queryDevice.value(queryDevice.record().indexOf("main_pin")).toString());
            tmpDevice.setOptionalId(queryDevice.value(queryDevice.record().indexOf("optional_pin")).toString());
            tmpDevice.setPinType(queryDevice.value(queryDevice.record().indexOf("hardware_type")).toString());
            tmpDevice.setPinSubType(queryDevice.value(queryDevice.record().indexOf("subtype")).toString());
            tmpDevice.setPtrModule(&moduleList[imod]);
            moduleList[imod].append(tmpDevice);

        }
        qDebug() << "in module "+moduleList[imod].getLabel()+": "+QString::number(moduleList[imod].deviceCount())+" devices";
    }
    return moduleList;
}

//-----------------------------------------------------------------------

QList<LocationModel> QueryBean::getAllLocations() {
    QString query = "SELECT id, label, description FROM t_location";
    QSqlQuery sqlQuery(query, database);
    QList<LocationModel> result;
    while(sqlQuery.next()) {
        LocationModel tmpModel;
        bool ok;
        tmpModel.setId(sqlQuery.value(sqlQuery.record().indexOf("id")).toInt(&ok));
        if(!ok)
            throw error::SqlException(query, "unable to convert type of 'variant' to 'integer'", AT);

        if(sqlQuery.value(sqlQuery.record().indexOf("label")).isNull())
            throw error::SqlException(query, "the field t_location.label is null id("+QString::number(tmpModel.getId())+")", AT);
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

//-----------------------------------------------------------------------

QList<SymbolicTypeModel> QueryBean::getAllSymbolicTypes() {
    QString s = "SELECT id, label, description FROM t_symbolic_type";
    QSqlQuery query(s, database);
    QList<SymbolicTypeModel> result;
    while(query.next()) {
        SymbolicTypeModel tmpModel;
        bool ok;
        tmpModel.setId(query.value(query.record().indexOf("id")).toInt(&ok));
        if(!ok)
            throw error::SqlException(s, "unable to convert type of 'variant' to 'integer'", AT);

        if(query.value(query.record().indexOf("label")).isNull())
            throw error::SqlException(s, "the field t_location.label is null id("+QString::number(tmpModel.getId())+")", AT);
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

//-----------------------------------------------------------------------

QList<HardwareTypeModel> QueryBean::getAllHardwareTypes() {
    QString s = "SELECT id, label, description FROM t_hardware_type";
    QSqlQuery query(s, database);
    QList<HardwareTypeModel> result;

    while(query.next()) {
        HardwareTypeModel tmpModel;
        bool ok;
        tmpModel.setId(query.value(query.record().indexOf("id")).toInt(&ok));
        if(!ok)
            throw error::SqlException(s, "unable to convert type of 'variant' to 'integer'", AT);

        if(query.value(query.record().indexOf("label")).isNull())
            throw error::SqlException(s, "the field t_location.label is null id("+QString::number(tmpModel.getId())+")", AT);
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

//-----------------------------------------------------------------------

QList<ZigbusNetworkModel> QueryBean::getAllZigbusNetworks() {
    QString s = "SELECT id, label, description FROM t_zigbus_network";
    QSqlQuery query(s, database);
    QList<ZigbusNetworkModel> result;

    while(query.next()) {
        ZigbusNetworkModel tmpModel;
        bool ok;
        tmpModel.setId(query.value(query.record().indexOf("id")).toInt(&ok));
        if(!ok)
            throw error::SqlException(s, "unable to convert type of 'variant' to 'integer'", AT);

        if(query.value(query.record().indexOf("label")).isNull())
            throw error::SqlException(s, "the field t_location.label is null id("+QString::number(tmpModel.getId())+")", AT);
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

//-----------------------------------------------------------------------

QList<SymbolicNetworkModel> QueryBean::getAllSymbolicNetworks() {
    QString s = "SELECT id, label, description FROM t_symbolic_network";
    QSqlQuery query(s, database);
    QList<SymbolicNetworkModel> result;

    while(query.next()) {
        SymbolicNetworkModel tmpModel;
        bool ok;
        tmpModel.setId(query.value(query.record().indexOf("id")).toInt(&ok));
        if(!ok)
            throw error::SqlException(s, "unable to convert type of 'variant' to 'integer'", AT);

        if(query.value(query.record().indexOf("label")).isNull())
            throw error::SqlException(s, "the field t_location.label is null id("+QString::number(tmpModel.getId())+")", AT);
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

//-----------------------------------------------------------------------

int QueryBean::insertDevice(const Device &device) {
    QString s =
    "INSERT INTO t_device (et_module, et_symbolic_network, et_symbolic_type, et_hardware_type, et_location, instance, main_pin, optional_pin, subtype) "
    "VALUES ((SELECT id FROM t_module WHERE t_module.moduleid='"+device.getPtrModule()->getLabel()+"'), "
    "(SELECT id FROM t_symbolic_network WHERE t_symbolic_network.label='"+device.getVendor()+"'), "
    "(SELECT id FROM t_symbolic_type WHERE t_symbolic_type.label='"+device.getType()+"'), "
    "(SELECT id FROM t_hardware_type WHERE t_hardware_type.label='"+device.getPinType()+"'), "
    "(SELECT id FROM t_location WHERE t_location.label='"+device.getLocation()+"'), "
    "'"+device.getInstance()+"', "
    "'"+device.getPinId()+"', "
    "'"+device.getOptionalId()+"', "
            "'"+device.getPinSubType()+"');";
    QSqlQuery query(this->database);
    bool ok = query.exec(s);
    if(!ok)
        throw error::SqlException(s, query.lastError().text(), AT);
    return query.numRowsAffected();
}

//-----------------------------------------------------------------------

int QueryBean::updateDevice(const Device &deviceInEdition, const Device &tmpDevice) {
    bool ok;
    int deviceId = -1;
    QString s = "SELECT t_device.id "
            "FROM t_device "
            "INNER JOIN t_module ON t_device.et_module = t_module.id "
            "INNER JOIN t_symbolic_network ON t_device.et_symbolic_network=t_symbolic_network.id "
            "INNER JOIN t_symbolic_type ON t_device.et_symbolic_type=t_symbolic_type.id "
            "INNER JOIN t_location ON t_device.et_location = t_location.id "
            "INNER JOIN t_hardware_type ON t_device.et_hardware_type = t_hardware_type.id "
            "INNER JOIN t_zigbus_network ON t_module.et_zigbus_netid = t_zigbus_network.id "
            "WHERE t_symbolic_network.label = '"+deviceInEdition.getVendor()+"' "
            "AND t_symbolic_type.label = '"+deviceInEdition.getType()+"' "
            "AND t_location.label = '"+deviceInEdition.getLocation()+"' "
            "AND t_hardware_type.label = '"+deviceInEdition.getPinType()+"' "
            "AND t_zigbus_network.label = '"+deviceInEdition.getPtrModule()->getZigbusNetworkId()+"' "
            "AND t_module.moduleid = '"+deviceInEdition.getPtrModule()->getLabel()+"' "
            "AND t_device.instance = '"+deviceInEdition.getInstance()+"' "
            "AND t_device.main_pin='"+deviceInEdition.getPinId()+"' "
            "AND t_device.optional_pin='"+deviceInEdition.getOptionalId()+"' "
            "AND t_device.subtype='"+deviceInEdition.getPinSubType()+"' LIMIT 1;";
    QSqlQuery queryId(s, database);
    if(queryId.next()) {
        deviceId =queryId.value(queryId.record().indexOf("id")).toInt(&ok);
        if(!ok)
            throw error::SqlException(s, "No valid data imported ...", AT);
    }
    else throw error::SqlException(s, "no valid data imported ...", AT);
    s = "UPDATE t_device SET "
            "et_symbolic_network=(SELECT id FROM t_symbolic_network WHERE label='"+tmpDevice.getVendor()+"'), "
            "et_symbolic_type=(SELECT id FROM t_symbolic_type WHERE label='"+tmpDevice.getType()+"'), "
            "et_location=(SELECT id FROM t_location WHERE label='"+tmpDevice.getLocation()+"'), "
            "instance='"+tmpDevice.getInstance()+"', "
            "et_module=(SELECT id FROM t_module WHERE moduleid='"+tmpDevice.getPtrModule()->getLabel()+"' AND "
            "               et_zigbus_netid=(SELECT id FROM t_zigbus_network WHERE label ='"+tmpDevice.getPtrModule()->getZigbusNetworkId()+"')), "
            "main_pin='"+tmpDevice.getPinId()+"', "
            "optional_pin='"+tmpDevice.getOptionalId()+"', "
            "et_hardware_type=(SELECT id FROM t_hardware_type WHERE label='"+tmpDevice.getPinType()+"'), "
            "t_device.subtype='"+tmpDevice.getPinSubType()+"' "
            "WHERE id="+QString::number(deviceId);
    QSqlQuery query(database);
    ok = query.exec(s);
    if(!ok)
        throw error::SqlException(s, query.lastError().text(), AT);
    return query.numRowsAffected();
}

//-----------------------------------------------------------------------

int QueryBean::updateModule(const Module &moduleInEdition, const Module &tmpModule) {
    int moduleId = -1;
    bool ok;
    QString s ="SELECT t_module.id FROM t_module "
            "INNER JOIN t_zigbus_network ON t_module.et_zigbus_netid=t_zigbus_network.id "
            "WHERE moduleid='"+moduleInEdition.getLabel()+"' "
            "AND t_zigbus_network.label='"+moduleInEdition.getZigbusNetworkId()+"' LIMIT 1;";

    QSqlQuery queryId(s, database);
    if(queryId.next()) {
        moduleId = queryId.value(queryId.record().indexOf("id")).toInt(&ok);
        if(!ok)
            throw error::SqlException(s, "No valid data imported ...", AT);
    }
    else
        throw error::SqlException(s, "No valid data imported ...", AT);

    s = "UPDATE t_module SET "
            "moduleid='"+tmpModule.getLabel()+"', "
            "nbpin_numeric="+tmpModule.getNumericIOCount()+", "
            "nbpin_analogic="+tmpModule.getAnalogIOCount()+", "
            "et_zigbus_netid=(SELECT id FROM t_zigbus_network WHERE label='"+tmpModule.getZigbusNetworkId()+"') "
            "WHERE id="+QString::number(moduleId)+";";
    QSqlQuery queryUpdate(database);
    ok = queryUpdate.exec(s);
    if(!ok)
        throw error::SqlException(s, queryUpdate.lastError().text(), AT);
    return queryUpdate.numRowsAffected();
}

//-----------------------------------------------------------------------

int QueryBean::deleteDevice(const Device &deviceToDelete) {
    QString s = "DELETE FROM t_device "
            "WHERE et_module=(SELECT id FROM t_module WHERE moduleid='"+deviceToDelete.getPtrModule()->getLabel()+"' AND "
            "       et_zigbus_netid=(SELECT id FROM t_zigbus_network WHERE label='"+deviceToDelete.getPtrModule()->getZigbusNetworkId()+"')) "
            "AND et_symbolic_type=(SELECT id FROM t_symbolic_type WHERE label='"+deviceToDelete.getType()+"') "
            "AND et_symbolic_network=(SELECT id FROM t_symbolic_network WHERE label='"+deviceToDelete.getVendor()+"') "
            "AND et_location=(SELECT id FROM t_location WHERE label='"+deviceToDelete.getLocation()+"') "
            "AND et_hardware_type=(SELECT id FROM t_hardware_type WHERE label='"+deviceToDelete.getPinType()+"') "
            "AND main_pin='"+deviceToDelete.getPinId()+"' "
            "AND optional_pin='"+deviceToDelete.getOptionalId()+"' "
            "AND subtype='"+deviceToDelete.getPinSubType()+"'";

    QSqlQuery query(database);
    bool ret = query.exec(s);
    if(!ret)
        throw error::SqlException(s, query.lastError().text(), AT);
    return query.numRowsAffected();
}

//-----------------------------------------------------------------------

int QueryBean::deleteModule(const Module &moduleToDelete) {
    QString s = "DELETE FROM t_module WHERE moduleid='"+moduleToDelete.getLabel()+"' "
            "AND et_zigbus_netid=(SELECT id FROM t_zigbus_network WHERE label='"+moduleToDelete.getZigbusNetworkId()+"') ";
    QSqlQuery query(database);
    bool ret = query.exec(s);
    if(!ret)
        throw error::SqlException(s, query.lastError().text(), AT);
    return query.numRowsAffected();
}

//-----------------------------------------------------------------------

QList<HardwareSubTypeModel> QueryBean::getAllHardwareSubtypes() {
    QString s = "SELECT t_hardware_subtype.id as subtypeid, subtype as subtypelabel, t_hardware_type.label as typelabel, t_hardware_subtype.description as description "
            "FROM t_hardware_subtype "
            "INNER JOIN t_hardware_type on t_hardware_subtype.et_hardware_type = t_hardware_type.id";
    QSqlQuery query(s, database);
    QList<HardwareSubTypeModel> resultList;
    while(query.next()) {
        HardwareSubTypeModel tmp;
        tmp.setId(query.value(query.record().indexOf("subtypeid")).toInt());
        tmp.setSubtype(query.value(query.record().indexOf("subtypelabel")).toString());
        tmp.setCorrespondingType(query.value(query.record().indexOf("typelabel")).toString());
        tmp.setDescription(query.value(query.record().indexOf("description")).toString());
        resultList.append(tmp);
    }
    return resultList;
}

//-----------------------------------------------------------------------

int QueryBean::insertModule(const Module &module) {
    QString s = "INSERT INTO t_module (moduleid, nbpin_numeric, nbpin_analogic, description, et_zigbus_netid) "
            "VALUES('"+module.getLabel()+"', "+QString::number(module.getNumericIOCount())+", "+
            QString::number(module.getAnalogIOCount())+", '', "
            "(SELECT id FROM t_zigbus_network WHERE label='"+module.getZigbusNetworkId()+"'))";
    QSqlQuery query(database);
    bool ok = query.exec(s);
    if(!ok)
        throw error::SqlException(s, query.lastError().text(), AT, false);
    return query.numRowsAffected();
}

//-----------------------------------------------------------------------

int QueryBean::insertLocation(const LocationModel &location) {
    QString s = "INSERT INTO t_location (label, description) "
            "VALUES('"+location.getLabel()+"', '"+location.getDescription()+"')";
    qDebug() << s;
    QSqlQuery query(database);
    bool ok = query.exec(s);
    if(!ok)
        throw error::SqlException(s, query.lastError().text(), AT, false);
    qDebug() << "location inserted " << location.getLabel();
    return query.numRowsAffected();
}

//-----------------------------------------------------------------------

int QueryBean::deleteLocation(const LocationModel& location) {
    QString s = "DELETE FROM t_location WHERE id="+QString::number(location.getId())+" AND label='"+location.getLabel()+"'";
    qDebug() << s;
    QSqlQuery query(database);
    bool ok = query.exec(s);
    if(!ok) throw error::SqlException(s, query.lastError().text(), AT, false);
    qDebug() << "location deleted: " << location.getLabel();
    return query.numRowsAffected();

}

//-----------------------------------------------------------------------

int QueryBean::insertSymbolicType(const SymbolicTypeModel &type) {
    QString s = "INSERT INTO t_symbolic_type (label, description)";
    s += " VALUES('"+type.getLabel()+"', '"+type.getDescription()+"');";
    qDebug() << s;
    QSqlQuery query(database);
    bool ok = query.exec(s);
    if(!ok)
        throw error::SqlException(s, query.lastError().text(), AT, false);
    qDebug() << "type inserted: " << type.getLabel();
    return query.numRowsAffected();
}

//-----------------------------------------------------------------------

int QueryBean::updateSymbolicTypeById(const SymbolicTypeModel &type, int id) {
    QString s = "UPDATE t_symbolic_type SET label='"+type.getLabel()+"', description='"+type.getDescription()+"'";
    s += " WHERE id="+QString::number(id);
    qDebug() << s;
    QSqlQuery query(database);
    bool ok = query.exec(s);
    if(!ok)
        throw error::SqlException(s, query.lastError().text(), AT, false);
    qDebug() << "symbolic type updated. id="+QString::number(id);
    return query.numRowsAffected();
}

//-----------------------------------------------------------------------

int QueryBean::deleteSymbolicTypeById(int id) {
    QString s = "DELETE FROM t_symbolic_type WHERE id="+QString::number(id)+";";
    qDebug() << s;
    QSqlQuery query(database);
    bool ok = query.exec(s);
    if(!ok)
        throw error::SqlException(s, query.lastError().text(), AT, false);
    qDebug() << "symbolic type deleted: " << id;
    return query.numRowsAffected();
}

//-----------------------------------------------------------------------

#include "DBInitRead.h"

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

//--------------------------------------------------------------------------------------

XAPNetworkProperties::XAPNetworkProperties() {
    this->diffusionAddress = "";
    this->diffusionPort = -1;
    this->appAddress.setVendor("");
    //qDebug()<<"Build XAPNetworkProperties: appAddress.getVendor() = "<<appAddress.getVendor();
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

//--------------------------------------------------------------------------------------

DBInitRead::DBInitRead(AbstractApplication* owner)
{
    //Valeurs d'init par defaut
    this->configDirectory = "./config/";
    this->configFileName = ""+qApp->applicationName()+".xml";
    this->owner = owner;
    xapProperties.setAppAddress(XAPAddress("", "", "", ""));
    //qDebug() << "Building DBInitRead: xapProperties.getAppAddress().getVendor() = "<<xapProperties.getAppAddress().getVendor();
}

//--------------------------------------------------------------------------------------

void DBInitRead::importDatabaseProperties(const QString& fileName) {
    QString databaseName, hostAddress, userName, password, xmlResult;
    int hostPort;
    bool fileExists = QFile::exists(fileName);
    if(!fileExists) {
        throw error::InitializationException(""+AT+" Configuration file not found !", true);
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
        throw error::InitializationException(""+AT+" query failed", true);
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
        throw error::InitializationException(""+AT+" query failed", true);
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
        throw error::InitializationException(""+AT+" query failed", true);
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
        throw error::InitializationException(""+AT+" query failed", true);
    //qDebug() << "[DBInitRead::importDatabaseProperties] invalid query !";

    query.setQuery("declare variable $url external;"
                   "doc($url)/configuration/database/hostport/text()");
    if (query.isValid()) {
        if (query.evaluateTo(&xmlResult)) {
            if(xmlResult.contains("\n")) xmlResult.remove("\n");
            bool conversionOK;
            hostPort = xmlResult.toInt(&conversionOK);
            if(!conversionOK)
                throw error::InitializationException(""+AT+" unable to convert hostport from string to integer", true);
            //qDebug() << "[DBInitRead::importDatabaseProperties] error: unable to convert hostport from string to integer";
        }
    }
    else
        throw error::InitializationException(""+AT+" query failed", true);
    //qDebug() << "[DBInitRead::importDatabaseProperties] invalid query !";
    this->dbProperties.setDatabaseName(databaseName.trimmed());
    this->dbProperties.setHostAddress(hostAddress.trimmed());
    this->dbProperties.setHostPort(hostPort);
    this->dbProperties.setUserName(userName.trimmed());
    this->dbProperties.setPassword(password.trimmed());
#if defined _ZB_DEBUG_
    qDebug() << dbProperties.toString();
#endif
}

//--------------------------------------------------------------------------------------

void DBInitRead::importXAPNetworkProperties(const QString& fileName) {
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
        throw error::InitializationException(""+AT+" query failed !", true);

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
        throw error::InitializationException(""+AT+" xap-address not found...", true);
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

    xapProperties.setAppAddress(XAPAddress::fromString(xapAddress));
    xapProperties.setHeartBeatInterval(hbInterval);
    xapProperties.setEnableHeartBeat(enableHeartBeat);
    xapProperties.setDiffusionAddress(diffusionAddress);
    xapProperties.setDiffusionPort(diffusionPort);

    int i = 0;
    i = 1;
}


//--------------------------------------------------------------------------------------

void DBInitRead::importZigbusNetworkProperties(const QString& fileName) {

}

//--------------------------------------------------------------------------------------

void DBInitRead::initialize() {
    importDatabaseProperties(""+configDirectory+configFileName);
    importXAPNetworkProperties(""+configDirectory+configFileName);
}

//--------------------------------------------------------------------------------------

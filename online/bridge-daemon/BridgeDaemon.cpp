#include "BridgeDaemon.h"

BridgeDaemon::BridgeDaemon(QObject* parent) : QObject(parent), AbstractApplication()
{
    qApp->setApplicationName("bridge-daemon");
    qApp->setApplicationVersion("0.0.1a");
    xapNetwork = NULL;
    DAT = NULL;
    queryBean = NULL;
    zbpNetwork = NULL;
    iniParam = new DBInitRead(this);
}

void BridgeDaemon::initializeApplication() {
    try {
        // Creation du point d'acces pour le dialogue xAP
        XAPNetworkProperties xapProperties;
        iniParam->initialize();
        xapProperties = iniParam->getXapProperties();
        xapNetwork = new XAPNetwork("xap", xapProperties, this);
        connect(xapNetwork, SIGNAL(messageReceived(GenMessage*,QString)), this, SLOT(processMessage(GenMessage*, QString)));
        connect(this, SIGNAL(messageForApps(GenMessage*)), xapNetwork, SLOT(sendMessage(GenMessage*)));
        connect(xapNetwork, SIGNAL(toDisplay(QString)), this, SLOT(display(QString)));
        xapNetwork->initialize();
        //xapNetwork->startListening();
        xapNetwork->start();

        //Creation du point d'acces pour le réseau de module zigbus
        queryBean = new QueryBean(iniParam->getDbProperties());
        DAT = new SingleDAT(queryBean);
        GenMessageFactory::setDeviceAddressTranslator(DAT);

        zbpNetwork = new ZbpNetwork(DAT, iniParam->getZbpProperties(), this);
        connect(this, SIGNAL(messageForDevices(GenMessage*)), zbpNetwork, SLOT(sendMessage(GenMessage*)));
        connect(zbpNetwork, SIGNAL(messageReceived(GenMessage*,QString)), this, SLOT(processMessage(GenMessage*,QString)));
        connect(zbpNetwork, SIGNAL(toDisplay(QString)), this, SLOT(display(QString)));
        zbpNetwork->initialize();
        zbpNetwork->start();
    }
    catch(const error::InitializationException &e) {
        qDebug() << e.toString();
        if(e.isCritic()) {
            qDebug() << "CRITICAL ERROR: " << qApp->applicationName()+qApp->applicationVersion()+" will now quit";
            clearAndQuit();
        }
    }
    catch(const error::SysException& exception) {
        qDebug() << exception.toString();
    }
}

void BridgeDaemon::clearAndQuit() {
    if(iniParam != NULL)
        delete iniParam;
    if(xapNetwork != NULL)
        delete xapNetwork;
    qApp->quit();
    if(zbpNetwork != NULL)
        delete zbpNetwork;
    if(DAT != NULL)
        delete DAT;
    if(queryBean != NULL)
        delete queryBean;
}


void BridgeDaemon::processMessage(GenMessage* message, QString networkId) {
    if(networkId == "xap") {
        emit messageForDevices(message);
    }
    else if(networkId == "zigbus") {
        emit messageForApps(message);
    }
}

void BridgeDaemon::display(QString message) {
    qDebug() << message;
}

#include "BridgeDaemon.h"

BridgeDaemon::BridgeDaemon(QObject* parent) : QObject(parent), AbstractApplication()
{
    qApp->setApplicationName("bridge-daemon");
    qApp->setApplicationVersion("0.0.1a");
    this->xapNetwork = NULL;
    this->iniParam = new DBInitRead(this);
}

void BridgeDaemon::initializeApplication() {
    try {
        XAPNetworkProperties xapProperties;
        iniParam->initialize();
        xapProperties = iniParam->getXapProperties();
        xapNetwork = new XAPNetwork(QString("xap-bridge"), xapProperties, this);
        connect(xapNetwork, SIGNAL(messageReceived(GenMessage*,QString)), this, SLOT(processMessage(GenMessage*, QString)));
        connect(xapNetwork, SIGNAL(toDisplay(QString)), this, SLOT(display(QString)));
        xapNetwork->initialize();
        xapNetwork->startListening();

    }
    catch(const error::InitializationException &e) {
        qDebug() << e.toString();
        if(e.isCritical()) {
            qDebug() << "CRITICAL ERROR";
            qDebug() << qApp->applicationName()+qApp->applicationVersion()+" will now quit";
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
}


void BridgeDaemon::processMessage(GenMessage* message, QString networkId) {
    if(networkId == "xap-bridge") {
        //Traitement des messages venant du reseau xAP
        qDebug() << "message received:\n";
        qDebug() << message->toString();
        //Translation xap -> zigbus + Transmission sur zigbus
        //zigbusNetwork->sendMessage(message);
    }
    else if(networkId == "zigbus-bridge") {
        //Traitement des messages venant des Devices
        //==> Translation zigbus -> xAP + transmission sur xAP
        //xapNetwork->sendMessage(message);
    }
}

void BridgeDaemon::display(QString message) {
    qDebug() << message;
}

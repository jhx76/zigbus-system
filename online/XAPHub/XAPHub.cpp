#include "XAPHub.h"

XAPHub::XAPHub() {
    zAppInfo = new ApplicationInformation("xap-hub", _EVOLUTIONS);

    network = NULL;
    initRead = NULL;
}


XAPHub::~XAPHub() {
    if(network) {
        network->stopListening();
        delete network;
    }
}


void XAPHub::initializeApplication() {
    initRead = new DBInitRead(this);
    initRead->initialize();

    XAPNetworkProperties properties = initRead->getXapProperties();
    network = new XAPNetwork("", properties, this);
    connect(network, SIGNAL(toDisplay(QString)), this, SLOT(display(QString)));
    connect(network, SIGNAL(xapMsgReceived(XAPMessage)), this, SLOT(messageReceived(XAPMessage)));
    network->startListening();
}


void XAPHub::display(QString s) {
    qDebug() << s;
}

void XAPHub::messageReceived(XAPMessage message) {

}

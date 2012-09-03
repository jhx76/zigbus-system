
#include "XAPNetwork.h"

XAPNetwork::XAPNetwork(const QString& networkId, QObject * parent) : GenNetwork(networkId, parent)
{
    sendHeartBeat = false;
    socket = new QUdpSocket();
    this->hbTimer = new QTimer(this);
    hbTimer->setInterval(5000);
    hostAddress = "";
    QObject::connect(this->hbTimer, SIGNAL(timeout()), this, SLOT(sendHeartBeatMessage()));
}

XAPNetwork::XAPNetwork(const QString& networkId, const XAPNetworkProperties &properties, QObject *parent)
    : GenNetwork(networkId, parent) {
    sendHeartBeat = properties.isEnableHeartBeat();
    hostAddress = properties.getDiffusionAddress();
    port = properties.getDiffusionPort();

    if(hostAddress.isEmpty())
        hostAddress = "255.255.255.255";

    socket = new QUdpSocket();
    hbTimer = new QTimer(this);
    hbInterval = properties.getHeartBeatInterval();
    hbTimer->setInterval(properties.getHeartBeatInterval()*1000);
    appAddress = properties.getAppAddress();
    QObject::connect(this->hbTimer, SIGNAL(timeout()), this, SLOT(sendHeartBeatMessage()));
}

//----------------------------------------------------------------------------

XAPNetwork::~XAPNetwork(){
    if(socket != NULL) {
        if(socket->isOpen()) {
            disconnect(socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
            disconnect(this, SIGNAL(xapMsgReceived(XAPMessage)), this, SLOT(processXAPMessage(XAPMessage)));
            socket->close();
        }
        delete this->socket;
    }

    if(hbTimer) {
        hbTimer->stop();
        disconnect(this->hbTimer, SIGNAL(timeout()), this, SLOT(sendHeartBeatMessage()));
        delete hbTimer;
    }
}

//----------------------------------------------------------------------------

void XAPNetwork::initialize(const QString& ipaddress) {
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    QObject::connect(this, SIGNAL(xapMsgReceived(XAPMessage)), this, SLOT(processXAPMessage(XAPMessage)));
}

//----------------------------------------------------------------------------

void XAPNetwork::stopListening() {
    this->listening = false;
}

//----------------------------------------------------------------------------

bool XAPNetwork::startListening() {
    bool connected = false;
    emit toDisplay(QString(AT)+"connecting xAP Network...");

    while(!connected && port <= HUB_AREA_MAX) {
        connected = socket->bind(port, QUdpSocket::DefaultForPlatform);
        if(!connected) {
            emit toDisplay(AT+"unable to connect on port "+QString::number(port)+". Socket already used. Trying another port...");
            if(port < HUB_AREA_MIN) port = HUB_AREA_MIN;
            else port++;
        }
    }
    listening = connected;

    if(connected) {
        emit toDisplay(AT+"connection successful: ");
        emit toDisplay(AT+"diffusion-address="+hostAddress+
                       "|diffusion-port="+QString::number(STANDARD_PORT)+
                       "|listening on "+QString::number(port)+
                       "|heartbeat interval "+QString::number(hbInterval)+
                       "|enable heartbeat: "+((sendHeartBeat)?"true":"false"));

        if(sendHeartBeat) {
            //QObject::connect(this->hbTimer, SIGNAL(timeout()), this, SLOT(sendHeartBeatMessage()));
            sendHeartBeatMessage();
            this->hbTimer->start();
            //emit toDisplay(AT+"hbTimer started ? "+(hbTimer->isActive()?"true":"false")+" ("+QString::number(hbTimer->interval())+")");
        }
    }
    else {
        emit toDisplay(AT+"Connection failed... Socket Already used.");
    }
    return connected;
}

//----------------------------------------------------------------------------

bool XAPNetwork::isListening() {
    return listening;
}

//----------------------------------------------------------------------------

void XAPNetwork::sendMessage(GenMessage* message) {
    emit displayMessageSent(message->toString());
    XAPMessage messageToSend = translate(message);
    this->sendMessage(messageToSend);
}

//----------------------------------------------------------------------------

void XAPNetwork::sendMessage(const XAPMessage &message) {
    if(listening) {
        QByteArray datagram;
        QString str;
        str = message.toString();
        datagram = datagram.append(str);
        socket->writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, STANDARD_PORT);
        emit toDisplay("message sent:\n"+message.toString());
    }
    else
        throw error::SysException(AT+"[XAPNetwork::sendMessage] Unable to send message: network is not listening");
}

//----------------------------------------------------------------------------

void XAPNetwork::sendHeartBeatMessage(const GenAddress& source) {

    if(listening) {
        QString xapsource = source.getVendor();
        xapsource += ".";
        xapsource += source.getType();
        xapsource += ".";
        xapsource += source.getLocation();
        if(!source.getInstance().isEmpty()) {
            xapsource += ":";
            xapsource += source.getInstance();
        }
        sendMessage(XAPHeartBeatMessage(xapsource));
    }
}

//----------------------------------------------------------------------------

void XAPNetwork::sendHeartBeatMessage() {
  //  qDebug() << AT << "enter in slot sendHeartBeatMessage()";
    if(listening) {
        XAPHeartBeatMessage message(appAddress.toString());
        message.setInterval(hbInterval);
        message.setPort(port);
        sendMessage(message);
    }
}

//----------------------------------------------------------------------------

QString XAPNetwork::lastError() {
    return socket->errorString();
}

//----------------------------------------------------------------------------

void XAPNetwork::processDatagram(QByteArray _datagram) {
    try {
        XAPMessage msgreceived = XAPMessage::fromString(QString(_datagram.constData()));
        emit xapMsgReceived(msgreceived);
    }
    catch(QString & str) {
        emit this->toDisplay(str);
    }
}

//----------------------------------------------------------------------------

void XAPNetwork::readPendingDatagrams() {
    while (socket->hasPendingDatagrams() && listening) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        qDebug() << datagram;
        processDatagram(datagram);
    }
}

//----------------------------------------------------------------------------

void XAPNetwork::processXAPMessage(XAPMessage xapmessage) {
    try {
        GenMessage* genMessage = GenMessageFactory::createMessage(xapmessage);
        if(genMessage != NULL) {
            emit this->messageReceived(genMessage, getNetworkId());
            //QString str = "From: "+getNetworkId();
            //str += genMessage->toString();
            //emit this->toDisplay(str);
        }
    }
    catch(QString & str) {
        emit this->toDisplay(str);
    }
}

//----------------------------------------------------------------------------

XAPMessage XAPNetwork::translate(GenMessage *message) {
    XAPMessage xapMessage;
    QString xapsource;
    QString xaptarget;

    GenMessage::TypeMessage type = message->getTypeMessage();
    if(type == GenMessage::Command) {
        //CommandMessage* commandMessage = (CommandMessage*)message;

        CommandMessage* commandMessage = static_cast<CommandMessage*>(message);
        if(!commandMessage)
            throw error::TranslationException("Bad identified type", message);
        xapMessage.setClass("xapbsc.cmd");
        xapsource = commandMessage->getSource().getVendor()+".";
        xapsource += commandMessage->getSource().getType()+".";
        xapsource += commandMessage->getSource().getLocation();
        xapsource += (commandMessage->getSource().getInstance().isEmpty()
                      ? ""
                      : ":"+commandMessage->getSource().getInstance());
        xapMessage.setSource(xapsource);

        xaptarget = commandMessage->getTarget().getVendor()+".";
        xaptarget += commandMessage->getTarget().getType()+".";
        xaptarget += commandMessage->getTarget().getLocation();
        xaptarget += (commandMessage->getTarget().getInstance().isEmpty()
                      ? ""
                      : ":"+commandMessage->getTarget().getInstance());
        xapMessage.setTarget(xaptarget);

        XAPBlock cmdBlock;
        cmdBlock.setBlockname("command");
        if(commandMessage->contains(gen::state))
            cmdBlock.append("state", commandMessage->getParam(gen::state));
        if(commandMessage->contains(gen::level))
            cmdBlock.append("level", commandMessage->getParam(gen::level));
        if(commandMessage->contains(gen::time)) {
            cmdBlock.append("time", commandMessage->getParam(gen::time));
            if(commandMessage->contains(gen::unit))
                cmdBlock.append("unit", commandMessage->getParam(gen::unit));
        }
        if(commandMessage->contains(gen::text))
            cmdBlock.append("text", commandMessage->getParam(gen::text));
        if(commandMessage->contains(gen::displaytext))
            cmdBlock.append("displaytext", commandMessage->getParam(gen::displaytext));
        xapMessage.append(cmdBlock);
        return xapMessage;
    }
    else if(type == GenMessage::Ack) {
        throw error::TranslationException("Unable to translate AckMessage with this version",message);
    }
    else if(type == GenMessage::Configuration) {
        //! @todo Définir l'implementation du systeme de configuration des appareils (XML ou SGBD)
        ConfigurationMessage *configMessage = static_cast<ConfigurationMessage*>(message);
        if(!configMessage)
            throw error::TranslationException("Error when casting GenMessage into ConfigurationMessage");

        xapMessage.setClass("zb.configure");
        xapsource = configMessage->getSource().getVendor()+".";
        xapsource += configMessage->getSource().getType()+".";
        xapsource += configMessage->getSource().getLocation();
        xapsource += (configMessage->getSource().getInstance().isEmpty()
                      ? ""
                      : ":"+configMessage->getSource().getInstance());
        xapMessage.setSource(xapsource);

        xaptarget = configMessage->getTarget().getVendor()+".";
        xaptarget += configMessage->getTarget().getType()+".";
        xaptarget += configMessage->getTarget().getLocation();
        xaptarget += (configMessage->getTarget().getInstance().isEmpty()
                      ? ""
                      : ":"+configMessage->getTarget().getInstance());
        xapMessage.setTarget(xaptarget);

        XAPBlock block;
        block.setBlockname("configure");
        xapMessage.append(block);
        //throw error::TranslationException("Unable to translate ConfigurationMessage with this version",message);
    }
    else if(type == GenMessage::Event) {
        //! @todo EventMessage translation to xAP
        throw error::TranslationException("Unable to translate EventMessage with this version",message);
    }
    else if(type == GenMessage::HeartBeat) {
        //! @todo HeartBeatMessage translation to xAP
        throw error::TranslationException("Unable to translate HeartBeatMessage with this version",message);
    }
    else if(type == GenMessage::Information) {
        //! @todo InformationMessage translation to xAP
        throw error::TranslationException("Unable to translate InformationMessage with this version",message);
    }
    else if(type == GenMessage::Initialisation) {
        throw error::TranslationException("Unable to translate InitialisationMessage with this version",message);
    }
    else if(type == GenMessage::Ping) {
        throw error::TranslationException("Unable to translate PingMessage with this version",message);
    }
    else if(type == GenMessage::PingResult) {
        throw error::TranslationException("Unable to translate PingResultMessage with this version",message);
    }
    else if(type == GenMessage::Query) {
        //! @todo QueryMessage translation to xAP
        throw error::TranslationException("Unable to translate QueryMessage with this version",message);
    }
    else
        throw error::TranslationException("Unknown message type.", message);
}

//----------------------------------------------------------------------------

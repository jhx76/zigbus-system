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

void XAPNetwork::run() {
    startListening();
    exec();
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
    try {
        //emit displayMessageSent(message->toString());
        XAPMessage messageToSend = translate(message);
        this->sendMessage(messageToSend);
    }
    catch(const error::TranslationException& exception) {
        qDebug() << exception.toString();
    }
}

//----------------------------------------------------------------------------

void XAPNetwork::sendMessage(const XAPMessage &message) {
    if(listening) {
        QByteArray datagram;
        QString str;
        str = message.toString();
        qDebug() << str;
        datagram = datagram.append(str);
        socket->writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, STANDARD_PORT);
        //emit toDisplay("message sent:\n"+message.toString());
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
        //qDebug() << datagram;
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
        CommandMessage* commandMessage = static_cast<CommandMessage*>(message);
        if(!commandMessage)
            throw error::TranslationException(message, "Bad identified type", AT);
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
        if(commandMessage->getCommandType() == "configuration")
            cmdBlock.setBlockname("configuration");
        else
            cmdBlock.setBlockname("output.state");
        if(commandMessage->contains(gen::state))
            cmdBlock.append("state", commandMessage->getParam(gen::state));
        if(commandMessage->contains(gen::level))
            cmdBlock.append("level", commandMessage->getParam(gen::level));
        if(commandMessage->contains(gen::time)) {
            cmdBlock.append("time", commandMessage->getParam(gen::time));
            if(commandMessage->contains(gen::unit))
                cmdBlock.append("unit", commandMessage->getParam(gen::unit));
        }
        if(commandMessage->contains(gen::position))
            cmdBlock.append("position", commandMessage->getParam(gen::position));
        if(commandMessage->contains(gen::func))
            cmdBlock.append("func", commandMessage->getParam(gen::func));
        if(commandMessage->contains(gen::type))
            cmdBlock.append("type", commandMessage->getParam(gen::type));
        if(commandMessage->contains(gen::stype))
            cmdBlock.append("stype", commandMessage->getParam(gen::stype));
        if(commandMessage->contains(gen::text))
            cmdBlock.append("text", commandMessage->getParam(gen::text));
        if(commandMessage->contains(gen::displaytext))
            cmdBlock.append("displaytext", commandMessage->getParam(gen::displaytext));
        if(commandMessage->contains(gen::id)) {
            if(commandMessage->getTarget().getType() == "heater" || commandMessage->getTarget().getType() == "chauffage")
                cmdBlock.append("alter+", commandMessage->getParam(id));
            else if(commandMessage->getTarget().getType() == "servo")
                cmdBlock.append("idcmd", commandMessage->getParam(id));
            else
                cmdBlock.append("id", commandMessage->getParam(id));
        }
        if(commandMessage->contains(gen::id2)) {
            if(commandMessage->getTarget().getType() == "heater"
                    || commandMessage->getTarget().getType() == "chauffage")
                cmdBlock.append("alter-", commandMessage->getParam(id2));
            else if(commandMessage->getTarget().getType() == "servo")
                cmdBlock.append("idpuis", commandMessage->getParam(id2));
            else
                cmdBlock.append("id2", commandMessage->getParam(id2));
        }

        xapMessage.append(cmdBlock);
    }
    else if(type == GenMessage::Event) {
        EventMessage* eventMessage = static_cast<EventMessage*>(message);
        if(!eventMessage)
            throw error::TranslationException(message, "Bad identified type", AT);
        xapMessage.setClass("xapbsc.event");

        if(eventMessage->getTypeEvent() == "init") {
            XAPBlock block("output.state");
            block.append("state", "on");
            xapMessage.append(block);
            xapsource = eventMessage->getSource().getVendor()+".";
            xapsource += eventMessage->getSource().getType()+".";
            xapsource += eventMessage->getSource().getLocation();
            xapsource += (eventMessage->getSource().getInstance().isEmpty()
                          ? ""
                          : ":"+eventMessage->getSource().getInstance());
            xapMessage.setSource(xapsource);
        }
        else
            throw error::TranslationException(message, "unknown event type", AT);
    }
    else if(type == GenMessage::Information) {
        //! @todo InformationMessage translation to xAP
        throw error::TranslationException(message, "Unable to translate InformationMessage with this version", AT);
    }
    else if(type == GenMessage::Query) {
        //! @todo QueryMessage translation to xAP
        throw error::TranslationException(message, "Unable to translate QueryMessage with this version", AT);
    }
    else
        throw error::TranslationException(message, "Unknown message type.", AT);

    delete message;
    return xapMessage;
}

//----------------------------------------------------------------------------

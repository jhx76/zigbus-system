#ifndef _XAPNETWORK_H
#define _XAPNETWORK_H

#include <QUdpSocket>
#include <QTimer>

// pour les traitements des objets generiques
#include <com/common/GenNetwork.h>
#include <com/common/GenAddress.h>
#include <com/common/GenMessageFactory.h>

// les types de messages generiques
#include <com/common/ConfigurationMessage.h>
#include <com/common/CommandMessage.h>
#include <com/common/EventMessage.h>
#include <com/common/InformationMessage.h>
#include <com/common/QueryMessage.h>
#include <com/common/HeartBeatMessage.h>

#include <com/xap/XAPHeartBeatMessage.h>
#include <com/xap/XAPMessage.h>
#include <core/SysUtils.h>
#include <core/DBInitRead.h>

#include <core/Error.h>


#define STANDARD_PORT   3639

#define HUB_AREA_MIN      49152
#define HUB_AREA_MAX      49182

/**
  @class XAPNetwork
  @author jhx
  @date 26/09/2011
  */
class XAPNetwork : public GenNetwork {
    Q_OBJECT
private:
    /**
      The network access. As the xAP Protocol is embedded in UDP Broadcasts, the XAPNetwork is associated to a UDP socket.
      */
    QUdpSocket* socket;

    /**

      */
    QTimer* hbTimer;

    /**

      */
    int hbInterval;

    /**

      */
    QString hostAddress;

    /**

      */
    int port;

    /**

      */
    bool listening;

    /**

      */
    bool sendHeartBeat;

    /**

      */
    XAPAddress appAddress;




public:
    /**
      Default constructor.
      */
    explicit XAPNetwork(const QString& networkId, QObject * parent = 0);

    /**

      */
    XAPNetwork(const QString& networkId, const XAPNetworkProperties &properties, QObject *parent);

    /**
      Default destructor.
      */
    virtual ~XAPNetwork();

    /**

      */
    XAPMessage translate(GenMessage* message);

    /**

      */
    virtual void initialize(const QString& address="");

    /**

      */
    virtual QString lastError();

    /**

      */
    int getHbInterval() { return hbInterval; }

    /**

      */
    void setHbInterval(int i) { hbInterval = i; }

signals:
    /**
      signal emitted when a xAP message has been received from the network socket.
      */
    void xapMsgReceived(XAPMessage message);

    /**
      signal emitted when a string character has been received on the socket.
      */
    void toDisplay(QString);

    /**

      */
    void displayMessageSent(QString);

public slots:
    /**

      */
    virtual bool startListening();

    /**

      */
    virtual bool isListening();

    /**

      */
    virtual void stopListening();

    /**
      process the datagram received on the socket
      */
    void processDatagram(QByteArray _datagram);

    /**
      process a XAPMessage that has been received, and constructs a ZBMessage from it.
      */
    void processXAPMessage(XAPMessage xapmessage);

    /**
      Send a xAP message object throught the network (UDP broadcast).
      */
    void sendMessage(const XAPMessage &message);

    /**

      */
    void readPendingDatagrams();

    /**
      Converts the ZBMessage into a XAPMessage and trys to send its string character representation through the network.
      */
    virtual void sendMessage(GenMessage *message);

    /**
        Send a heartbeat message correspondance.
      */
    void sendHeartBeatMessage();

    /**
      Send a global heart beat notifying the bridge is alive
      */
    void sendHeartBeatMessage(const GenAddress& source);

    /**

      */
    bool isHeartBeatSender() { return sendHeartBeat; }

    /**

      */
    void setHeartBeatSender(bool value) { sendHeartBeat = value; }
};
#endif

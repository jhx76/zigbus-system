#ifndef BRIDGEDAEMON_H
#define BRIDGEDAEMON_H


#include <core/AbstractApplication.h>
#include <core/DBInitRead.h>
#include <core/SysUtils.h>
#include <core/SingleDAT.h>
#include <QString>
#include <com/xap/XAPNetwork.h>
#include <com/xap/XAPHeartBeatMessage.h>
#include <com/xap/XAPMessage.h>
#include <com/zbp/ZbpMessage.h>
#include <com/zbp/ZbpNetwork.h>
#include <com/common/GenMessage.h>

/**
  @class BridgeDaemon
  @author jhx
  @brief Demon s'executant sur le bridge entre le réseau LAN et le réseau Zigbus. Il permet la traduction
  du protocole zigbus en d'autres protocoles domotiques standards tels que xAP ou XPL.

  Comme toute application xAP, le bridge daemon peut utiliser un hub xAP afin de cohabiter avec d'autres applications sur le même host.
  cf. documentation du xAP Hub.


*/

class BridgeDaemon : public QObject, AbstractApplication
{
    Q_OBJECT
private:
    XAPNetwork* xapNetwork;
    ZbpNetwork* zbpNetwork;
    DBInitRead* iniParam;
    SingleDAT* DAT;
    QueryBean* queryBean;

public:
    BridgeDaemon(QObject* parent = 0);

    virtual void initializeApplication();

    void clearAndQuit();

public slots:
    void processMessage(GenMessage* message, QString networkId);

    void display(QString message);

signals:
    void messageForDevices(GenMessage* message);

    void messageForApps(GenMessage* message);

};

#endif // BRIDGEDAEMON_H

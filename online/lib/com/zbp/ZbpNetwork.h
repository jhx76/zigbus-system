#ifndef ZBPNETWORK_H
#define ZBPNETWORK_H

#include <com/common/GenNetwork.h>
#include <com/common/CommandMessage.h>
#include <com/common/EventMessage.h>
#include <com/common/QueryMessage.h>
#include <com/common/InformationMessage.h>
#include <com/common/PingMessage.h>

#include <com/zbp/zigbus.h>
#include <com/zbp/ZbpMessage.h>
#include <com/zbp/ZbpAddress.h>

class ZbpNetwork : public GenNetwork
{
    Q_OBJECT
private:


public:
    /**

      */
    ZbpNetwork(QObject* parent = 0);

    /**

      */
    virtual void initialize(const QString& str);

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

      */
    ZbpMessage convertAndFreeMemory(GenMessage* message);

public slots:
    /**

      */
    virtual void sendMessage(GenMessage* message);




};

#endif // ZBPNETWORK_H

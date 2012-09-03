#ifndef GENNETWORK_H
#define GENNETWORK_H

#include <QObject>
#include <QString>
#include <com/common/GenMessage.h>

/**

  */
class GenNetwork : public QObject
{
    Q_OBJECT
private:
    /**

      */
    QString networkId;

public:
    /**

      */
    GenNetwork(const QString& id = "00", QObject* parent = 0);

    /**

      */
    virtual void initialize(const QString& str) = 0;

    /**

      */
    virtual bool startListening() = 0;

    /**

      */
    virtual bool isListening() = 0;

    /**

      */
    virtual void stopListening() = 0;

    /**

      */
    const QString& getNetworkId() const { return networkId; }

    /**

      */
    void setNetworkId(const QString& id) { networkId = id; }

public slots:
    /**

      */
    virtual void sendMessage(GenMessage* message) = 0;

signals:
    /**

      */
    void messageReceived(GenMessage* message, QString networkId);
};

#endif // GENNETWORK_H

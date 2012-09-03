#ifndef XAPHEARTBEATMESSAGE_H
#define XAPHEARTBEATMESSAGE_H

#include <com/xap/XAPMessage.h>
#include <com/xap/XAPHeader.h>

/**
    @author jhx
    @date 07/11/2011
    @brief A message that notifies all other zigbus entities about its living.
  */
class XAPHeartBeatMessage : public XAPMessage
{
private:
    /**

      */
    int interval;

    /**

      */
    int port;


public:
    /**

      */
    XAPHeartBeatMessage(const QString& xapsource, const QString& uid = "FF123400", int hop = 1, const QString& version = "12");

    /**

      */
    XAPHeartBeatMessage(const XAPHeartBeatMessage& other);

    /**

      */
    virtual ~XAPHeartBeatMessage();

    /**

      */
    virtual QString toString() const;

    /**

      */
    int getPort() const {
        return port;
    }

    /**

      */
    void setPort(int i);
    /**

      */
    int getInterval() { return interval; }

    /**

      */
    void setInterval(int i);
};

#endif // XAPHEARTBEATMESSAGE_H

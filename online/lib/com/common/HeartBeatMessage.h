#ifndef HEARTBEATMESSAGE_H
#define HEARTBEATMESSAGE_H

#include <com/common/GenMessage.h>

class HeartBeatMessage : public GenMessage
{
private:
    int interval;
    int port;
    int pid;

public:
    HeartBeatMessage(const GenAddress& source);

    HeartBeatMessage(const GenAddress& source, int port, int interval, int pid = -1);

    HeartBeatMessage(const HeartBeatMessage& other);

    virtual QString toString();

    int getPort() const { return port; }

    void setPort(int port ) { this->port = port; }

    int getInterval() const { return interval; }

    void setInterval(int interval) { this->interval = interval; }

    int getPid() const { return pid; }

    void setPid(int pid) { this->pid = pid; }

};

#endif // HEARTBEATMESSAGE_H

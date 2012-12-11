#ifndef XAPHUB_H
#define XAPHUB_H
#include <core/AbstractApplication.h>
#include <core/ApplicationInformation.h>
#include <core/DBInitRead.h>

#include <com/xap/XAPNetwork.h>


#define _EVOLUTION   "" \
    "|09/12/2012|1.0.0.0|First compilation ! :)" \

class XAPHub : public AbstractApplication
{
    Q_OBJECT
private:
    XAPNetwork* network;

    DBInitRead* initRead;

    ApplicationInformation* zAppInfo;


public:
    XAPHub();

    virtual ~XAPHub();

    virtual void initializeApplication();

public slots:
    void display(QString);

    void messageReceived(XAPMessage message);


};

#endif // XAPHUB_H

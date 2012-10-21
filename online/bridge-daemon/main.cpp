#include <QtCore/QCoreApplication>
#include <BridgeDaemon.h>
#include <com/zbp/ZbpMessage.h>
#include <QString>
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BridgeDaemon daemon;
    daemon.initializeApplication();
    return a.exec();
}

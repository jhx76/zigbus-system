#include <QtCore/QCoreApplication>

#include <BridgeDaemon.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BridgeDaemon daemon;
    daemon.initializeApplication();
    return a.exec();
}

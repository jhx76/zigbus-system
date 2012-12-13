#include <QtGui/QApplication>
#include <QDate>
#include <QString>
#include "AdminWindow.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AdminWindow w(NULL);
    w.show();

    return a.exec();
}

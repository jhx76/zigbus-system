#include <QApplication>
#include <XAPHub.h>
#include <XAPHubWidget.h>
#include <SlidePanel.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget p;
    XAPHub hub;
    XAPHubWidget w(&hub);
    w.setGeometry(0, 50, 200, 150);
    SlidePanel slide(&w, &p);
    slide.show();
    hub.initialize();
    return a.exec();
}

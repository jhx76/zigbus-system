#-------------------------------------------------
#
# Project created by QtCreator 2012-07-06T17:51:25
#
#-------------------------------------------------

QT       += core gui network xml xmlpatterns

TARGET = XAPHub
CONFIG   -= app_bundle
TEMPLATE = app

#OBJECTS_DIR = ../../bin/BridgeDaemon/build/obj

#MOC_DIR = ../../bin/BridgeDaemon/build/moc

DESTDIR = ../exe

CONFIG(debug, debug|release) {
    TARGET = BridgeDaemond
    DEFINES += ZB_DEBUG
}
else {
    TARGET = BridgeDaemon
}


SOURCES += main.cpp \
    XAPHub.cpp \
    XAPHeader.cpp \
    XAPBlock.cpp \
    SlidePanel.cpp \
    ExceptionManagement.cpp \
    Chaine.cpp \
    XAPNameValuePair.cpp \
    XAPMessage.cpp \
    XAPHubedApplication.cpp \
    XAPHubedApplicationWidget.cpp \
    XAPHubWidget.cpp \
    CountDownLabel.cpp

HEADERS += \
    XAPHub.h \
    XAPHeader.h \
    XAPBlock.h \
    SlidePanel.h \
    ExceptionManagement.h \
    Chaine.h \
    XAPParser.h \
    XAPNameValuePair.h \
    XAPMessage.h \
    XAPHubedApplication.h \
    XAPHubedApplicationWidget.h \
    XAPHubWidget.h \
    CountDownLabel.h

FORMS += \
    XAPHubedApplicationWidget.ui

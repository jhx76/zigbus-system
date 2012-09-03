#-------------------------------------------------
#
# Project created by QtCreator 2012-09-02T21:40:02
#
#-------------------------------------------------

QT       += core xml xmlpatterns network sql

QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../lib/

OBJECTS_DIR = ../../build/bridge-daemon/obj

MOC_DIR = ../../build/bridge-daemon/moc

DESTDIR = ../../bin

CONFIG(debug, debug|release) {
    TARGET = bridge-daemond
    DEFINES += ZB_DEBUG
}
else {
    TARGET = bridge-daemon
}


SOURCES += main.cpp \
    BridgeDaemon.cpp \
    ../lib/com/xap/XAPNetwork.cpp \
    ../lib/com/xap/XAPNameValuePair.cpp \
    ../lib/com/xap/XAPMessage.cpp \
    ../lib/com/xap/XAPHeartBeatMessage.cpp \
    ../lib/com/xap/XAPHeader.cpp \
    ../lib/com/xap/XAPBlock.cpp \
    ../lib/com/xap/XAPUtils.cpp \
    ../lib/com/common/QueryMessage.cpp \
    ../lib/com/common/InformationMessage.cpp \
    ../lib/com/common/HeartBeatMessage.cpp \
    ../lib/com/common/GenNetwork.cpp \
    ../lib/com/common/GenMessageFactory.cpp \
    ../lib/com/common/GenMessage.cpp \
    ../lib/com/common/GenAddress.cpp \
    ../lib/com/common/EventMessage.cpp \
    ../lib/com/common/ConfigurationMessage.cpp \
    ../lib/com/common/CommandMessage.cpp \
    ../lib/core/SysUtils.cpp \
    ../lib/core/Module.cpp \
    ../lib/core/Error.cpp \
    ../lib/core/Device.cpp \
    ../lib/core/DBInitRead.cpp \
    ../lib/core/AbstractApplication.cpp \
    ../lib/com/zbp/ZbpMessage.cpp \
    ../lib/com/zbp/ZbpAddress.cpp

HEADERS += \
    BridgeDaemon.h \
    ../lib/com/xap/XAPNetwork.h \
    ../lib/com/xap/XAPNameValuePair.h \
    ../lib/com/xap/XAPMessage.h \
    ../lib/com/xap/XAPHeartBeatMessage.h \
    ../lib/com/xap/XAPHeader.h \
    ../lib/com/xap/XAPCste.h \
    ../lib/com/xap/XAPBlock.h \
    ../lib/com/xap/XAPUtils.h \
    ../lib/com/common/QueryMessage.h \
    ../lib/com/common/InformationMessage.h \
    ../lib/com/common/HeartBeatMessage.h \
    ../lib/com/common/GenNetwork.h \
    ../lib/com/common/GenMessageFactory.h \
    ../lib/com/common/GenMessage.h \
    ../lib/com/common/GenAddress.h \
    ../lib/com/common/EventMessage.h \
    ../lib/com/common/ConfigurationMessage.h \
    ../lib/com/common/CommandMessage.h \
    ../lib/core/SysUtils.h \
    ../lib/core/QueryBean.h \
    ../lib/core/Module.h \
    ../lib/core/Error.h \
    ../lib/core/Device.h \
    ../lib/core/DBInitRead.h \
    ../lib/core/AbstractApplication.h \
    ../doxygen-mainpage.h \
    ../lib/com/zbp/ZbpMessage.h \
    ../lib/com/zbp/ZbpAddress.h

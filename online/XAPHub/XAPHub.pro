#-------------------------------------------------
#
# Project created by QtCreator 2012-12-09T13:54:52
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = XAPHub
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../lib

SOURCES += main.cpp \
    ../lib/com/xap/XAPUtils.cpp \
    ../lib/com/xap/XAPNetworkProperties.cpp \
    ../lib/com/xap/XAPNetwork.cpp \
    ../lib/com/xap/XAPNameValuePair.cpp \
    ../lib/com/xap/XAPMessageException.cpp \
    ../lib/com/xap/XAPMessage.cpp \
    ../lib/com/xap/XAPHeartBeatMessage.cpp \
    ../lib/com/xap/XAPHeader.cpp \
    ../lib/com/xap/XAPException.cpp \
    ../lib/com/xap/XAPBlock.cpp \
    ../lib/core/SysUtils.cpp \
    ../lib/core/Error.cpp \
    ../lib/core/DBInitRead.cpp \
    ../lib/core/ApplicationInformation.cpp \
    ../lib/core/AbstractApplication.cpp \
    XAPHub.cpp

HEADERS += \
    ../lib/com/xap/XAPUtils.h \
    ../lib/com/xap/XAPNetworkProperties.h \
    ../lib/com/xap/XAPNetwork.h \
    ../lib/com/xap/XAPNameValuePair.h \
    ../lib/com/xap/XAPMessageException.h \
    ../lib/com/xap/XAPMessage.h \
    ../lib/com/xap/XAPHeartBeatMessage.h \
    ../lib/com/xap/XAPHeader.h \
    ../lib/com/xap/XAPException.h \
    ../lib/com/xap/XAPCste.h \
    ../lib/com/xap/XAPBlock.h \
    ../lib/core/SysUtils.h \
    ../lib/core/Error.h \
    ../lib/core/DBInitRead.h \
    ../lib/core/ApplicationInformation.h \
    ../lib/core/AbstractApplication.h \
    XAPHub.h

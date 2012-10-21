#-------------------------------------------------
#
# Project created by QtCreator 2012-09-02T21:40:02
#
#-------------------------------------------------

QT       += core gui xml xmlpatterns network sql debug

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

unix|win32:HEADERS                 += ../lib/com/serial/qextserialbase.h \
                          ../lib/com/serial/qextserialport.h \
                          ../lib/com/serial/qextserialenumerator.h

unix|win32:SOURCES                 += ../lib/com/serial/qextserialbase.cpp \
                          ../lib/com/serial/qextserialport.cpp \
                          ../lib/com/serial/qextserialenumerator.cpp

unix:HEADERS           += ../lib/com/serial/posix_qextserialport.h
unix:SOURCES           += ../lib/com/serial/posix_qextserialport.cpp
unix:DEFINES           += _TTY_POSIX_


win32:HEADERS          += ../lib/com/serial/win_qextserialport.h
win32:SOURCES          += ../lib/com/serial/win_qextserialport.cpp
win32:DEFINES          += _TTY_WIN_


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
    ../lib/com/common/CommandMessage.cpp \
    ../lib/core/SysUtils.cpp \
    ../lib/core/Module.cpp \
    ../lib/core/Error.cpp \
    ../lib/core/Device.cpp \
    ../lib/core/DBInitRead.cpp \
    ../lib/core/AbstractApplication.cpp \
    ../lib/com/zbp/ZbpMessage.cpp \
    ../lib/com/zbp/ZbpAddress.cpp \
    ../lib/com/zbp/ZbpNetwork.cpp \
    ../lib/core/SingleDAT.cpp \
    ../lib/core/DatabaseProperties.cpp \
    ../lib/com/xap/XAPNetworkProperties.cpp \
    ../lib/com/xap/XAPException.cpp \
    ../lib/com/xap/XAPMessageException.cpp \
    ../lib/core/QueryBean.cpp \
    ../lib/core/model/ZigbusNetworkModel.cpp \
    ../lib/core/model/SymbolicTypeModel.cpp \
    ../lib/core/model/SymbolicNetworkModel.cpp \
    ../lib/core/model/LocationModel.cpp \
    ../lib/core/model/HardwareTypeModel.cpp \
    ../lib/com/zbp/zigbus.cpp \
    ../lib/com/zbp/ZbpNetworkProperties.cpp \

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
    ../lib/com/common/CommandMessage.h \
    ../lib/core/SysUtils.h \
    ../lib/core/QueryBean.h \
    ../lib/core/Module.h \
    ../lib/core/Error.h \
    ../lib/core/Device.h \
    ../lib/core/DBInitRead.h \
    ../lib/core/AbstractApplication.h \
    ../lib/com/zbp/ZbpMessage.h \
    ../lib/com/zbp/ZbpAddress.h \
    ../lib/com/zbp/zigbus.h \
    ../lib/com/common/GenericProtocol.h \
    ../lib/com/zbp/ZbpNetwork.h \
    ../lib/core/SingleDAT.h \
    ../lib/core/DatabaseProperties.h \
    ../lib/com/xap/XAPNetworkProperties.h \
    ../lib/com/xap/XAPException.h \
    ../lib/com/xap/XAPMessageException.h \
    ../lib/core/model/ZigbusNetworkModel.h \
    ../lib/core/model/SymbolicTypeModel.h \
    ../lib/core/model/SymbolicNetworkModel.h \
    ../lib/core/model/LocationModel.h \
    ../lib/core/model/HardwareTypeModel.h \
    ../lib/com/zbp/ZbpNetworkProperties.h

#-------------------------------------------------
#
# Project created by QtCreator 2012-09-12T20:49:58
#
#-------------------------------------------------

QT += core gui sql xml xmlpatterns debug

TARGET = admin
TEMPLATE = app

INCLUDEPATH += ../lib

SOURCES += main.cpp\
        AdminWindow.cpp \
    DeviceAdministrationPanel.cpp \
    ../lib/core/Device.cpp \
    ../lib/core/Module.cpp \
    ../lib/core/DBInitRead.cpp \
    ../lib/core/DatabaseProperties.cpp \
    ../lib/com/xap/XAPNetworkProperties.cpp \
    ../lib/com/xap/XAPMessage.cpp \
    ../lib/core/SysUtils.cpp \
    ../lib/core/Error.cpp \
    ../lib/com/xap/XAPNameValuePair.cpp \
    ../lib/com/xap/XAPHeader.cpp \
    ../lib/com/xap/XAPBlock.cpp \
    ../lib/core/ModuleTreeItem.cpp \
    ../lib/core/DeviceTreeItem.cpp \
    ../lib/com/common/GenAddress.cpp

HEADERS  += AdminWindow.h \
    DeviceAdministrationPanel.h \
    ../lib/core/Device.h \
    ../lib/core/Module.h \
    ../lib/core/DBInitRead.h \
    ../lib/core/DatabaseProperties.h \
    ../lib/com/xap/XAPNetworkProperties.h \
    ../lib/com/xap/XAPMessage.h \
    ../lib/core/SysUtils.h \
    ../lib/core/Error.h \
    ../lib/com/xap/XAPNameValuePair.h \
    ../lib/com/xap/XAPHeader.h \
    ../lib/com/xap/XAPBlock.h \
    ../lib/core/ModuleTreeItem.h \
    ../lib/core/DeviceTreeItem.h \
    ../lib/com/common/GenAddress.h

FORMS    += AdminWindow.ui \
    DeviceAdministrationPanel.ui

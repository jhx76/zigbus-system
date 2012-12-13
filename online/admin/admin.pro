#-------------------------------------------------
#
# Project created by QtCreator 2012-09-12T20:49:58
#
#-------------------------------------------------

QT += core gui sql xml xmlpatterns debug

TEMPLATE = app

INCLUDEPATH += ../lib

OBJECTS_DIR = ../../build/admin/obj

MOC_DIR = ../../build/admin/moc

DESTDIR = ../../bin

CONFIG(debug, debug|release) {
    TARGET = admind
    DEFINES += ZB_DEBUG
}
else {
    TARGET = admin
}




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
    ../lib/com/common/GenAddress.cpp \
    DeviceEditionPanel.cpp \
    ModuleEditionPanel.cpp \
    DeviceCreationDialog.cpp \
    ../lib/core/QueryBean.cpp \
    ../lib/core/model/LocationModel.cpp \
    ../lib/core/model/SymbolicTypeModel.cpp \
    ../lib/core/model/SymbolicNetworkModel.cpp \
    ../lib/core/model/HardwareTypeModel.cpp \
    ../lib/core/model/ZigbusNetworkModel.cpp \
    DatabaseConnectionDialog.cpp \
    ../lib/com/xap/XAPMessageException.cpp \
    ../lib/com/zbp/ZbpNetworkProperties.cpp \
    ../lib/core/model/HardwareSubTypeModel.cpp \
    ModuleCreationDialog.cpp \
    LocationCreationDialog.cpp \
    LocationManagementDialog.cpp \
    ../lib/core/ApplicationInformation.cpp \
    TypesManagementDialog.cpp \
    TypeCreationDialog.cpp

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
    ../lib/com/common/GenAddress.h \
    DeviceEditionPanel.h \
    ModuleEditionPanel.h \
    DeviceCreationDialog.h \
    ../lib/core/QueryBean.h \
    ../lib/core/model/LocationModel.h \
    ../lib/core/model/SymbolicTypeModel.h \
    ../lib/core/model/SymbolicNetworkModel.h \
    ../lib/core/model/HardwareTypeModel.h \
    ../lib/core/model/ZigbusNetworkModel.h \
    DatabaseConnectionDialog.h \
    ../lib/com/xap/XAPMessageException.h \
    ../lib/com/zbp/ZbpNetworkProperties.h \
    ../lib/core/model/HardwareSubTypeModel.h \
    ModuleCreationDialog.h \
    LocationCreationDialog.h \
    LocationManagementDialog.h \
    ../lib/core/ApplicationInformation.h \
    TypesManagementDialog.h \
    TypeCreationDialog.h

FORMS    += AdminWindow.ui \
    DeviceAdministrationPanel.ui \
    DeviceEditionPanel.ui \
    ModuleEditionPanel.ui \
    DeviceCreationDialog.ui \
    DatabaseConnectionDialog.ui \
    ModuleCreationDialog.ui \
    LocationCreationDialog.ui \
    LocationManagementDialog.ui \
    TypesManagementDialog.ui \
    TypeCreationDialog.ui

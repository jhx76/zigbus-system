#include "SingleDAT.h"

SingleDAT::SingleDAT() {
    this->queryBean = NULL;
}

SingleDAT::SingleDAT(QueryBean *bean) {
    this->queryBean = bean;
    initialize();
}

SingleDAT::~SingleDAT() {
    queryBean = NULL;
}

void SingleDAT::initialize() {
    try {
        if(queryBean != NULL) {
            this->moduleList = queryBean->buildModuleList();
        }
        else throw error::NullPointerException("Null pointer", AT);
    }
    catch(const error::NullPointerException& exception) {
        qDebug() << exception.toString();
    }
}

GenAddress SingleDAT::find(const ZbpAddress &src) {
    GenAddress resultAddress;
    bool ok;

    if(src.getHardwareType() == type_UNDEF && src.getMainPin() == "" && src.getOptionalPin() == "") {
        //On recherche l'adresse d'un module
        QString moduleAddress = QString::number(src.getModuleAddress(), 16);
        QString netAddress = QString::number(src.getNetworkAddress(), 10);
        for(int imod = 0; imod < moduleList.count(); imod++) {
            int tableModId = moduleList[imod].getLabel().toInt(&ok, 8);
            if(!ok)
                throw QString(AT+"error: unable to convert '"+moduleList[imod].getLabel()+"' into integer");
            int tableNetId = moduleList[imod].getZigbusNetworkId().toInt(&ok, 10);
            if(!ok)
                throw QString(AT+"error: unable to convert '"+moduleList[imod].getZigbusNetworkId()+"' into integer");
            int srcModId = moduleAddress.toInt(&ok, 16);
            if(!ok)
                throw QString(AT+"error: unable to convert '"+moduleAddress+"' into integer");
            int srcNetId = netAddress.toInt(&ok, 10);
            if(!ok)
                throw QString(AT+"error: unable to convert '"+netAddress+"' into integer");
            if(tableModId == srcModId && tableNetId == srcNetId) {
                resultAddress.setVendor("zigbus");
                resultAddress.setType("module");
                resultAddress.setLocation(src.toTrame().mid(0, 2));
                resultAddress.setInstance(src.toTrame().mid(2));
                return resultAddress;
            }
        }
        throw QString(AT+"error: module not found in declarations");
    }
    else {
        QString moduleAddress = QString::number(src.getModuleAddress(), 16);
        QString netAddress = QString::number(src.getNetworkAddress(), 10);
        for(int imod = 0; imod < moduleList.count(); imod++) {
            QString dfs = moduleList[imod].getLabel();
            int tableModId = moduleList[imod].getLabel().toInt(&ok, 8);
            if(!ok)
                throw QString(AT+"error: unable to convert '"+moduleList[imod].getLabel()+"' into intger");
            int tableNetId = moduleList[imod].getZigbusNetworkId().toInt(&ok, 10);
            if(!ok)
                throw QString(AT+"error: unable to convert '"+moduleList[imod].getZigbusNetworkId()+"' into intger");
            int srcModId = moduleAddress.toInt(&ok, 16);
            if(!ok)
                throw QString(AT+"error: unable to convert '"+moduleAddress+"' into intger");
            int srcNetId = netAddress.toInt(&ok, 10);
            if(!ok)
                throw QString(AT+"error: unable to convert '"+netAddress+"' into intger");
            if(tableModId == srcModId && tableNetId == srcNetId) {
                for(int idev = 0; idev < moduleList[imod].deviceCount(); idev++) {
                    if(moduleList[imod].elementAt(idev).getPinId() == src.getMainPin()
                            && moduleList[imod].elementAt(idev).getOptionalId() == src.getOptionalPin()
                            && moduleList[imod].elementAt(idev).getPinSubType() == convertSubTypeToStr(src.getSubType())
                            && convertDeviceType(moduleList[imod].elementAt(idev).getPinType()) == src.getHardwareType()) {
                        resultAddress.setVendor(moduleList[imod].elementAt(idev).getVendor());
                        resultAddress.setType(moduleList[imod].elementAt(idev).getType());
                        resultAddress.setLocation(moduleList[imod].elementAt(idev).getLocation());
                        resultAddress.setInstance(moduleList[imod].elementAt(idev).getInstance());
                        return resultAddress;
                    }
                }
            }
        }
        throw QString(AT+"error: device not found in declarations");
    }
}

ZbpAddress SingleDAT::find(const GenAddress &src, const QString& mainPin,
                           const QString& optionalPin, const QString& pinType) {
    ZbpAddress resultAddress;
    bool ok;
    if(src.getType() == "module") {
        //exemple: zigbus-dev.module.00:01
        for(int imod = 0; imod < moduleList.count(); imod++) {
            if(moduleList[imod].getLabel().toInt() == src.getInstance().toInt() &&
                    moduleList[imod].getZigbusNetworkId().toInt() == src.getLocation().toInt()) {
                for(int idev = 0; idev < moduleList[imod].deviceCount(); idev++) {
                    if(moduleList[imod].elementAt(idev).getPinId() == mainPin.trimmed() &&
                            moduleList[imod].elementAt(idev).getOptionalId().trimmed() == optionalPin.trimmed() &&
                            moduleList[imod].elementAt(idev).getPinType().trimmed() == pinType.trimmed()) {
                        resultAddress.setModuleAddress(src.getInstance().toInt(&ok, 8));
                        resultAddress.setNetworkAddress(src.getLocation().toInt(&ok, 10));
                        resultAddress.setMainPin(mainPin);
                        resultAddress.setOptionalPin(optionalPin);
                        resultAddress.setSubType(convertStrToSubType(moduleList[imod].elementAt(idev).getPinSubType()));
                        return resultAddress;

                    }
                }
            }
        }
        throw QString("error: required device not found");
    }
    else {
        for(int imod = 0; imod < moduleList.count(); imod++){
            for(int idev = 0; idev < moduleList[imod].deviceCount(); idev++) {
                qDebug() << src.toString() << " == " << moduleList[imod].elementAt(idev).getGenericAddress().toString();
                if(src == moduleList[imod].elementAt(idev).getGenericAddress()) {
                    resultAddress.setModuleAddress(moduleList[imod].getLabel().toInt(&ok, 8));
                    resultAddress.setNetworkAddress(moduleList[imod].getZigbusNetworkId().toInt(&ok, 10));
                    resultAddress.setMainPin(moduleList[imod].elementAt(idev).getPinId());
                    resultAddress.setOptionalPin(moduleList[imod].elementAt(idev).getOptionalId());
                    resultAddress.setHardwareType(zigbus::convertDeviceType(moduleList[imod].elementAt(idev).getPinType()));
                    return resultAddress;
                }
            }
        }
        throw QString("error: device not found");
    }
}

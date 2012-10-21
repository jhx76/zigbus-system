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
        QString moduleAddress = QString::number(src.getModuleAddress());


        QString netAddress = QString::number(src.getNetworkAddress());
        for(int imod = 0; imod < moduleList.count(); imod++) {
            if(moduleList[imod].getLabel().toInt() == moduleAddress.toInt() &&
                    moduleList[imod].getZigbusNetworkId().toInt() == netAddress.toInt()) {
                resultAddress.setVendor("zigbus-dev");
                resultAddress.setType("module");
                resultAddress.setLocation(src.toTrame().mid(0, 2));
                resultAddress.setInstance(src.toTrame().mid(2));
                return resultAddress;
            }
            throw QString("error: module not found in declarations");
        }
    }
    else {
        throw QString("error: find device addresses is not enable on this version !");
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
                    //qDebug() << moduleList[imod].elementAt(idev).getPinId() << " == " << mainPin << " &&";
                    //qDebug() << "    " << moduleList[imod].elementAt(idev).getOptionalId() << " == " << optionalPin << " &&";
                    //qDebug() << "    " << moduleList[imod].elementAt(idev).getPinType() << " == " << pinType;
                    if(moduleList[imod].elementAt(idev).getPinId() == mainPin.trimmed() &&
                            moduleList[imod].elementAt(idev).getOptionalId().trimmed() == optionalPin.trimmed() &&
                            moduleList[imod].elementAt(idev).getPinType().trimmed() == pinType.trimmed()) {
                        resultAddress.setModuleAddress(src.getInstance().toInt());
                        resultAddress.setNetworkAddress(src.getLocation().toInt());
                        resultAddress.setMainPin(mainPin);
                        resultAddress.setOptionalPin(optionalPin);
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
                    resultAddress.setModuleAddress(moduleList[imod].getLabel().toInt(&ok));
                    resultAddress.setNetworkAddress(moduleList[imod].getZigbusNetworkId().toInt(&ok));
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

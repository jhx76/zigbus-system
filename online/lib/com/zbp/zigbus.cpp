#include "zigbus.h"

zigbus::ZigbusDeviceType zigbus::convertDeviceType(const QString& strType) {
    if(strType == "temperature") return zigbus::type_TEMPERATURE;
    else if(strType == "heater") return zigbus::type_HEATER;
    else if(strType == "lampe") return zigbus::type_LAMPE;
    else if(strType == "numeric_input") return zigbus::type_NUMERIC_INPUT;
    else if(strType == "numeric_output") return zigbus::type_NUMERIC_OUTPUT;
    else if(strType == "analogic_input") return zigbus::type_ANALOGIC_INPUT;
    else if(strType == "pwm") return zigbus::type_PWM_OUTPUT;
    else if(strType == "remote") return zigbus::type_REMOTE;
    else if(strType == "serial") return zigbus::type_SERIAL;
    else if(strType == "servo") return zigbus::type_SERVO;
    else if(strType == "token") return zigbus::type_TOKEN;
    else return zigbus::type_UNDEF;
}

QString zigbus::convertDeviceType(zigbus::ZigbusDeviceType type) {
    switch(type) {
    case zigbus::type_TEMPERATURE: return "temperature";
    case zigbus::type_HEATER: return "heater";
    case zigbus::type_LAMPE: return "lampe";
    case zigbus::type_NUMERIC_INPUT: return "numeric_input";
    case zigbus::type_NUMERIC_OUTPUT: return "numeric_output";
    case zigbus::type_ANALOGIC_INPUT: return "analogic_input";
    case zigbus::type_PWM_OUTPUT: return "pwm";
    case zigbus::type_REMOTE: return "remote";
    case zigbus::type_SERIAL: return "serial";
    case zigbus::type_SERVO: return "servo";
    case zigbus::type_TOKEN: return "token";
    default: return "";
    }
}



zigbus::ZigbusHeaterFunction zigbus::convertHeaterFunction(const QString &strFunc) {
    if(strFunc.toUpper() == "STOP") return zigbus::hfunc_STOP;
    else if(strFunc.toUpper() == "ECO") return zigbus::hfunc_ECO;
    else if(strFunc.toUpper() == "CONFORT") return zigbus::hfunc_CONFORT;
    else if(strFunc.toUpper() == "CONFORT-1") return zigbus::hfunc_CONFORT1;
    else if(strFunc.toUpper() == "CONFORT-2") return zigbus::hfunc_CONFORT2;
    else return zigbus::hfunc_UNDEF;
}

QString zigbus::convertHeaterFunction(zigbus::ZigbusHeaterFunction func) {
    switch(func) {
    case zigbus::hfunc_STOP: return "STOP";
    case zigbus::hfunc_ECO: return "ECO";
    case zigbus::hfunc_CONFORT2: return "CONFORT-2";
    case zigbus::hfunc_CONFORT1: return "CONFORT-1";
    case zigbus::hfunc_CONFORT: return "CONFORT";
    default: return "";
    }
}


zigbus::ZigbusSubType zigbus::convertStrToSubType(const QString &str) {
    if(str.toUpper() == "DHT11") return zigbus::stype_DHT11;
    else if(str.toUpper() == "LM35DZ") return zigbus::stype_LM35DZ;
    else return zigbus::stype_UNDEF;
}

QString zigbus::convertSubTypeToStr(zigbus::ZigbusSubType stype) {
    switch(stype) {
    case zigbus::stype_DHT11:
        return "DHT11";
    case zigbus::stype_LM35DZ:
        return "LM35DZ";
    default:
        return "";
    };
}

int zigbus::convertDevicePinId(const QString& strPinId) {
    bool ok;
    int rslt = strPinId.mid(1).toInt(&ok);
    if(!ok) throw QString();
    if(strPinId.mid(0, 1) == "S")
        return rslt;
    else if(strPinId.mid(0, 1) == "A")
        return rslt+100;
    else throw QString(AT+"error: unknown pin id");
}

QString zigbus::convertDevicePinId(int id) {
    QString rslt = "";
    if(id < 100) {
        rslt = "S";
        rslt += QString::number(id);
    }
    else {
        rslt = "A";
        rslt += QString::number(id - 100);
    }
    return rslt;
}

QString zigbus::convertAnalogicReference(zigbus::ZigbusAnalogicReference ref) {
    switch(ref) {
    case aref_INTERNAL: return "internal";
    case aref_INTERNAL1V1: return "internal1V1";
    case aref_INTERNAL2V56: return "internal2V56";
    case aref_EXTERNAL: return "external";
    default: return "";
    }
}

zigbus::ZigbusAnalogicReference zigbus::convertAnalogicReference(const QString& str) {
    if(str.toUpper() == "INTERNAL") return aref_INTERNAL;
    else if(str.toUpper() == "INTERNAL1V1") return aref_INTERNAL1V1;
    else if(str.toUpper() == "INTERNAL2V56") return aref_INTERNAL2V56;
    else if(str.toUpper() == "EXTERNAL") return aref_EXTERNAL;
    else return aref_DEFAULT;
}

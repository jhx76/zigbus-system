#include "zigbus.h"
zigbus::ZigbusDeviceType zigbus::convertDeviceType(const QString& strType) {
    if(strType == "temperature") return zigbus::type_TEMPERATURE;
    else if(strType == "heater") return zigbus::type_HEATER;
    else if(strType == "lamp") return zigbus::type_LAMP;
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

zigbus::ZigbusHeaterFunction zigbus::convertHeaterFunction(const QString &strFunc) {
    if(strFunc.toUpper() == "STOP") return zigbus::hfunc_STOP;
    else if(strFunc.toUpper() == "ECO") return zigbus::hfunc_ECO;
    else if(strFunc.toUpper() == "CONFORT") return zigbus::hfunc_CONFORT;
    else if(strFunc.toUpper() == "CONFORT-1") return zigbus::hfunc_CONFORT1;
    else if(strFunc.toUpper() == "CONFORT-2") return zigbus::hfunc_CONFORT2;
    else return zigbus::hfunc_UNDEF;
}

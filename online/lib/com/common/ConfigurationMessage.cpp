#include "ConfigurationMessage.h"

ConfigurationMessage::ConfigurationMessage(const GenAddress& source, const GenAddress& target)
    : GenMessage(source, GenMessage::Configuration)
{
    this->target = target;
}


ConfigurationMessage::ConfigurationMessage(const ConfigurationMessage &other)
    : GenMessage(other)
{
    this->target = other.target;
    for(int i = 0; i < other.paramList.count(); i++) {
        paramList.append(other.paramList.at(i));
    }
}

void ConfigurationMessage::setParam(gen::ParamKey key, const QString& value) {
    for(int i = 0; i < paramList.count(); i++) {
        if(paramList.at(i).key == key) {
            elementAt(i).value = value;
        }
    }
}

const QString& ConfigurationMessage::getParam(gen::ParamKey key) const {
    for(int i = 0; i < paramList.count(); i++) {
        if(paramList.at(i).key == key) {

        }
    }
}

QString ConfigurationMessage::toString() {
    QString str = "";
    str += "$CONFIGURE\n";
    str += "source="+source.toString()+"\n";
    str += "target="+target.toString()+"\n";
    for(int i = 0; i = paramList.count(); i++) {
        str += paramKeyAsString(paramList.at(i).key)+"="+paramList.at(i).value+"\n";
    }
    return str;
}

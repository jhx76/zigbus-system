#include "InformationMessage.h"

InformationMessage::InformationMessage(const GenAddress& source) : GenMessage(source, GenMessage::Information)
{

}

InformationMessage::InformationMessage(const InformationMessage &other) : GenMessage(other) {
    for(int i = 0; i < other.paramList.count(); i++) {
        paramList.append(other.paramList[i]);
    }
}


const QString& InformationMessage::getParam(gen::ParamKey key) const {
    for(int i = 0; i < paramList.count(); i++) {
        if(paramList.at(i).key == key) {
            return paramList.at(i).value;
        }
    }
}

void InformationMessage::setParam(gen::ParamKey key, const QString &value) {
    for(int i = 0; i < paramList.count(); i++) {
        if(paramList.at(i).key == key) {
            paramList[i].value = value;
            return;
        }
    }
    gen::Param param;
    param.key = key;
    param.value = value;
    paramList.append(param);
}

bool InformationMessage::contains(gen::ParamKey key) const {
    for(int i = 0; i < paramList.count(); i++) {
        if(paramList[i].key == key)
            return true;
    }
    return false;
}


int InformationMessage::paramCount() const {
    return paramList.count();
}

const gen::Param& InformationMessage::at(int i) const {
    return paramList.at(i);
}

gen::Param& InformationMessage::elementAt(int i) {
    return paramList[i];
}

void InformationMessage::append(const gen::Param &param) {
    paramList.append(param);
}

void InformationMessage::removeAt(int i) {
    paramList.removeAt(i);
}

void InformationMessage::clear() {
    while(!paramList.isEmpty()) {
        paramList.takeFirst();
    }
}

bool InformationMessage::isEmpty() const {
    return paramList.isEmpty();
}

QString InformationMessage::toString() {
    QString rslt = "";
    rslt += "$INFORMATION\n";
    rslt += "source="+source.toString()+"\n";
    for(int i = 0; i < paramList.count(); i++) {
        rslt += paramKeyAsString(paramList.at(i).key)+"="+paramList.at(i).value+"\n";
    }
    return rslt;
}


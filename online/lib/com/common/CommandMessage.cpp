#include "CommandMessage.h"

CommandMessage::CommandMessage(const GenAddress &source, const GenAddress &target) : GenMessage(source, Command) {
    this->target = target;
}

CommandMessage::CommandMessage(const CommandMessage &other) : GenMessage(other){
    this->target = other.target;
    for(int i = 0; i < other.paramList.count(); i++) {
        paramList[i].key = other.paramList[i].key;
        paramList[i].value = other.paramList[i].value;
    }
}

const QString& CommandMessage::getParam(ParamKey key) const {
    for(int i = 0; i < this->paramList.count(); i++) {
        if(paramList[i].key == key) {
            return paramList[i].value;
        }
    }
}

void CommandMessage::setParam(ParamKey key, const QString &value) {
    for(int i = 0; i < paramList.count(); i++) {
        if(paramList[i].key == key) {
            paramList[i].value = value;
            return;
        }
    }
    Param tmpParam;
    tmpParam.key = key;
    tmpParam.value = value;
    this->paramList.append(tmpParam);
}

bool CommandMessage::contains(ParamKey key) const {
    for(int i = 0; i < paramList.count(); i++)
      if(paramList[i].key == key)
            return true;
    return false;
}

bool CommandMessage::isEmpty() const {
    return paramList.isEmpty();
}

int CommandMessage::paramCount() const {
    return paramList.count();
}

gen::Param& CommandMessage::elementAt(int i) {
    return paramList[i];
}

const gen::Param& CommandMessage::at(int i) const {
    return paramList.at(i);
}

void CommandMessage::append(const gen::Param &param) {
    paramList.append(param);
}

void CommandMessage::removeAt(int i) {
    paramList.removeAt(i);
}

void CommandMessage::clear() {
    while(!paramList.isEmpty()) {
        paramList.takeFirst();
    }
}

QString CommandMessage::toString() {
    QString rslt = "";
    rslt += "$COMMAND\n";
    rslt += "source="+source.toString()+"\n";
    rslt += "target="+target.toString()+"\n";
    for(int i = 0; i < paramList.count(); i++) {
        rslt += paramKeyAsString(paramList.at(i).key);
        rslt += "=";
        rslt += paramList.at(i).value;
        rslt +="\n";
    }

    return rslt;
}

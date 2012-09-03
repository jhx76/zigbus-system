#include "EventMessage.h"

EventMessage::EventMessage(const GenAddress &source) : GenMessage(source, GenMessage::Event)
{

}

EventMessage::EventMessage(const EventMessage &other) : GenMessage(other) {

}


const QString& EventMessage::getParam(ParamKey key) const {
    for(int i = 0; i < paramList.count(); i++) {
        if(paramList.at(i).key == key) {
            return paramList.at(i).value;
        }
    }
    return "";
}

void EventMessage::setParam(ParamKey key, const QString &value) {
    for(int i = 0; i < paramList.count(); i++) {
        if(paramList.at(i).key == key ) {
            paramList[i].value = value;
            return;
        }
    }
    Param param;
    param.key = key;
    param.value = value;
    paramList.append(param);

}

bool EventMessage::contains(ParamKey key) const {
    for(int i = 0; i < paramList.count(); i++) {
        if(paramList.at(i).key == key) {
            return true;
        }
    }
    return false;
}

Param& EventMessage::elementAt(int i) {
    return paramList[i];
}

const Param& EventMessage::at(int i) const {
    return paramList.at(i);
}

int EventMessage::paramCount() const  {
    return paramList.count();
}

void EventMessage::append(const gen::Param &param) {
    if(!this->contains(param.key))
        paramList.append(param);
    else
        qDebug() << "param already exists in the message";
}

void EventMessage::removeAt(int i) {
    paramList.removeAt(i);
}

void EventMessage::clear() {
    while(!paramList.isEmpty())
        paramList.takeFirst();
}

bool EventMessage::isEmpty() const {
    return paramList.isEmpty();
}

QString EventMessage::toString() {
    QString rslt = "";
    rslt += "$EVENT\n";
    rslt += "source="+source.toString()+"\n";
    for(int i = 0; i < paramList.count(); i++) {
        rslt += paramKeyAsString(paramList.at(i).key)+"="+paramList.at(i).value+"\n";
    }
    return rslt;
}


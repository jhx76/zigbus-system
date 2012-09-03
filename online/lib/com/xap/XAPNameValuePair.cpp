
#include "XAPNameValuePair.h"

XAPNameValuePair::XAPNameValuePair(){
    name = "";
    value = "";
}

XAPNameValuePair::XAPNameValuePair(const QString & name, const QString & value){
    this->name = name;
    this->value = value;
}

XAPNameValuePair::XAPNameValuePair(const XAPNameValuePair & other){
    name = other.getName();
    value = other.getValue();
}

XAPNameValuePair::~XAPNameValuePair(){

}

XAPNameValuePair XAPNameValuePair::fromString(const QString & str)
{
    XAPNameValuePair nvpair;
    QString name, value;
    name = str.mid(0, str.indexOf("="));
    if(!name.isEmpty()) {
        value = str.mid(str.indexOf("=") + 1, str.count() - str.indexOf("=") + 1);
        nvpair = XAPNameValuePair(name, value);
    }
    return nvpair;
}

QString XAPNameValuePair::toString() const {

    QString str = name + "=" + value + "\n";
    if(value.isEmpty())
        return "";
    return str;
}


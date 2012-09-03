#include "Module.h"

Module::Module()
{
}

//----------------------------------------------------------------------------

Module::Module(const QString &label, int analogicIOCount, int numericIOCount) {
    this->label = label;
    this->analogIOCount = analogicIOCount;
    this->numericIOCount = numericIOCount;
}

//----------------------------------------------------------------------------

Module::Module(const Module &other) {
    this->label = other.label;
    this->analogIOCount = other.analogIOCount;
    this->numericIOCount = other.numericIOCount;
    for(int i = 0; i < other.deviceCount(); i++) {
        Device d(other.deviceList[i]);
        this->append(d);
    }
}

//----------------------------------------------------------------------------

QString Module::toString() const {
    QString s = "";
    s += "label: "+this->label+"\n";
    s += "numeric count: " +QString::number(this->numericIOCount)+"\n";
    s += "analogic count: "+QString::number(this->analogIOCount)+"\n";
    for(int i = 0; i < deviceCount(); i++)
        s += deviceList.at(i).toString();
    return s;
}

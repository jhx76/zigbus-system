#include "GenMessage.h"

GenMessage::GenMessage(const GenAddress& source, TypeMessage type)
{
    this->source = source;
    this->typeMessage = type;
}

GenMessage::GenMessage(const GenMessage &other) {
    this->source = other.source;
    this->typeMessage = other.typeMessage;
}

QString GenMessage::toString() {
    QString rslt = "";
    rslt += "no information on the message ... due to a bad class interpretation";
    return rslt;
}

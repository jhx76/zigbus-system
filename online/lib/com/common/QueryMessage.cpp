#include "QueryMessage.h"

QueryMessage::QueryMessage(const GenAddress& source, const GenAddress& target) : GenMessage(source, GenMessage::Query)
{
    this->target = target;
}


QueryMessage::QueryMessage(const QueryMessage &other) : GenMessage(other) {
    this->setTypeMessage(GenMessage::Query);
    this->setTarget(target);
}


QString QueryMessage::toString() {
    QString rslt = "";
    rslt += "$QUERY\n";
    rslt += "source="+source.toString()+"\n";
    rslt += "target="+target.toString()+"\n";
    return rslt;
}

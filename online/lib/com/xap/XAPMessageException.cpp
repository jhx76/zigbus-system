#include "XAPMessageException.h"

XAPMessageException::XAPMessageException() throw()
{
    msgSrc = "";
    errorMessage = "";
    codePosition = "";
}

XAPMessageException::XAPMessageException(const XAPMessageException &other) throw() {
    this->msgSrc = other.msgSrc;
    this->errorMessage = other.errorMessage;
    this->codePosition = other.codePosition;
}

XAPMessageException::XAPMessageException(const QString &msgSrc, const QString &errorMessage, const QString &codePosition) throw()
{
    this->msgSrc = msgSrc;
    this->errorMessage = errorMessage;
    this->codePosition = codePosition;
}

QString XAPMessageException::toString() const throw() {
    QString s = "XAPMessageException: at "+codePosition+"\n";
    s += "in message :\n";
    s+= msgSrc;
    s += "error: "+errorMessage;
    return s;
}

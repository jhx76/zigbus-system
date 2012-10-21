#ifndef XAPMESSAGEEXCEPTION_H
#define XAPMESSAGEEXCEPTION_H
#include <QString>

class XAPMessageException
{
private:
    QString msgSrc;
    QString errorMessage;
    QString codePosition;

public:
    XAPMessageException() throw();
    XAPMessageException(const QString& msgSrc, const QString& errorMessage, const QString& codePosition) throw();
    XAPMessageException(const XAPMessageException& other) throw();
    QString toString() const throw();
    const QString& getMsgSrc() const throw() { return msgSrc; }
    void setMsgSrc(const QString& msgSrc) throw() { this->msgSrc = msgSrc; }
    const QString& getErrorMessage() const throw() { return errorMessage; }
    void setErrorMessage(const QString& errorMessage) throw() { this->errorMessage = errorMessage; }
    const QString& getCodePosition() const throw() { return codePosition; }
    void setCodePosition(const QString& codePosition) throw() { this->codePosition = codePosition; }
};

#endif // XAPMESSAGEEXCEPTION_H

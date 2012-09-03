#include "Error.h"
#include <com/common/GenMessage.h>

namespace error {

    InitializationException::InitializationException(const QString& errorMessage, bool critic) throw() {
        this->errorMessage = errorMessage;
        errorNum = -1;
        critical = critic;
    }

    QString InitializationException::toString() const throw() {
        QString message = "";
        message += "[ERROR"+(errorNum != -1 ? QString::number(errorNum)
                                            : "")
                   +"] "+getErrorMessage()+"\n";
        return message;
    }

    InitializationException::InitializationException(int errorNum, const QString &errorMessage, bool critic) throw() {
        this->errorNum = errorNum;
        this->errorMessage = errorMessage;
        this->critical = critic;
    }


    TranslationException::TranslationException(const QString &message) throw() {
        this->message = "";
        this->objectMessage = NULL;
    }

    TranslationException::TranslationException(const QString &message, const GenMessage *object) throw() {
        this->message = message;
        this->objectMessage = const_cast<GenMessage*>(object);
    }

    TranslationException::TranslationException(const TranslationException &other) throw() {
        this->message = other.message;
        this->objectMessage = other.objectMessage;
    }

    QString TranslationException::toString() const throw() {
        QString s = "[ERROR]\"";
        s += message+"\" occured on message above:\n";
        s += objectMessage->toString()+"\n";
    }


    SysException::SysException(const QString& message) throw() {
        this->message = message;
    }

    SysException::SysException(const SysException &other) throw() {
        this->message = other.message;
    }

    const QString& SysException::getMessage() const throw() {
        return this->message;
    }

    void SysException::setMessage(const QString& message) throw() {
        this->message = message;
    }

    QString SysException::toString() const throw() {
        QString str = this->message;
        return str;
    }

}



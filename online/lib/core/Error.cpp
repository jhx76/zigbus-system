/*
    This file is part of Zigbus Home Automation API. 
    Copyright (C) 2012 jhx

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Error.h"
#include <com/common/GenMessage.h>

namespace error {


    BaseException::BaseException() throw() {
        this->message = "";
        this->codePosition = "";
        this->critic = false;
        dateTime = QDateTime::currentDateTime();
    }

    BaseException::BaseException(const QString &message, const QString &codePosition, bool critic) throw() {
        this->message = message;
        this->codePosition = codePosition;
        this->critic = critic;
        this->dateTime = QDateTime::currentDateTime();
    }

    BaseException::BaseException(const BaseException& other) throw() {
        this->message = other.message;
        this->codePosition = other.codePosition;
        this->dateTime = other.dateTime;
        this->critic = other.critic;
    }

    InitializationException::InitializationException() throw()
        : BaseException()
    {
    }

    InitializationException::InitializationException(const QString& message, const QString& codePosition, bool critic) throw()
        : BaseException(message, codePosition, critic)
    {
    }

    InitializationException::InitializationException(const InitializationException& other) throw()
        : BaseException(other)
    {
    }

    QString InitializationException::toString() const throw() {
        QString message = "InitializationException ("+dateTime.toString("dd.MM.yyyy h:m:s ap")+")\n";
        message += "at "+codePosition+" : " +this->getMessage();
        return message;
    }


    TranslationException::TranslationException() throw() : BaseException() {
        this->objectMessage = NULL;
    }

    TranslationException::TranslationException(const GenMessage *object, const QString& message,
                                               const QString& codePosition, bool critic) throw()
        : BaseException(message, codePosition, critic)
    {
        this->objectMessage = const_cast<GenMessage*>(object);
    }

    TranslationException::TranslationException(const TranslationException &other) throw()
        : BaseException(other) {
        this->objectMessage = other.objectMessage;
    }

    QString TranslationException::toString() const throw() {
        QString s = "TranslationException ("+this->dateTime.toString("dd.MM.yyyy h:m:s ap")+")\n";
        s += "at "+codePosition;
        s += message+"\" occured on message above:\n";
        s += objectMessage->toString()+"\n";
        return s;
    }


    SysException::SysException() throw()
        : BaseException()
    {
    }

    SysException::SysException(const QString& message, const QString& codePosition, bool critic) throw()
        : BaseException(message, codePosition, critic)
    {
    }

    SysException::SysException(const SysException &other) throw()
        : BaseException(other)
    {
    }

    QString SysException::toString() const throw() {
        QString s = "SysException ("+dateTime.toString("dd.MM.yyyy h:m:s ap")+")\n";
        s += "at : "+codePosition+"\n";
        s += message+"\n";
        return s;
    }


    SqlException::SqlException() throw()
        : BaseException()
    {
        query = "";
    }

    SqlException::SqlException(const QString& query, const QString& message, const QString& codePosition, bool critic) throw()
        : BaseException(message, codePosition, critic)
    {
        this->query = query;
    }

    SqlException::SqlException(const SqlException& other) throw()
        : BaseException(other)
    {
        this->query = other.query;
    }

    QString SqlException::toString() const throw() {
        QString result = "SqlException ("+dateTime.toString("dd.MM.yyyy h:m:s ap")+")\n";
        result += "at "+codePosition+":\n";
        result += "error: "+message+"\n";
        result += "on query: \n"+query+"\n";
        return result;
    }

    NullPointerException::NullPointerException() throw()
        : BaseException()
    {
    }

    NullPointerException::NullPointerException(const NullPointerException &other) throw()
        : BaseException(other)
    {
    }

    NullPointerException::NullPointerException(const QString &message, const QString &position, bool critic) throw()
        : BaseException(message, position, critic)
    {
    }

    QString NullPointerException::toString() const throw() {
        QString s = "NullPointerException ("+dateTime.toString("dd.MM.yyyy h:m:s ap")+")\n";
        s += "at "+codePosition+".\n";
        s += "error: "+message+"\n";
        return s;
    }


}



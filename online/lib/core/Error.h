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

#ifndef ERROR_H
#define ERROR_H

#include <QString>
#include <QDateTime>

class GenMessage;

/**
  @namespace error
  @author jhx
  @brief Ce namespace centralise tous les outils utilises pour la gestion des erreurs et des exceptions
  susceptibles de survenir durant la vie du systeme.
  */
namespace error {
//##########################################################
//        CONSTANT VALUES DECLARATIONS
//##########################################################

    /**
      Le fichier recherche n'existe pas.
      */
    const int err_fileNotFound = 1;

    /**
      Le repertoire recherche n'existe pas.
      */
    const int err_DirNotFound = 2;

    /**
      Impossible d'ouvrir un fichier
      */
    const int err_openFile = 3;

    /**
      Conversion d'une chaine vers un entier
      */
    const int err_strToInt = 4;


//##########################################################
//          EXCEPTION CLASSES DECLARATIONS
//##########################################################

//##### BASE CLASS ######
    /**
      @class BaseException
      @author jhx
      @date 04/10/2012
      @brief Base class for all exception classes within the error namespace
      */
    class BaseException {
    protected:
        /**

          */
        QString message;

        /**

          */
        bool critic;

        /**

          */
        QString codePosition;

        /**

          */
        QDateTime dateTime;

    public:
        /**
          Default Constructor
          */
        BaseException() throw();

        /**
          Copy constructor
          */
        BaseException(const BaseException& other) throw();

        /**
          Constructor to use when initializing an exception subclass
          */
        BaseException(const QString& message, const QString& codePosition = "", bool critic = false) throw();

        /**
          @return a exception description character string
          */
        const QString& getMessage() const throw() { return message; }

        /**
          Set the exception description string value to @arg message
          */
        void setMessage(const QString& message) throw() { this->message = message; }

        /**
          @return <b>true</b> if the exception has a critical aspect, otherwise return <b>false</b>
          */
        bool isCritic() const throw() { return critic; }

        /**
          Set the critic boolean value to @arg critic
          */
        void setCritic(bool critic = true) throw() { this->critic = critic; }

        /**

          */
        const QString& getCodePosition() const throw() { return this->codePosition; }

        /**

          */
        void setCodePosition(const QString& position) throw() { this->codePosition = position; }

        /**

          */
        const QDateTime& getDateTime() const throw() { return this->dateTime; }

        /**

          */
        void setDateTime(const QDateTime& dateTime) throw() { this->dateTime = dateTime; }

        /**
          @return a description string of the exception, containing the context where happened the exception and
          a description of the error
          */
        virtual QString toString() const throw() {
            QString s = "BaseException: ";
            return s;
        }
    };

    /**
      @class InitializationException
      @author jhx
      @brief Ce type d'exception est leve lorsque le programme a detecte des erreur a l'initialisation.
      */
    class InitializationException : public BaseException {
    public:
        /**
          Default constructor
          */
        InitializationException() throw();

        /**
          Copy constructor
          */
        InitializationException(const InitializationException& other) throw();

        /**
          @param errorMessage Une chaine descriptive de l'erreur qui a declenche l'exception
          @param critic "true" si l'erreur qui declenche l'exception est critique, sinon "false".
          */
        InitializationException(const QString& message, const QString& codePosition, bool critic = false) throw();

        /**
          @return Une chaine descriptive (humainement complete) de l'erreur qui a declenche l'exception
          */
        virtual QString toString() const throw();

    };

    /**
      @class TranslationException
      @author jhx
      @brief Classe d'exception permettant de gerer les erreurs survenues lors des traductions de messages generiques
      vers d'autres protocoles de communication.
      */
    class TranslationException : public BaseException {

    private:
        /**
          Pointeur vers l'objet GenMessage sur lequel la traduction n'a pas pu s'effectuer.
          Il permettra de loger les informations du message en question, ce qui permettra de faire un report
          precis.
          */
        GenMessage* objectMessage;

    public:
        /**
          Constructeur par defaut
          @param message chaine desciptive de l'exception
          */
        TranslationException() throw();

        /**
          Constructeur a utiliser dans le code
          @param message chaine descriptive de l'exception
          @param object pointeur sur l'objet concerne par l'exception
          */
        TranslationException(const GenMessage* object, const QString& message,
                             const QString & codePosition="", bool critic=false) throw();

        /**
          Constructeur de recopie
          @param other L'objet a recopier
          */
        TranslationException(const TranslationException& other) throw();

        /**
          Methode d'acces au pointeur sur l'objet concerne par l'exception
          @return Pointeur sur l'objet concerne par l'exception
          */
        GenMessage* getObjectMessage() const throw() { return objectMessage; }

        /**
          Methode de mise a jour du pointeur sur l'objet concerne par l'exception
          @param object Pointeur sur l'objet concerne par l'exception
          */
        void setObjectMessage(GenMessage* object) throw() { this->objectMessage = object; }

        /**
          Methode descriptive de l'exception
          @return Une chaine de caracteres descriptive de l'exception
          */
        virtual QString toString() const throw();
    };



    class SysException : public BaseException {
    public:
        /**
          Constructeur par defaut
          */
        SysException() throw();

        /**

          */
        SysException(const QString& message, const QString& codePosition = "", bool critic = false) throw();

        /**
          Constructeur de recopie
          @param other Objet a recopier
          */
        SysException(const SysException& other) throw();

        /**
          Genere une chaine descriptive plus complete (Humainement parlant) de l'exception.
          Pour afficher un message d'erreur concernant ce type d'exception, on utilisera plutot cette chaine-ci.
          @return Une chaine descriptive de l'exception
          */
        virtual QString toString() const throw();
    };

    /**
      @class SqlException
      @author jhx
      @brief Exception lancée lorsque survient une erreur SQL lors d'une utilisation des classes du module SQL de Qt.

      Dans la gestion des exceptions de type SqlException, le code est susceptible de reproduire d'autres exceptions d'un
      tout autre type, suivant le contexte où survient l'erreur.
      */
    class SqlException : public BaseException {
    private:
        QString query;

    public:
        /**

          */
        SqlException() throw();

        /**

          */
        SqlException(const QString& query, const QString& message, const QString& position, bool critic = false) throw();

        /**

          */
        SqlException(const SqlException& other) throw();

        const QString& getQuery() const throw() { return query; }

        void setQuery(const QString& query) throw() { this->query = query; }

        /**

          */
        virtual QString toString() const throw();
    };


    class NullPointerException : public BaseException {
    public:
        NullPointerException() throw();
        NullPointerException(const NullPointerException& other) throw();
        NullPointerException(const QString& message, const QString& position, bool critic = false) throw();
        virtual QString toString() const throw();
    };

}
#endif // ERROR_H

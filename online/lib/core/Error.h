#ifndef ERROR_H
#define ERROR_H

#include <QString>

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
    /**
      @class InitializationException
      @author jhx
      @brief Ce type d'exception est leve lorsque le programme a detecte des erreur a l'initialisation.
      */
    class InitializationException {
    private:
        /**
          Une chaine descriptive de l'erreur qui a declenche l'exception
          */
        QString errorMessage;

        /**
          Le numero de l'erreur declenchante.
          */
        int errorNum;

        /**
          "true" si l'erreur qui declenche l'exception est critique, sinon "false".
          */
         bool critical;

    public:
        /**
          Constructeur par defaut
          @param errorMessage Une chaine descriptive de l'erreur qui a declenche l'exception
          @param critic "true" si l'erreur qui declenche l'exception est critique, sinon "false".
          */
        InitializationException(const QString& errorMessage = "", bool critic = false) throw();

        /**
          Constructeur surcharge
          @param errorNum Le numero de l'erreur declenchante.
          @param errorMessage Une chaine descriptive de l'erreur qui a declenche l'exception
          @param critic "true" si l'erreur qui declenche l'exception est critique, sinon "false".
          */
        InitializationException(int errorNum, const QString& errorMessage = "", bool critic = false) throw();

        /**
          @return Une chaine descriptive de l'erreur qui a declenche l'exception
          */
        const QString& getErrorMessage() const throw() { return errorMessage; }

        /**
          @param errorMessage Une chaine descriptive de l'erreur qui a declenche l'exception
          */
        void setErrorMessage(const QString& errorMessage) throw() { this->errorMessage = errorMessage; }

        /**
          @return "true" si l'erreur qui declenche l'exception est critique, sinon "false".
          */
        bool isCritical() const throw() { return critical; }

        /**
          @param c "true" si l'erreur qui declenche l'exception est critique, sinon "false".
          */
        void setCritical(bool c) throw() { this->critical = c; }

        /**
          @return Une chaine descriptive (humainement complete) de l'erreur qui a declenche l'exception
          */
        QString toString() const throw();

        /**
          @return Le numero de l'erreur declenchante.
          */
        int getErrorNum() const throw() { return errorNum; }

        /**
          @param Le numero de l'erreur declenchante.
          */
        void setErrorNum(int error) throw() { errorNum = error; }
    };

    /**
      @class TranslationException
      @author jhx
      @brief Classe d'exception permettant de gerer les erreurs survenues lors des traductions de messages generiques
      vers d'autres protocoles de communication.
      */
    class TranslationException {

    private:
        /**
          Chaine de caracteres contenant le descriptif de l'erreur.
          */
        QString message;

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
        TranslationException(const QString& message = "") throw();

        /**
          Constructeur a utiliser dans le code
          @param message chaine descriptive de l'exception
          @param object pointeur sur l'objet concerne par l'exception
          */
        TranslationException(const QString& message, const GenMessage* object) throw();

        /**
          Constructeur de recopie
          @param other L'objet a recopier
          */
        TranslationException(const TranslationException& other) throw();

        /**
          Methode d'acces au descriptif de l'exception
          @return une chaine descriptive de l'exception
          */
        const QString& getMessage() const throw() { return message; }

        /**
          Methode de mise a jour du descriptif de l'exception
          @param message Chaine de caracteres descriptive de l'exception
          */
        void setMessage(const QString& message) throw() { this->message = message; }

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
        QString toString() const throw();
    };

    class SysException {
    private:
        /**
          Chaine desciptive de l'exception
          */
        QString message;

    public:
        /**
          Constructeur par defaut
          @param message Chaine descriptive de l'exception
          */
        SysException(const QString& message = "") throw();

        /**
          Constructeur de recopie
          @param other Objet a recopier
          */
        SysException(const SysException& other) throw();

        /**
          Methode d'acces a la chaine descriptive de l'exception
          @return Une chaine descriptive de l'exception
          */
        const QString& getMessage() const throw();

        /**
          Methode de mise a jour de la chaine descriptive.
          @param message Une chaine descriptive de l'exception
          */
        void setMessage(const QString& message) throw();

        /**
          Genere une chaine descriptive plus complete (Humainement parlant) de l'exception.
          Pour afficher un message d'erreur concernant ce type d'exception, on utilisera plutot cette chaine-ci.
          @return Une chaine descriptive de l'exception
          */
        QString toString() const throw();
    };


}
#endif // ERROR_H

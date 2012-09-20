#ifndef DATABASEPROPERTIES_H
#define DATABASEPROPERTIES_H

#include <QString>
#include <QtXmlPatterns>
#include <QDebug>

#include <core/SysUtils.h>
#include <core/Error.h>

/**
  @class DatabaseProperties
  @author jhx
  @brief Cette classe encapsule toutes les donnees necessaires a la connexion a une base de donnees.
  Elle peut etre instanciee et initialisee directement, ou bien via un fichier xml, passe en parametre du constructeur. Elle
  est utilisee a l'initialisation d'une connexion a une base de donnees.
  */
class DatabaseProperties {
private:
    /**
      Le nom de la base de donnees sur le server
      */
    QString databaseName;

    /**
      L'adresse IP ou l'alias du serveur host.
      */
    QString hostAddress;

    /**
      Le port sur lequel la base de donnees est joignable sur le server host.
      */
    int hostPort;

    /**
      Le nom d'utilisateur utilise pour les operations sur la base de donnees.
      */
    QString userName;

    /**
      Le mot de passe correspondant au nom d'utilisateur utilise.
      */
    QString password;

    friend class DBInitRead;

public:
    /**
      Constructeur par defaut.
      */
    DatabaseProperties();

    /**
      Constructeur surcharge.
      @param databaseName
      @param hostAddress
      @param hostPort
      @param userName
      @param password
      */
    DatabaseProperties(const QString& databaseName, const QString& hostAddress, int hostPort, const QString& userName, const QString& password);

    /**

      */
    DatabaseProperties(const QString& fileName);

    /**
      Constructeur de recopie
      @param other
      */
    DatabaseProperties(const DatabaseProperties& other);

    /**
      Destructeur par defaut
      */
    ~DatabaseProperties();

    /**
      Compare l'objet courant avec l'objet passe en parametre.
      @param other l'objet a comparer avec l'objet courant
      @return Si toutes les valeurs des deux objets compares sont egales, renvoie <b>true</b>, sinon renvoie <b>false</b>
      */
    bool isEqual(const DatabaseProperties& other) const;

    /**
      Surcharge de l'operateur = pour cette classe.
      @param other L'objet a recopier
      */
    DatabaseProperties& operator=(const DatabaseProperties& other);

    /**
      Genere une chaine descriptive complete de l'objet
      @return une chaine descriptive de l'objet
      */
    QString toString() const;

    /**
      Methode d'acces a databaseName
      @return databaseName: le nom de la base de donnees
      */
    const QString& getDatabaseName() const { return databaseName; }

    /**
      Methode de mise a jour de databaseName
      @param databaseName Le nom de la base de donnees
      */
    void setDatabaseName(const QString& databaseName) { this->databaseName = databaseName; }

    /**
      Methode d'acces a hostAddress
      @return hostAddress: l'adresse ip ou l'alias du server host.
      */
    const QString& getHostAddress() const { return hostAddress; }

    /**
      Methode de mise a jour de hostAddress
      @param hostAddress L'adresse ip ou l'alias du server host.
      */
    void setHostAddress(const QString& hostAddress) { this->hostAddress = hostAddress; }

    /**
      Methode d'acces a hostPort
      @return hostPort: le port du server sur lequel la base de donnees est joignable.
      */
    int getHostPort() const { return hostPort; }

    /**
      Methode de mise a jour de hostPort
      @param port: Le port du server host sur lequel la base de donnees est joignable
      */
    void setHostPort(int port) { this->hostPort = port; }

    /**
      Methode d'acces a userName
      @return userName: le nom d'utilisateur utilise pour les operations sur la base de donnees
      */
    const QString& getUserName() const { return userName; }

    /**
      Methode de mise a jour de userName
      @param userName le nom d'utilisateur utilise pour les operations sur la base de donnees
      */
    void setUserName(const QString& userName) { this->userName = userName; }

    /**
      Methode d'acces a password
      @return password le mot de passe correspondant a userName
      */
    const QString& getPassword() const { return password; }

    /**
      Methode de mise a jour de password
      @param password le mot de passe correspondant a userName
      */
    void setPassword(const QString& password) { this->password = password; }
};

/**
  Surcharge l'operateur de comparaison ==.
  @param a le premier objet a comparer
  @param b le second objet a comparer
  @return <b>true</b> si les proprietes des deux objets sont egales, sinon renvoie <b>false</b>
  */
bool operator==(const DatabaseProperties& a, const DatabaseProperties& b);
#endif // DATABASEPROPERTIES_H

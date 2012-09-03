#ifndef DBINITREAD_H
#define DBINITREAD_H

#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QStringList>
#include <QtXml>
#include <QXmlQuery>
#include <core/AbstractApplication.h>
#include <com/xap/XAPMessage.h>
#include "Error.h"

class DBInitRead;

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

/**
  @class XAPNetworkProperties
  @author jhx
  @brief Classe encapsulant toutes les donnees qui permettront la configuration d'un point d'acces au
  reseau xAP.
  */
class XAPNetworkProperties {




private:
    /**
      Adresse de diffusion pour l'application en cours et pour les messages xAP qu'elle pourrait transmettre.
      On mettra la plupart du temps une adresse de broadcast, sauf pour les passerelles, qui, elles, auront des
      interlocuteurs bien definis (par exemple pour passer d'un reseau TCP/IP a un autre).
      */
    QString diffusionAddress;

    /**

      */
    int diffusionPort;

    /**
      Port d'écoute
      */
    int listeningPort;
    /**
      Précise si le heart beat est active ou non pour le reseau xAP.
      */
    bool enableHeartBeat;

    /**
      Interval de temps en secondes sur lequel sera base le HeartBeat XAP.
      */
    int heartBeatInterval;

    /**

      */
    XAPAddress appAddress;




public:

    friend class DBInitRead;
    /**
      Constructeur par defaut.
      */
    XAPNetworkProperties();

    /**
      Constructeur surcharge.
      */
    XAPNetworkProperties(const QString& diffusionAddress, int diffusionPort);

    /**
      Constructeur de recopie.
      */
    XAPNetworkProperties(const XAPNetworkProperties& other);

    /**
      Compare un objet avec l'objet courant.
      @param other l'objet a comparer
      @return <b>true</b> si la valeur des proprietes de l'objet courant sont egales a celles de l'objet a comparer. Sinon, renvoie <b>false</b>.
      */
    bool isEqual(const XAPNetworkProperties& other) const;

    /**
      Surcharge de l'operateur '='.
      @param other l'objet a recopier
      @return une reference sur l'objet courant
      */
    XAPNetworkProperties& operator=(const XAPNetworkProperties& other);

    /**
      Genere une chaine de caracteres descriptive de l'objet courant.
      @return une chaine descriptive de l'objet courant
      */
    QString toString() const;

    /**

      */
    int getHeartBeatInterval() const { return heartBeatInterval; }

    /**

      */
    void setHeartBeatInterval(int interval) { this->heartBeatInterval = interval; }

    /**

      */
    const QString& getDiffusionAddress() const { return diffusionAddress; }

    /**

      */
    void setDiffusionAddress(const QString& address) { this->diffusionAddress = address; }

    /**

      */
    int getDiffusionPort() const { return diffusionPort; }

    /**

      */
    void setDiffusionPort(int port) { this->diffusionPort = port; }

    /**

      */
    bool isEnableHeartBeat() const { return enableHeartBeat; }

    /**

      */
    void setEnableHeartBeat(bool value) { this->enableHeartBeat = value; }

    /**

      */
    const XAPAddress& getAppAddress() const { return appAddress; }

    /**

      */
    void setAppAddress(const XAPAddress& address) { this->appAddress = address; }

    /**

      */
    int getListeningPort() const { return listeningPort; }

    /**

      */
    void setListeningPort(int port) { listeningPort = port; }
};

/**

  */
bool operator==(const XAPNetworkProperties& a, const XAPNetworkProperties& b);

/**
  @class DBInitRead
  @brief Classe d'initialisation pour les applications, serveurs et demons du systeme.
  @author jhx

  La configuration basique de l'applicatif se trouve dans un fichier xml portant le nom de l'application concernée.
  On trouve dans ce fichier xml la configuration de la connection a la base de données, la configuration du réseau xAP,
  et la configuration du réseau Zigbus.
  Une fois cette configuration importée, si la connection a la base de données echoue, une exception critique est émise. Cette exception
  doit être interceptée et sa descritpion stockée dans un fichier de log. Si cet exception est lancée, l'application ne doit pas démarrer
  car elle n'a pas acces aux données nécessaire pour travailler correctement sur le système communicatif, et risquerai de créer des
  confusion au sein des appareils du réseau.
  Les données concernant les appareils appartenant au systeme se trouvent dans la base de données.
  */
class DBInitRead
{
private:
    /**

      */
    AbstractApplication* owner;

    /**
      Chemin d'acces aux fichiers de configuration.
      C'est dans ce repertoire qu'on ira chercher la config au lancement du programme
      */
    QString configDirectory;

    /**
      Nom du fichier xml contenant la config du programme
      */
    QString configFileName;


    /**
      Proprietes de la connexion a la base de donnees.
      Elle est recuperee depuis l'objet d'initialisation par le back-end des programmes pour que ceux-ci puissent
      instancier des connexions a la base de donnees.
      */
    DatabaseProperties dbProperties;


    /**
    Objet de parametrage pour la connexion au réseau xAP de l'application.
      */
    XAPNetworkProperties xapProperties;


public:
    /**
      Constructeur par defaut
      */
    DBInitRead(AbstractApplication* owner);

    /**
      Importe la configuration de l'application depuis les fichiers xml de config.
      Si les fichiers ne sont pas trouvés, s'ils sont mal formés ou qu'il ne contiennent pas les informations nécessaires a l'application,
      cette méthode lance une exception de type error::InitializationException.
      Un appel a cette methode ne construit pas l'objet de connection a la base de données, ni les composant réseau xAP et Zigbus,
      mais en importe uniquement les configurations. Charge a l'application elle-meme de construire ces objets a partir des objets
      encapsulant les informations de paramétrage. Cela permet de configurer les différentes applications du systeme grace aux seuls
      fichiers de configuration XML.
      @throw error::InitializationException

      @todo refact initilize() method whith XQuery.
      */
    void initialize();

    /**
      Importe la configuration de la connection a la base de données depuis le fichier spécifié.
      Un objet DatabaseProperties peut ensuite être récupéré avec la méthode getDbProperties().
      @throw error::InitializationException
      */
    void importDatabaseProperties(const QString& fileName);

    /**
      Importe la configuration du réseau xAP.
      L'objet XAPNetworkProperties peut ensuite être récupéré grâce à la méthode getXapProperties().
      @throw error::InitializationException
      */
    void importXAPNetworkProperties(const QString& fileName);

    /**
      Importe la configuration du réseau Zigbus.
      @todo importZigbusNetworkProperties() implementation.
      */
    void importZigbusNetworkProperties(const QString& fileName);

    /**

      */
    const QString& getConfigDirectory() const { return configDirectory; }

    /**

      */
    void setConfigDirectory(const QString& directory) { this->configDirectory = directory; }

    /**

      */
    const QString& getConfigFileName() const { return configFileName; }

    /**

      */
    void setConfigFileName(const QString& fileName) { this->configFileName = fileName; }

    /**

      */
    const DatabaseProperties& getDbProperties() const { return dbProperties; }

    /**

      */
    void setDbProperties(const DatabaseProperties &dbProperties) { this->dbProperties = dbProperties; }

    /**

      */
    const XAPNetworkProperties& getXapProperties() const { return xapProperties; }

    /**

      */
    void setXapProperties(const XAPNetworkProperties& properties) { this->xapProperties = properties; }
};

#endif // DBINITREAD_H

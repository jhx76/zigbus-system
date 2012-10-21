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
#include <core/DatabaseProperties.h>
#include <com/xap/XAPNetworkProperties.h>
#include <com/xap/XAPMessage.h>
#include <com/zbp/ZbpNetworkProperties.h>

#include "Error.h"
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

    /**

      */
    ZbpNetworkProperties zbpProperties;

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
      @todo verify importZigbusProperties() implementation.
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

    /**

      */
    const ZbpNetworkProperties& getZbpProperties() const { return zbpProperties; }

    /**

      */
    void setZbpProperties(const ZbpNetworkProperties& properties) { this->zbpProperties = properties; }
};

#endif // DBINITREAD_H

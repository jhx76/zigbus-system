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


#ifndef XAPNETWORKPROPERTIES_H
#define XAPNETWORKPROPERTIES_H

#include <com/xap/XAPMessage.h>
#include <QString>
#include <QtXmlPatterns>
#include <QDebug>

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

      */
    XAPNetworkProperties(const QString& fileName);

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

#endif // XAPNETWORKPROPERTIES_H

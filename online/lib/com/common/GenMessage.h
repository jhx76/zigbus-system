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

#ifndef GENMESSAGE_H
#define GENMESSAGE_H

#include <com/common/GenAddress.h>
#include <QDebug>


#define STR_ON "on"
#define STR_OFF "off"
#define STR_TOOGLE "toogle"

/**
  @namespace gen
  */
namespace gen {

/**
  @enum ParamKey
  */
typedef enum ParamKey {
    time,
    state,
    level,
    unit,
    text,
    displaytext,
    initialize,
    configure,

    id,
    id2,
    alterp,
    alterm,
    idpuis,
    idcmd,

    type,
    stype,
    ref,
    func,
    position,
    temp,
    hygro

} ParamKey;

/**
  @struct Param
  */
typedef struct Param {
    ParamKey key;
    QString value;

    QString KeyAsString() {
        switch(this->key) {
        case time: return "time";
        case state: return "state";
        case level: return "level";
        case unit: return "unit";
        case text: return "text";
        case displaytext: return "displaytext";
        case initialize: return "initialize";
        case configure: return "configure";
        case id: return "id";
        case id2: return "id2";
        case alterp: return "alter+";
        case alterm: return "alter-";
        case idpuis: return "idpuis";
        case idcmd: return "idcmd";
        case type: return "type";
        case stype: return "stype";
        case ref: return "ref";
        case func: return "func";
        case position: return "position";
        case temp: return "temp";
        case hygro: return "hygro";
        default: return "";
        };
    }

} Param;

}

/**
  @class GenMessage
  @author jhx
  @brief La classe GenMessage et toutes ses sous-classes fournissent une abstraction des protocols de communication
  pouvant etre utilises dans le systeme. Pour le moment, nous utilisons les protocols xAP et zigbus (cf sections suivantes pour
  un descrptif de ces protocols). Dans le futur, nous esperons pouvoir integrer d'autres protocols tel que le protocol XPL.

  <p><h2>Protocol xAP (eXtensible Automation Protocol) </h2>
  xAP est un protocole ouvert, et standard dans le domaine de la "Home Automation".
  Les messages xAP sont broadcastes sur le reseau. L'en tete du message contient des champs telle que l'adresse de l'emetteur
  et l'adresse de la cible afin que les entites du reseau puissent identifier si le message leur est destine. On utilisera le schema
  xAPBSC (xAP Basic Status and Control) pour les communications standardisees. Se reporter a <a href="http://www.xapautomation.org/index.php?title=Protocol_definition">la definition du protocol xAP</a>
  et a la <a href="http://www.xapautomation.org/index.php?title=Basic_Status_and_Control_Schema">definition de xAPBSC</a> pour plus d'information sur ce sujet.

  Un schema propre au systeme zigbus est utilise pour completer
  xAPBSC. Le schema zb-xAP contient les classes de message suivantes: zb.configure, zb.initialize, zb.ping, zb.pingresult.
    Voici un exemple d'un message xAP:\n\n
          xap-header\n
          {\n
          v=12\n
          hop=1\n
          uid=FF0123400\n
          class=zb.configure\n
          source=zigbus.controller.sysdom\n
          target=zigbus.lampe.salon:1\n
          }\n
          configure\n
          {\n
          }\n
    </p>


    <p><h2>Zigbus protocol</h2>
    Zigbus est un protocol de communication bas niveau pour les modules controllant les appareils electriques menagers.

    </p>

  */
class GenMessage
{
public:
    /**
      @enum TypeMessage
      */
    typedef enum {
        Command,
        Query,
        Information,
        Event,
        Ping,
        Ack,
        HeartBeat
    } TypeMessage;


protected:
    /**

      */
    GenAddress source;

    /**

      */
    TypeMessage typeMessage;


public:
    /**

      */
    GenMessage(const GenAddress& source, TypeMessage type);

    /**

      */
    GenMessage(const GenMessage& other);

    /**

      */
    virtual QString toString() const;

    /**

      */
    const GenAddress& getSource() const { return source; }

    /**

      */
    void setSource(const GenAddress& source) { this->source = source; }

    /**

      */
    TypeMessage getTypeMessage() const { return typeMessage; }

    /**

      */
    void setTypeMessage(TypeMessage typeMessage) { this->typeMessage = typeMessage; }

    /**

      */
    static QString paramKeyAsString(gen::ParamKey key) {
//        if(key == gen::time) return "time";
//        else if(key == gen::state) return "state";
//        else if(key == gen::level) return "level";
//        else if(key == gen::unit) return "unit";
//        else if(key == gen::text) return "text";
//        else if(key == gen::displaytext) return "display text";
//        else if(key == gen::type) return "type";
//        else if(key == gen::stype) return "sub-type";
//        else if(key == gen::id) return "id";

        switch(key) {
        case gen::time: return "time";
        case gen::state: return "state";
        case gen::level: return "level";
        case gen::unit: return "unit";
        case gen::text: return "text";
        case gen::displaytext: return "display text";
        case gen::id: return "id";
        case gen::id2: return "id2";
        case gen::type: return "type";
        case gen::stype: return "sub-type";
        case gen::ref: return "ref";
        case gen::func: return "func";
        default: return "unknown";
        }
    }

};

#endif // GENMESSAGE_H

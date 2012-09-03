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
    displaytext
} ParamKey;

/**
  @struct Param
  */
typedef struct Param {
    ParamKey key;
    QString value;
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
        PingResult,
        Configuration,
        Initialisation,
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
    virtual QString toString();

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
        if(key == gen::time) return "time";
        if(key == gen::state) return "state";
        if(key == gen::level) return "level";
        if(key == gen::unit) return "unit";
        if(key == gen::text) return "text";
        if(key == gen::displaytext) return "display text";
    }
};

#endif // GENMESSAGE_H

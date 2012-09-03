#ifndef CONFIGURATIONMESSAGE_H
#define CONFIGURATIONMESSAGE_H

#include <com/common/GenMessage.h>
#include <QList>
using namespace gen;

/**
  @class ConfigurationMessage
  @author jhx
  @brief Ce message permet de demander l'envoi des paramètres de configuration à un appareil.

 <h3>Principe de fonctionnement:</h3>
 <p>
 La configuration des appareils présents sur le réseau zigbus se fait de la manière suivante:<br>
 Le serveur de scénario ou un controleur sur le réseau envoi un message xAP de classe <b>zb.configure</b> contenant juste
 l'entete xAP et un bloc vide nommé <b>configure</b>. En réponse à cela, la passerelle vérifie la présence dans la base de données
 de l'appareil en question. Si l'appareil est trouvé, ses données de configuration sont récupérées et envoyées sous la forme
 d'un message zigbus à l'appareil.<br>
 <b>Le protocole xAP n'est donc en aucun cas tributaire de la configuration d'un appareil</b>. Il sert juste au transport de la demande
 de configuration. C'est la passerelle (BridgeDaemon) qui identifie la demande de configuration et se charge d'aller chercher la
 configuration et de l'envoyer a l'appareil.
 </p>
 <h3>Les protocoles:</h3>
<ul>
  <li>
    <b>xAP protocol:</b>\n
        example:\n
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
  </li>
  <li>
    <b>Zigbus protocol:\n</b>

      <li>Configuration d'une sortie unique en numérique:\n</li>
       <table>
        <tr>
            <th>Sortie(7 bits)</th>
            <th>Etat(1 bit)</th>
            <th>Type(5 bits)</th>
            <th>Ordre(5 bits)</th>
        </tr>
        <tr>
            <td>S4</td>
            <td>On</td>
            <td>Sortie Numerique</td>
            <td>Configure</td>
        </tr>
        <tr>
            <td>0000100</td>
            <td>1</td>
            <td>00001</td>
            <td>11110</td>
        </tr>
        <tr>
            <td>A2</td>
            <td>Off</td>
            <td></td>
            <td></td>
        </tr>
        <tr>
            <td>1100110</td>
            <td>0</td>
            <td>00001</td>
            <td>11110</td>
        </tr>
       </table>
       \n
       <li>Configuration d'une IO unique en entrée numérique:</li>
       <table>
        <tr>
            <th>Sortie(7 bits)</th>
            <th>Type(5 bits)</th>
            <th>Ordre(5 bits)</th>
        </tr>
        <tr>
            <td>S4</td>
            <td>Entrée Numerique</td>
            <td>Configure</td>
        </tr>
        <tr>
            <td>0000100</td>
            <td>00010</td>
            <td>11110</td>
        </tr>
        <tr>
            <td>A2</td>
            <td></td>
            <td></td>
        </tr>
        <tr>
            <td>1100110</td>
            <td>00010</td>
            <td>11110</td>
        </tr>
       </table>

        <li>references pour les entrees analogiques:\n</li>
            <ul>
                <li>000	Default</li>
                <li>001	Internal</li>
                <li>010	Internal 1V1</li>
                <li>011	Internal 2V56</li>
                <li>100	External</li>
            </ul>
        <li>Configure port Analogique 2 avec reference 2V56</li>
       <table>
        <tr>
            <th>Entree(7 bits)</th>
            <th>Reference(3 bits)</th>
            <th>Type(5 bits)</th>
            <th>Ordre(5 bits)</th>
        </tr>
        <tr>
            <td>A2</td>
            <td>Int 2V56</td>
            <td>Entrée Analogique</td>
            <td>Configure</td>
        </tr>
        <tr>
            <td>1100110</td>
            <td>011</td>
            <td>00010</td>
            <td>11110</td>
        </tr>
       </table>

        <li>Configure un chauffage avec Alter+ sur A1 et Alter- sur S11</li>
       <table>
        <tr>
            <th>Sortie Alter-(7 bits)</th>
            <th>Sortie Alter+(7 bits)</th>
            <th>Type(5 bits)</th>
            <th>Ordre(5 bits)</th>
        </tr>
        <tr>
            <td>S11</td>
            <td>A1</td>
            <td>Chauffage</td>
            <td>Configure</td>
        </tr>
        <tr>
            <td>0001011</td>
            <td>1100101</td>
            <td>00110</td>
            <td>11110</td>
        </tr>
       </table>

        <li>Configure une sonde temperature de type DHT11 (Hygro + Temp) sur S4 </li>
       <table>
        <tr>
            <th>Entree(7 bits)</th>
            <th>Type capteur(3 bits)</th>
            <th>Type(5 bits)</th>
            <th>Ordre(5 bits)</th>
        </tr>
        <tr>
            <td>S4</td>
            <td>DHT11</td>
            <td>Temperature</td>
            <td>Configure</td>
        </tr>
        <tr>
            <td>0000100</td>
            <td>001</td>
            <td>00111</td>
            <td>11110</td>
        </tr>
       </table>

       <li>Configure 1  servo sur 9 et sa puissance sur 10</li>
       <table>
        <tr>
            <th>IO Puissance(7 bits)</th>
            <th>IO Servo(7 bits)</th>
            <th>Type(5 bits)</th>
            <th>Ordre(5 bits)</th>
        </tr>
        <tr>
            <td>S10</td>
            <td>S9</td>
            <td>Servo</td>
            <td>Configure</td>
        </tr>
        <tr>
            <td>0001010</td>
            <td>0001001</td>
            <td>01000</td>
            <td>11110</td>
        </tr>
       </table>
  </li>
  \n<li><b>String representation</b>\n
  </li>
</ul>

@todo Message configuration Lampe
@todo Message configuration Remote
@todo Message configuration Token
@todo Message configuration Serie

  */
class ConfigurationMessage : public GenMessage
{
private:
    /**
      Adresse cible du message de configuration.
      */
    GenAddress target;

    /**
      Liste des parametres de configuration s'il y en existe.
      */
    QList<gen::Param> paramList;

public:
    /**
    Constructeur
    @param source l'adresse source du message
    @param target l'adresse cible du message
      */
    ConfigurationMessage(const GenAddress& source, const GenAddress& target);

    /**
      Constructeur de recopie
      @param other l'objet a recopier
      */
    ConfigurationMessage(const ConfigurationMessage& other);

    /**
      Défini un parametre dans la liste de parametre. Si le parametre existe deja au sein de la liste,
      sa valeur est mise a jour.
      @param key La cle du parametre
      @param value la valeur du parametre
      */
    void setParam(gen::ParamKey key, const QString& value);

    /**
      Recupere la valeur du parametre dont la cle est passée en argument
      @param key la cle du parametre a rechercher
      @return La valeur du parametre s'il existe au sein de la liste. Si le parametre n'existe pas,
      renvoie une chaine vide.
      */
    const QString& getParam(gen::ParamKey key) const;

    /**
      Ajoute un parametre en fin de liste.
      @param param le parametre a ajouter a la liste.
      */
    void append(gen::Param param) { paramList.append(param); }

    /**
      Supprime le parametre stocké a l'index @arg i. Le nombre d'occurence dans la liste est mis a jour,
      et les element suivant celui qui est supprimé sont décalé de 1 vers la gauche.
      @param i l'index de l'element a supprimer.
      */
    void removeAt(int i) { paramList.removeAt(i); }

    /**
      Renvoie le nombre d'elements contenus dans la liste de parametres
      @return le nombre d'element contenus dans la liste.
      */
    int paramCount() const { return paramList.count(); }

    /**
      Recupere une reference sur le parametre qui est stocké a l'index @arg i.
      @param i l'index de l'element a retourner
      @return le parametre situe a l'index i.
      */
    gen::Param& elementAt(int i) { return paramList[i]; }

    /**
      Recupere une reference <b>constante</b> sur le parametre qui est stocké a l'index @arg i.
      @param i l'index de l'element a retourner.
      @return le parametre situé a l'index i.
      */
    const gen::Param& at(int i) { return paramList.at(i); }

    /**
      Supprime tous les elements de la liste de parametres.
      */
    void clear() { while(!paramList.isEmpty()) paramList.takeFirst(); }

    /**
      Renvoie une reference constante sur l'adresse de la cible du message.
      @return une référence constante sur l'adresse de la cible.
      */
    const GenAddress& getTarget() const { return target; }

    /**
      Mise a jour de l'adresse de la cible.
      @param target l'adresse de la cible a attribuer au message.
      */
    void setTarget(const GenAddress& target) { this->target = target; }

    /**
      Cette methode permet de générer une chaine de caracteres descriptive de l'objet. Elle est
      composé de telle sorte qu'elle soit humainement compréhensible, c'est a dire qu'elle décrit tous
      les attributs présent dans l'objet.
      Dans notre cas, ce sera la chaine litérale du message générique.
      */
    virtual QString toString();
};

#endif // CONFIGURATIONMESSAGE_H

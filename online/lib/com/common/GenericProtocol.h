#ifndef GENERICPROTOCOL_H
#define GENERICPROTOCOL_H

/**
  <h1>GenericProtocol: traitement abstrait des messages</h1>
  <p>
  GenericProtocol est le système de traitement des messages interne à l'API de communication. Il permet
  une complète abstraction des messages reçus et envoyé, quel que soit le protocole utilisé (cf. la liste des protocoles
  supportés).
  </p>

  <h3>Sous-classes de GenericMessage</h3>
  <p>
  GenericProtocol comporte la classe GenMessage qui est en est la classe centrale.
  C'est une classe abstraite de laquelle héritent 6 autres classes qui représentent chacune
  un type de message particulier:
  <ul>
    <li>CommandMessage</li>
    <li>EventMessage</li>
    <li>InformationMessage</li>
    <li>QueryMessage</li>
    <li>PingMessage</li>
    <li>HeartBeatMessage</li>
  <ul>
  Le but de l'API de communication étant de pouvoir supporter le plus de protocoles possible, le tout message,
  entrant ou sortant, doit pouvoir être converti en l'une des sous-classes de GenMessage.
  </p>

  <h3>Adressage</h3>
  <p>Il existe plusieurs types d'adressage pour les messages generiques:
  <ul>
    <li><b>L'adressage "module":</b> il permet de s'adresser directement à un module zigbus. Sa forme est la suivante:<br/>
            @code
            ## source/target=mod(<netid>/<module id>)
            source=mod(N0/M023)
            @endcode
        <b>'source='</b>: indique que l'adresse est celle de l'emetteur<br/>
        <b>'mod()'</b>: indique le type d'adressage utilisé. Ici, c'est l'adressage module.
        <b>'N0/M0123'</b>: c'est l'argument de la fonction <b>'mod()'</b>. Contient l'id du réseau zigbus <b>N0</b> et l'id du module <b>M0123</b>
        </li>

    <li><b>L'adressage "dev":</b> C'est l'adresse d'un appareil ou d'une application et elle est de la forme:<br/>
        @code
        ## target=dev(<netid>/<type>@<location>:<instance>)
        target=dev(zigbus/lampe@exterieur:gauche)
        @endcode
        <b>'target='</b>: signifie que l'adresse est celle du destinataire<br/>
        <b>'dev()'</b>: cette fois on utilise la fonction d'adressage "dev()"<br/>
        <b>'zigbus/lampe@exterieur:gauche'</b>: l'adresse symbolique de l'appareil à contacter.
        </li>
  </ul>

  La conversion d'adresse d'un protocole à un autre nous oblige à maintenir une table de correspondance d'adresses pour les appareils et
  applications susceptibles de dialoguer avec le système.
  Cette table contiendra les adresses symboliques (type, location, symb network, instance) des entités du réseau, et leur adresse materiel (id network, id module, id pin, ...)



 </p>


    <h3>Support du protocol "Zigbus-Protocol" (Zbp)</h3>
    <h4>Structure</h4>
    <p>
    La structure principale d'un message Zbp est imposée par le champ ORDER qui est représenté par les 5 bits
    de poid faible de la trame.<br/>
    Voici la liste des valeurs que peut prendre ce champs et la ou les sous-classes de GenMessage correspondantes.
        <table>
        <tr>  <th>Order</th>  <th>generic class</th></tr>
            <tr> <td>OFF (0%)</td> <td>CommandMessage</td></tr>
            <tr> <td>ON (100%)</td> <td>CommandMessage</td></tr>
            <tr> <td>TOOGLE</td> <td>CommandMessage</td></tr>
            <tr> <td>SERVO</td> <td>CommandMessage</td></tr>
            <tr> <td>Texte</td> <td>CommandMessage</td></tr>
            <tr> <td>PWM</td> <td>CommandMessage</td></tr>
            <tr> <td>Chauffage</td> <td>CommandMessage</td></tr>
            <tr> <td>Etat</td> <td>QueryMessage</td></tr>
            <tr> <td>Serie</td> <td>CommandMessage</td></tr>
            <tr> <td>Remote</td> <td>CommandMessage</td></tr>
            <tr> <td>Ping</td> <td>PingMessage</td></tr>
            <tr> <td>Temperature(Query)</td> <td>QueryMessage</td></tr>
            <tr> <td>Temperature(response)</td> <td>InformationMessage</td></tr>
            <tr> <td>Configure</td> <td>CommandMessage</td></tr>
            <tr> <td>Initialize</td> <td>EventMessage</td></tr>
        </table>
    </p>

    <h4>Adressage</h4>



  */


#endif // GENERICPROTOCOL_H

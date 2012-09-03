/**
  @mainpage projet Zigbus

<p>
Le projet Zigbus a pour objectif de devenir un systeme domotique complet, performant et peu couteux.
Il est composé d'une série d'application C++ et Java:<br>
<ul>
    <li><a href="">Bridge-Daemon</a>: Passerelle logicielle entre le réseau LAN et le réseau zigbus. Il permet
        la traduction des différents protocoles utilisés par le systeme.</li>
    <li><a href="">Eyes</a>: Espace interactif permettant a l'utilisateur de controler le systeme.</li>
    <li><a href="">Zigbus-Mind</a>: Serveur de scénario et controleur du systeme. Toutes les taches automatisées
        émanent de cette application.</li>
</ul>
</p>
<p>
Le système s'appuie sur des modules dits "module Zigbus". Ces modules forment un réseau radio qui permet aux équipement électriques
ménager de communiquer entre eux et de réagir à des évènements survenant sur ce réseau. Le protocole utilisé par les modules est le
protocole Zigbus (Et oui, on fait ce qu'on peut !). C'est un protocole complexe, à longueur variable. La documentation du protocole est
disponible <a href="">ici</a>.
</p>


<p>
Toutes les informations relatives aux appareils appartenant au système sont stockée dans une base de données formées de fichiers xml.
La configuration des appareils est stockée dans le répertoire config du systeme de fichier, situé à la racine de repertoire du projet.
</p>

  */

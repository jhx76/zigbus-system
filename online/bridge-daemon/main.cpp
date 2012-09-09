#include <QtCore/QCoreApplication>

#include <BridgeDaemon.h>


#include <com/zbp/ZbpMessage.h>
#include <QString>
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //BridgeDaemon daemon;
    //daemon.initializeApplication();




    QString trame;
    //trame = "0000021F"; //trame : net(00), mod(02), order(init)
    //trame = "0000010C"; //trame Portail (ferme)
    //trame = "000004AC83"; //trame VNC cuisine ON



    /*
      Test Trame REQUETE TEMPERATURE
      N0/M1
 Entrée    Q  DHT11   Ordre
0000001    0   001    01011(temperature)
    => 00000122B
      */
    //trame = "00000122B";

    /*
      Test trame RESPONSE TEMPERATURE
      N0/M1
 H(64%)    temp(8°)  Entrée    R  DHT11   Ordre (temperature)
1000000     001000   0000001   1   001    01011
=> 0000011008032B
      */
    //trame = "0000011008032B";


    /*
      Test trame CONFIGURE TEMPERATURE
      N0/M1
Entrée  DHT11   temp   Ordre(configure)
0000001  001    00111  11110

=> 000000124FE
      */
    //trame = "00000124FE";

    /*
      Test trame CONFIGURE SORTIE NUMERIQUE
      N0/M1
    S4    OFF  s.num  ordre(configure)
 0000100   0   00001  11110

 => 000001203E
      */
    //trame = "000001203E";

    /*
      Test trame ON/OFF/TOOGLE
      N0/M1
10secondes  sortie(S9)  direct   Ordre(OFF)
0 001010     0001001      0       00000
=> 00000114240

10secondes  sortie(S9)  direct   Ordre(ON)
0 001010     0001001      0       00001
=> 00000114241

10secondes  sortie(S9)  direct   Ordre(TOOGLE)
0 001010     0001001      0       00010
=> 00000114242
      */
    //trame = "00000114240";
    //trame = "00000114241";
    //trame = "00000114242";


/*
    Test trame CONFIGURE HEATER
    N0/M2 (module chauffage) Pin 46/47
 alter-   alter+   chauffage  Ordre(Configure)
0101110   0101111    00110     11110
 => 0000025CBCDE
  */
    //trame = "0000025CBCDE";

/*
    Test trame CHAUFFAGE
  N0/M2 (module chauffage) Pin 46/47

 alter-   alter+  Fonc(eco) Ordre(chauffage)
0101110   0101111   010       00110
=> 000002172F46
  */
    //trame = "000002172F46";

    ZbpMessage message(trame);
    qDebug() << "ZIGBUS: '"+ message.toTrame() +"'";

    qDebug() << "building generic message ...";


/// @todo GenericMessage building From Zbp through the GenMessageFactory static class


    return a.exec();
}

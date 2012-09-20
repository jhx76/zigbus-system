#include "ZbpNetwork.h"

ZbpNetwork::ZbpNetwork(const QObject* parent) : GenNetwork("zigbus", parent)
{
}

void ZbpNetwork::initialize(const QString& str) {}


bool ZbpNetwork::startListening() {

}

bool ZbpNetwork::isListening() {

}

void ZbpNetwork::stopListening() {

}


void ZbpNetwork::sendMessage(GenMessage* message) {




}


ZbpMessage ZbpNetwork::convertAndFreeMemory(GenMessage *genericMessage) {
    ZbpMessage resultMessage;
    //if(messge == NULL)
    //    throw NullPointerException(AT, "can't convert a null message");

    switch(genericMessage->getTypeMessage()) {
    //################################
    // CONVERSION D'UNE COMMANDE
    //################################
    /*
      Peut donner une trame :
      - ON/OFF/TOOGLE
      - MOTEUR
      - PWM
      - CHAUFFAGE
      - CONFIGURE
      - SERVO
      - SERIE
      - TEXT
      - PORTAIL
    */
    case GenMessage::Command:
        CommandMessage* commandMessage = (CommandMessage*)genericMessage;
        /*if(commandMessage->contains(gen::initialize)) {
            resultMessage.setOrder(zigbus::order_INITIALIZE);
            GenAddress address = commandMessage->getTarget();

            ZbpAddress resultAddress = translateAddress(address);


        }*/

        break;

        //################################
        // CONVERSION D'UN EVENT
        //################################
        /*
          - INITIALIZE
          */
    case GenMessage::Event:
        EventMessage* eventMessage = (EventMessage*)genericMessage;

        break;

        //################################
        // CONVERSION D'UNE INFO
        //################################
        /*
          - STATE (RESPONSE)
          - TEMPERATURE (RESPONSE)
          - VERSION (RESPONSE)
          */
    case GenMessage::Information:
        InformationMessage* informationMessage = (InformationMessage*)genericMessage;

        break;

        //################################
        // CONVERSION D'UNE REQUETE
        //################################
        /*
          - STATE (QUERY)
          - TEMPERATURE (QUERY)
          - VERSION (QUERY)
          */
    case GenMessage::Query:
        QueryMessage* queryMessage = (QueryMessage*)genericMessage;

        break;

        //################################
        // CONVERSION D'UN PING
        //################################
        /*
          - PING
          */
   /* case GenMessage::Ping:
        PingMessage* pingMessage = (PingMessage*)genericMessage;

        break;*/

    default:
        //throw TranslationException();
    }







}



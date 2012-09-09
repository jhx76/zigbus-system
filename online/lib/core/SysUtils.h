#ifndef SYSUTILS_H
#define SYSUTILS_H

#include <QString>
#include <QBitArray>
#define STR_LF              "\n"
#define STR_BRACE_LEFT      "{"
#define STR_BRACE_RIGHT     "}"
//#define MAX_XAPHEADER_LINE  11
#define STR_EQUALS          "="
#define STR_GREATER         ">"
#define STR_LESS            "<"

/* MACRO pour recuperer la localisation d'une trace*/
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT /*__FUNC__*/QString(" (" __FILE__ " : " TOSTRING(__LINE__)")")
/**
  @namespace utils
  @author jhx
  @brief Le namespace utils centralise toutes les fonctions globales et classes qui sont utilisés pour effectuer des traitements
  internes.
  */
namespace utils {

/**
  @author jhx
  Fonction permettant de tronquer des chaines de caracteres grace a un separateur et une position. Tres pratique
  lorsqu'il s'agit d'analyser des protocoles de communication, il est utilise partout dans le code du systeme.
  @param base C'est la chaine de base depuis laquelle on essaie de recuperer une sous chaine
  @param separator Chaine de caractere contenant le separateur avec lequel on va tronquer la chaine de base.
  @param position C'est la position de la sous chaine que l'on veut recuperer par rapport au separateur. La premiere position est a 0.
  @param returnbase booleen specifiant que s'il y a une erreur pendant le traitement, on renvoie la chaine de base ou non. Lorsqu'il est
  a false, ce qui est la valeur par defaut, on renvoie une chaine vide. Lorsqu'il est a true, on renvoie la chaine de base.
  */
QString getSousChaine(const QString& base, const QString& separator, int position, bool returnbase = false);


}




class GenMessage;



#endif // SYSUTILS_H

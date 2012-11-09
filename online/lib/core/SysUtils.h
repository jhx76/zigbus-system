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

#ifndef SYSUTILS_H
#define SYSUTILS_H

#include <QString>
#include <QBitArray>
#define STR_LF              "\n"
#define STR_BRACE_LEFT      "{"
#define STR_BRACE_RIGHT     "}"
#define STR_EQUALS          "="
#define STR_GREATER         ">"
#define STR_LESS            "<"

/* MACRO pour recuperer la localisation d'une trace*/
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT QString(" [" __FILE__ "]" TOSTRING(__LINE__)" ")
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

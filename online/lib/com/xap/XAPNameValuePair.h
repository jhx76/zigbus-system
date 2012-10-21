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


#ifndef _XAPNAMEVALUEPAIR_H
#define _XAPNAMEVALUEPAIR_H

#include <QString>

/**
  @class XAPNameValuePair
  @author jhx
  @date 23/09/2011
  @brief XAPNameValuePair class provide a memory storage and process way for the xAP name-value pairs.
  XAPNameValuePair is composed of a name (the key) and a corresponding value.
  A xAP name-value pair has the following string character representation :
  [name]=[value]<LF>
  */
class XAPNameValuePair {
  private:
    /**
      The key/name part of the name-value pair.
      */
    QString name;

    /**
      The value part of the name-value pair.
      */
    QString value;

  public:
    /**
      Default constructor.
      */
    XAPNameValuePair();

    /**
      Override constructor.
      @param name The name part of the name-value pair
      @param value The value part of the name-value pair
      */
    XAPNameValuePair(const QString & name, const QString & value);

    /**
      Copy constructor
      @param other The XAPNameValuePair to copy.
      */
    XAPNameValuePair(const XAPNameValuePair & other);

    /**
      Default destructor.
      */
    virtual ~XAPNameValuePair();

    /**
      Construct a XAPNameValuePair object from its string character representation.
      @param str The string character representation from which to construct the XAPNameValuePair object.
      */
    static XAPNameValuePair fromString(const QString &str);

    /**
      @return Returns the string character representation of the XAPNameValuePair
      */
    QString toString() const;

    /**
      @return Returns the name part of the name-value pair
      */
    inline const QString & getName() const { return this->name; }


    /**
      Set the name part of the xAP name-value pair.
      @param name The name to set
      */
    inline void setName(const QString & name) { this->name = name; }

    /**
      @return Returns the value part of the name-value pair.
      */
    inline const QString & getValue() const { return this->value; }

    /**
      Set the value part of the name-value pair.
      @param value The value part to set.
      */
    inline void setValue(const QString & value) { this->value = value; }

    XAPNameValuePair& operator=(const XAPNameValuePair& other) {
        this->name = other.name;
        this->value = other.value;
        return *this;
    }

};
#endif

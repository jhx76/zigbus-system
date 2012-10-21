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



#ifndef _XAPBLOCK_H
#define _XAPBLOCK_H


#include <com/xap/XAPNameValuePair.h>
#include <QString>
#include <QList>

/**
  @class XAPBlock
  @author jhx
  @date 24/09/2011
  @brief XAPBlock class encapsulate a list of XAPNameValuePair objects.
  The XAPBlock is a composition of : a block name (a string) and a list of name-value pairs.
  A block represent an information within a xAP message.

  blockname<LF>
  {<LF>
  ...
  name-value pair list
  ...
  }<LF>

  */
class XAPBlock {
  private:
    /**
      The block name allow application to retrieve informations within a xAP message.
      The name that should take a block depends of the xAP message class, and its corresponding xAP schema/structure.
      */
    QString blockname;

protected:
    /**
      The list of name-value pairs.
      The number of pairs, their name and the value that they should take depends of the xAP message class and its corresponding xAP schema/structure.
      */
    QList<XAPNameValuePair> *nvlist;


  public:
    /**
      Default constructor.
      */
    XAPBlock();

    /**
      Override constructor.
      @param blockname The name of the block.
      */
    XAPBlock(const QString & blockname);

    /**
      Copy constructor
      @param other The other xAP block to copy within the new xAP block.
      */
    XAPBlock(const XAPBlock & other);

    /**
      Default destructor
      */
    ~XAPBlock();

    /**
      @return Returns the number of name-value pairs contained in the xAP block.
      */
    int count() const;

    /**
      Retrieves the index of the first element in the list having a name equal to @arg nvname.
      If the name is not found in the list, a call to this method will return -1.
      */
    int indexOf(const QString& nvname) {
        for(int i = 0; i < count(); i++) {
            if(elementAt(i).getName() == nvname)
                return i;
        }
        return -1;
    }

    /**
      @return Returns true value if the name-value pair list is empty. Otherwise, returns false.
      */
    bool isEmpty() const;

    /**
      Clear the name-value pair list. After a call of this method, the list will be empty.
      */
    void clear();

    /**
      Search a name-value pair that have the nvname as name.
      @param nvname The name of the name-value pair searched.
      @return Returns true value if the block contains a xAP name-value pair having the name
              equals to nvname. Otherwise, return false.
      */
    bool contains(const QString & nvname) const;

    /**
       This method allow the programmer parse a xap block. Return the XAPNameValuePair found at the i index within the list.
       @param i the index of the XAPNameValuePair required.
       @return Returns the XAPNameValuePair object found at the i index.
      */
    const XAPNameValuePair & at(int i) const ;

    /**

      */
    XAPNameValuePair& elementAt(int i);

    /**
        Remove from the list the XAPNameValuePair at found the i index.
        @param i The index of the XAPNameValuePair to remove from the list.
      */
    void removeAt(int i);

    /**
      Append a XAPNameValuePair object to the name-value pair list.
      @param nvpair The XAPNameValuePair object to append to the list.
      */
    void append(const XAPNameValuePair & nvpair);

    /**
      Append a XAPNameValuePair object to the name-value pair list.
      @param nvname The name of the name-value pair to append.
      @param nvvalue The value of the name-value pair to append.
      */
    void append(const QString & nvname, const QString & nvvalue);

    /**
      @return Returns a string character representation of the xAP message block.
      */
    QString toString() const;

    /**
      @return Returns the block name of the xAP block.
      */
    inline const QString & getBlockname() const { return blockname; }

    /**
      Set the name of the xAP block.
      @param blockname The value to set to the xAP block name.
      */
    inline void setBlockname(const QString & blockname) { this->blockname = blockname; }

    XAPBlock& operator=(const XAPBlock &other) {
        this->blockname = other.blockname;
        this->nvlist->clear();
        for(int i = 0; i < other.nvlist->count(); i++) {
            XAPNameValuePair nvpair = other.nvlist->at(i);
            this->nvlist->append(nvpair);
        }
        return *this;
    }

};
#endif

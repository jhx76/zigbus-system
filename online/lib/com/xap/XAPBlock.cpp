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


#include "XAPBlock.h"
#include "XAPNameValuePair.h"

XAPBlock::XAPBlock(){
   nvlist = new QList<XAPNameValuePair>;
}

//----------------------------------------------------------------------------

XAPBlock::XAPBlock(const QString & blockname){
    this->blockname = blockname;
    nvlist = new QList<XAPNameValuePair>;
}

//----------------------------------------------------------------------------

XAPBlock::XAPBlock(const XAPBlock & other){
    this->blockname = other.blockname;
    nvlist = new QList<XAPNameValuePair>;
    for(int i = 0; i < other.count(); i++)
        this->append(XAPNameValuePair(other.at(i).getName(), other.at(i).getValue()));
}

//----------------------------------------------------------------------------

XAPBlock::~XAPBlock(){
   /* for(int i = 0; i < nvlist->count(); i++)
        nvlist->removeAt(i);*/
    while(!nvlist->isEmpty())
        nvlist->takeFirst();
    delete nvlist;
}

//----------------------------------------------------------------------------

int XAPBlock::count() const {
    return nvlist->count();
}

//----------------------------------------------------------------------------

bool XAPBlock::isEmpty() const {
    return nvlist->isEmpty();
}

//----------------------------------------------------------------------------

void XAPBlock::clear() {
    nvlist->clear();
}

//----------------------------------------------------------------------------

bool XAPBlock::contains(const QString & nvname) const  {
    for(int i = 0; i < nvlist->count(); i++)
        if(nvlist->at(i).getName() == nvname)
            return true;

    return false;
}

//----------------------------------------------------------------------------

const XAPNameValuePair & XAPBlock::at(int i) const {
    return nvlist->at(i);
}

//----------------------------------------------------------------------------

void XAPBlock::removeAt(int i) {
//    nvlist->removeAt(i);
    nvlist->takeAt(i);
}

//----------------------------------------------------------------------------

void XAPBlock::append(const XAPNameValuePair & nvpair) {
    nvlist->append(nvpair);
}

//----------------------------------------------------------------------------

void XAPBlock::append(const QString & nvname, const QString & nvvalue) {
    append(XAPNameValuePair(nvname, nvvalue));
}

//----------------------------------------------------------------------------

QString XAPBlock::toString() const {
    QString str = "";
    if(blockname.isEmpty()) return "";
    str += blockname;
    str += "\n";
    str += "{\n";
    for(int i = 0; i < nvlist->count(); i++)
        if(!nvlist->at(i).getValue().isEmpty()) str += nvlist->at(i).toString();
    str += "}\n";
    return str;
}

//----------------------------------------------------------------------------

XAPNameValuePair& XAPBlock::elementAt(int i) {
    return nvlist->operator [](i);
}

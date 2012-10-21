
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

#include "XAPNameValuePair.h"

XAPNameValuePair::XAPNameValuePair(){
    name = "";
    value = "";
}

XAPNameValuePair::XAPNameValuePair(const QString & name, const QString & value){
    this->name = name;
    this->value = value;
}

XAPNameValuePair::XAPNameValuePair(const XAPNameValuePair & other){
    name = other.getName();
    value = other.getValue();
}

XAPNameValuePair::~XAPNameValuePair(){

}

XAPNameValuePair XAPNameValuePair::fromString(const QString & str)
{
    XAPNameValuePair nvpair;
    QString name, value;
    name = str.mid(0, str.indexOf("="));
    if(!name.isEmpty()) {
        value = str.mid(str.indexOf("=") + 1, str.count() - str.indexOf("=") + 1);
        nvpair = XAPNameValuePair(name, value);
    }
    return nvpair;
}

QString XAPNameValuePair::toString() const {

    QString str = name + "=" + value + "\n";
    if(value.isEmpty())
        return "";
    return str;
}


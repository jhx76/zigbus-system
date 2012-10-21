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

#include "SysUtils.h"


namespace utils {

QString getSousChaine(const QString& base, const QString& separator, int position, bool returnbase) {
    QString tmp = "";
    QString rslt = "";
    int cursor1 = -1, cursor2 = -1;
    if(!base.contains(separator)) {
        if(returnbase)
            return base;
        return rslt;
    }
    if(base.count(separator) < position)  {
        if(returnbase)
            return base;
        return rslt;
    }

    int i = 0;
    while(i <= position)
    {
        cursor1 = cursor2 + 1;
        cursor2 = base.indexOf(separator, cursor1 + 1);
        i++;
    }
    if(cursor2 == -1)
        tmp = base.right(base.count() - cursor1);
    else
        tmp = base.mid(cursor1, cursor2 - cursor1);
    return tmp;
}




}




//----------------------------------------------------------------------------



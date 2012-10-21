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

#include "XAPUtils.h"

QString XAPUtils::getLine(QString _str, int line)
{
    QString rslt = "";
    if(line > 0 && !_str.isEmpty() && line <= _str.count(STR_LF))
    {
        QString tmp = "";
        for(int i = 0, cursor1 = 0, cursor2 = 0; i < line || cursor2 == -1; i++)
        {
            tmp = _str.left(tmp.indexOf(STR_LF, cursor2));
            tmp = tmp.mid(cursor1, cursor2 - cursor1);
            cursor1 = cursor2 + 1;
            cursor2 = _str.indexOf(STR_LF, cursor1);
        }
        rslt = tmp;
    }
    return rslt;
}

//----------------------------------------------------------------------------

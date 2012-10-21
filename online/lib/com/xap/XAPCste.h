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

#ifndef XAPCSTE_H
#define XAPCSTE_H


#define STR_BRACE_LEFT                  "{"
#define STR_BRACE_RIGHT                 "}"
#define STR_LF                          "\n"
#define STR_EQUALS                      "="

#define STR_XAPVERSION                  "v"
#define STR_XAPHEADER                   "xap-header"
#define STR_XAPHOP                         "hop"
#define STR_XAPUID                         "uid"
#define STR_XAPCLASS                       "class"
#define STR_XAPSOURCE                      "source"
#define STR_XAPTARGET                      "target"

#define MAX_XAPHEADER_LINE               12

#define XAP_ERROR_WHEN_DATAGRAM_SEND    -1
#define XAP_SOCKET_CLOSED               -2
#define XAP_NULL_MESSAGE_ERROR          -3

#endif // XAPCSTE_H

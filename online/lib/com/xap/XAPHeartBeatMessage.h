
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

#ifndef XAPHEARTBEATMESSAGE_H
#define XAPHEARTBEATMESSAGE_H

#include <com/xap/XAPMessage.h>
#include <com/xap/XAPHeader.h>

/**
    @author jhx
    @date 07/11/2011
    @brief A message that notifies all other zigbus entities about its living.
  */
class XAPHeartBeatMessage : public XAPMessage
{
private:
    /**

      */
    int interval;

    /**

      */
    int port;


public:
    /**

      */
    XAPHeartBeatMessage(const QString& xapsource, const QString& uid = "FF123400", int hop = 1, const QString& version = "12");

    /**

      */
    XAPHeartBeatMessage(const XAPHeartBeatMessage& other);

    /**

      */
    virtual ~XAPHeartBeatMessage();

    /**

      */
    virtual QString toString() const;

    /**

      */
    int getPort() const {
        return port;
    }

    /**

      */
    void setPort(int i);
    /**

      */
    int getInterval() { return interval; }

    /**

      */
    void setInterval(int i);
};

#endif // XAPHEARTBEATMESSAGE_H

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

#ifndef GENMESSAGEFACTORY_H
#define GENMESSAGEFACTORY_H

#include <com/common/GenAddress.h>
#include <com/common/GenMessage.h>
#include <com/common/CommandMessage.h>
#include <com/common/QueryMessage.h>
#include <com/common/InformationMessage.h>
#include <com/common/EventMessage.h>
#include <com/common/HeartBeatMessage.h>

#include <com/zbp/ZbpMessage.h>
#include <com/zbp/ZbpAddress.h>
#include <com/zbp/zigbus.h>

#include <com/xap/XAPMessage.h>
#include <com/xap/XAPUtils.h>
#include <com/xap/XAPHeartBeatMessage.h>

#include <core/SingleDAT.h>

#include <core/SysUtils.h>

/**
    @class GenMessageFactory
    @author jhx
    @date 19/02/2012
    @brief GenMessageFactory is designed to manage the generic messages instanciation.
    It allows you to create message instances from different protocols. See the table bellow to know the
    supported protocols:
    @todo protocol table documentation
  */
class GenMessageFactory
{
private:
    static SingleDAT* deviceAddressTranslator;

    /**

      */
    static CommandMessage* createCommandMessage(ZbpMessage& message);

    /**

      */
    static CommandMessage* createCommandMessage(XAPMessage& message);

    /**

      */
    static QueryMessage* createQueryMessage(XAPMessage& message);

    /**

      */
    static QueryMessage* createQueryMessage(ZbpMessage& message);

    /**

      */
    static InformationMessage* createInformationMessage(XAPMessage& message);

    /**

      */
    static InformationMessage* createInformationMessage(ZbpMessage& message);

    /**

      */
    static EventMessage* createEventMessage(XAPMessage& message);

    /**

      */
    static EventMessage* createEventMessage(ZbpMessage& message);

    /**

      */
    static HeartBeatMessage* createHeartBeatMessage(XAPMessage& message);

    /**

      */
    static HeartBeatMessage* createHeartBeatMessage(ZbpMessage& message);

public:
    /**

      */
    static GenMessage* createMessage(ZbpMessage& message);

    /**

      */
    static GenMessage* createMessage(XAPMessage& message);

    /**

      */
    static void setDeviceAddressTranslator(SingleDAT* DAT) {
        deviceAddressTranslator = DAT;
    }
};

#endif // GENMESSAGEFACTORY_H

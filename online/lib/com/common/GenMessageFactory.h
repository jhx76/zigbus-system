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

#include <com/xap/XAPMessage.h>
#include <com/xap/XAPUtils.h>
#include <com/xap/XAPHeartBeatMessage.h>

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
};

#endif // GENMESSAGEFACTORY_H

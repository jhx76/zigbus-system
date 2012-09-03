#ifndef QUERYMESSAGE_H
#define QUERYMESSAGE_H

#include <com/common/GenMessage.h>

#include <QList>

/**
  @class QueryMessage
  @author jhx
  @date

  @brief
  */
class QueryMessage : public GenMessage
{
private:
    /**

      */
    GenAddress target;

public:
    /**

      */
    QueryMessage(const GenAddress& source, const GenAddress& target);

    /**

      */
    QueryMessage(const QueryMessage& other);

    /**

      */
    const GenAddress& getTarget() const { return target; }

    /**

      */
    void setTarget(const GenAddress& target) { this->target = target; }


    /**

      */
    virtual QString toString();
};

#endif // QUERYMESSAGE_H

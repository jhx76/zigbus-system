#ifndef EVENTMESSAGE_H
#define EVENTMESSAGE_H

#include <QList>
#include <com/common/GenAddress.h>
#include <com/common/GenMessage.h>

using namespace gen;

/**

  */
class EventMessage : public GenMessage
{
private:
    /**

      */
    QList<Param> paramList;

public:
    /**

      */
    EventMessage(const GenAddress& source);

    /**

      */
    EventMessage(const EventMessage& other);

    /**

      */
    const QString& getParam(ParamKey key) const;

    /**

      */
    void setParam(ParamKey key, const QString& value);

    /**

      */
    bool contains(ParamKey key) const;

    /**

      */
    gen::Param& elementAt(int i);

    /**

      */
    const gen::Param& at(int i) const;

    /**

      */
    void append(const gen::Param& param);

    /**

      */
    void removeAt(int i);

    /**

      */
    int paramCount() const;

    /**

      */
    bool isEmpty() const;

    /**

      */
    void clear();

    /**

      */
    virtual QString toString();

};

#endif // EVENTMESSAGE_H

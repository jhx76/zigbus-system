#ifndef COMMANDMESSAGE_H
#define COMMANDMESSAGE_H

#include <com/common/GenMessage.h>
#include <QList>

using namespace gen;

/**

  */
class CommandMessage : public GenMessage
{
private:
    /**

      */
    GenAddress target;

    /**

      */
    QList<Param> paramList;

public:
    /**

      */
    CommandMessage(const GenAddress& source, const GenAddress& target);

    /**

      */
    CommandMessage(const CommandMessage& other);

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

    /**

      */
    const GenAddress& getTarget() const { return target; }

    /**

      */
    void setTarget(const GenAddress& target) { this->target = target; }
};

#endif // COMMANDMESSAGE_H

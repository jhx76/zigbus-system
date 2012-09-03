#ifndef INFORMATIONMESSAGE_H
#define INFORMATIONMESSAGE_H

#include <com/common/GenMessage.h>
#include <QList>

/**
  @class InformationMessage
  @author jhx
  @date
  @brief InformationMessage class allows you to manage information messages in your application.
  */
class InformationMessage : public GenMessage
{
private:
    /**

      */
    QList<gen::Param> paramList;

public:
    /**

      */
    InformationMessage(const GenAddress& source);

    /**

      */
    InformationMessage(const InformationMessage& other);

    /**

      */
    const QString& getParam(gen::ParamKey key) const;

    /**

      */
    void setParam(gen::ParamKey key, const QString& value);

    /**

      */
    bool contains(gen::ParamKey key) const;

    /**

      */
    int paramCount() const;

    /**

      */
    const gen::Param& at(int i) const;

    /**

      */
    gen::Param& elementAt(int i);

    /**

      */
    void append(const gen::Param& param);

    /**

      */
    void removeAt(int i);

    /**

      */
    void clear();

    /**

      */
    bool isEmpty() const;

    /**

      */
    virtual QString toString();
};

#endif // INFORMATIONMESSAGE_H

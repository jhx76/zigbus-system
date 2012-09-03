#ifndef _XAPMESSAGE_H
#define _XAPMESSAGE_H

#include <QString>
#include <QList>
#include <QDebug>
#include <core/Error.h>
#include <core/SysUtils.h>
#include <com/xap/XAPCste.h>
#include <com/xap/XAPBlock.h>
#include <com/xap/XAPHeader.h>
#include <com/xap/XAPNameValuePair.h>

/**

  */
class XAPAddress {
private:
    /**

      */
    QString vendor;

    /**

      */
    QString type;

    /**

      */
    QString location;

    /**

      */
    QString instance;

public:
    /**

      */
    XAPAddress();

    /**

      */
    XAPAddress(const QString& vendor, const QString& type, const QString& location, const QString& instance = "");

    /**

      */
    XAPAddress(const XAPAddress& other);

    /**

      */
    static XAPAddress fromString(const QString& src);

    /**

      */
    const QString& getVendor() const { return vendor; }

    /**

      */
    void setVendor(const QString& vendor) { this->vendor = vendor; }

    /**

      */
    const QString& getType() const { return type; }

    /**

      */
    void setType(const QString& type) { this->type = type; }

    /**

      */
    const QString& getLocation() const { return location; }

    /**

      */
    void setLocation(const QString& location) { this->location = location; }

    /**

      */
    const QString& getInstance() const { return instance; }

    /**

      */
    void setInstance(const QString& instance) { this->instance = instance; }

    /**

      */
    bool isEqual(const XAPAddress& address) const {
        return (this->getVendor() == address.getVendor() &&
                this->getType() == address.getType() &&
                this->getLocation() == address.getLocation() &&
                this->getInstance() == address.getInstance());
    }

    /**

      */
    XAPAddress& operator=(const XAPAddress& other);

    /**

      */
    QString toString() const {
        QString rslt = vendor+"."+type+"."+location;
        rslt += (instance.isEmpty() ? "" : ":"+instance);
        return rslt;
    }
};

/**

  */
bool operator==(const XAPAddress& a, const XAPAddress& b);

/**
  @class XAPMessage
  @author jhx
  @date 25/09/2011

  @brief XAPMessage class allow the developper to storage xAP messages in memory.
  The XAPMessage objects can be built from string characters (see the fromString() static method).
  xAP messages are composed of a header block, and a list of other xAP blocks. The header block defines the
  schema of the message and the way to handle it. The list of xAP blocks and their internal structure are conform
  to the schema defined in the header.
  So, the developper has to check the xAP message class to apply process to the message.
  */
class XAPMessage {

private:
  /**

    */
    QList<XAPBlock>* blockList;

protected:
  /**

    */
    XAPHeader *header;

public:

    /**

      */
    XAPMessage();

    /**

      */
    XAPMessage(const QString & xapclass
               , const QString & xapsource
               , const QString  & target = ""
               , const QString & uid = "FF123400"
               , int hop = 1
               , const QString & version = "12");

    /**

      */
    XAPMessage(const XAPMessage & other);

    /**

      */
    XAPAddress getXAPSource() const;

    /**

      */
    XAPAddress getXAPTarget() const;

    /**

      */
    static XAPMessage fromString(const QString & str);

    /**

      */
    virtual ~XAPMessage();

    /**

      */
    bool contains(const QString & blockname) const;

    /**

      */
    bool isEmpty() const;

    /**

      */
    void append(const XAPBlock & block) const;

    /**

      */
    int count() const;

    /**

      */
    const XAPBlock & at(int i) const;

    /**

      */
    XAPBlock& elementAt(int i);

    /**

      */
    void removeAt(int i) const;

    /**

      */
    virtual QString toString() const;

    /**

      */
    void clear();

    /**

      */
    inline XAPHeader& getHeader() { return *header; }

    /**

      */
    inline void setVersion(const QString & str) { header->setVersion(str); }

    /**

      */
    inline const QString & getVersion() const { return header->getVersion(); }

    /**

      */
    inline void setHopCount(int hop) { header->setHop(hop); }

    /**

      */
    inline int getHopCount() const { return header->getHop(); }

    /**

      */
    inline void setUid(const QString &uid) { header->setUid(uid); }

    /**

      */
    inline const QString & getUid() const { return header->getUid(); }

    /**

      */
    inline void setClass(const QString & xapclass) { header->setClass(xapclass); }

    /**

      */
    inline const QString & getClass() const { return header->getClass(); }

    /**

      */
    inline void setSource(const QString & source) { header->setSource(source); }

    /**

      */
    inline const QString & getSource() const { return header->getSource(); }

    /**

      */
    inline void setTarget(const QString & target) { header->setTarget(target); }

    /**

      */
    inline const QString& getTarget() const { return header->getTarget(); }

    /**

      */
    XAPMessage& operator=(const XAPMessage& other) {
        this->header = new XAPHeader(*(other.header));
        this->blockList->clear();
        for(int i = 0; i < other.blockList->count(); i++) {
            XAPBlock tmpBlock = other.blockList->at(i);
            this->blockList->append(tmpBlock);
        }
        return *this;
    }

    QString valueOf(const QString& blockName, const QString& nvname);

};
#endif

#ifndef _XAPHEADER_H
#define _XAPHEADER_H


#include <com/xap/XAPBlock.h>
#include <com/xap/XAPNameValuePair.h>
#include <core/SysUtils.h>
#include <com/xap/XAPCste.h>
#include <QDebug>

/**
  @class XAPHeader
  @author jhx
  @date 24/09/2011

  @brief XAPHeader provide a representation of the header of a xAP message.
  This class inherits the XAPBlock class. So, a XAPHeader object is processed like a XAPBlock, but its
  schema is predefined. A xap header is the first block of a xAP message. It contains the name-value pairs
  that define the structure of the message. The header should contain the following name-value pairs:
  <ul>
  <li>v=[xAP version (default 12)]</li>
  <li>hop=[hop count]</li>
  <li>uid=[unique identifier target]</li>
  <li>class=[xAP message class]</li>
  <li>source=[xAP message source address]</li>
  <li>target=[xAP message target adddress (only for targeting messages)]</li>
  </ul>
  */
class XAPHeader : public XAPBlock {
  public:
    /**
      Default constructor.
      */
    XAPHeader();

    /**
      Override constructor.
      @param source
      @param xapclass
      @param uid
      @param hop
      @param version
      */
    XAPHeader(const QString & source
                         , const QString & xapclass
                         , const QString & uid = ""
                         , int hop = 1
                         , const QString & version = "12");

    /**
      Override constructor.
      @param source
      @param target
      @param xapclass
      @param uid
      @param hop
      @param version
      */
    XAPHeader(const QString & source
              , const QString & target
              , const QString & xapclass
              , const QString & uid = ""
              , int hop = 1
              , const QString & version = "12");

    /**
      Copy constructor.
      @param other
      */
    XAPHeader(const XAPHeader & other);

    /**

      */
    XAPHeader& operator=(const XAPHeader& other);

    /**
      @return Returns the value of the xAP protocol version used.
      */
    const QString & getVersion() const ;

    /**
      Set the value of the version name-value pair.
      @param version The version value to set
      */
    void setVersion(const QString & version);

    /**
      @return Returns the value of the source name-value pair.
      */
    const QString & getSource() const ;

    /**
      Set the value of the source name-value pair.
      @param source The source value to set.
      */
    void setSource(const QString & source);

    /**
      @return Returns the value of the class name-value pair.
      */
    const QString & getClass() const ;

    /**
      Set the value of the class name-value pair.
      @param xapclass The class value to set.
      */
    void setClass(const QString & xapclass) ;

    /**
      @return Returns the value of the target name-value pair.
      */
    const QString & getTarget() const ;

    /**
      Set the value of the target name-value pair.
      @param target The target value to set.
      */
    void setTarget(const QString & target);

    /**
     @return Returns the value of the uid name-value pair.
      */
    const QString & getUid() const ;

    /**
      Set the value of the uid name-value pair
      @param uid The uid value to set.
      */
    void setUid(const QString & uid);

    /**
      @return Returns the value of the hop name-value pair.
      */
    int getHop() const ;

    /**
      Set the value of the hop name-value pair.
      @param hop The hop value to set.
      */
    void setHop(int hop);
};
#endif

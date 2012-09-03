#ifndef _XAPNAMEVALUEPAIR_H
#define _XAPNAMEVALUEPAIR_H

#include <QString>

/**
  @class XAPNameValuePair
  @author jhx
  @date 23/09/2011
  @brief XAPNameValuePair class provide a memory storage and process way for the xAP name-value pairs.
  XAPNameValuePair is composed of a name (the key) and a corresponding value.
  A xAP name-value pair has the following string character representation :
  [name]=[value]<LF>
  */
class XAPNameValuePair {
  private:
    /**
      The key/name part of the name-value pair.
      */
    QString name;

    /**
      The value part of the name-value pair.
      */
    QString value;

  public:
    /**
      Default constructor.
      */
    XAPNameValuePair();

    /**
      Override constructor.
      @param name The name part of the name-value pair
      @param value The value part of the name-value pair
      */
    XAPNameValuePair(const QString & name, const QString & value);

    /**
      Copy constructor
      @param other The XAPNameValuePair to copy.
      */
    XAPNameValuePair(const XAPNameValuePair & other);

    /**
      Default destructor.
      */
    virtual ~XAPNameValuePair();

    /**
      Construct a XAPNameValuePair object from its string character representation.
      @param str The string character representation from which to construct the XAPNameValuePair object.
      */
    static XAPNameValuePair fromString(const QString &str);

    /**
      @return Returns the string character representation of the XAPNameValuePair
      */
    QString toString() const;

    /**
      @return Returns the name part of the name-value pair
      */
    inline const QString & getName() const { return this->name; }


    /**
      Set the name part of the xAP name-value pair.
      @param name The name to set
      */
    inline void setName(const QString & name) { this->name = name; }

    /**
      @return Returns the value part of the name-value pair.
      */
    inline const QString & getValue() const { return this->value; }

    /**
      Set the value part of the name-value pair.
      @param value The value part to set.
      */
    inline void setValue(const QString & value) { this->value = value; }

    XAPNameValuePair& operator=(const XAPNameValuePair& other) {
        this->name = other.name;
        this->value = other.value;
        return *this;
    }

};
#endif

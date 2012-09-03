
#include "XAPHeader.h"

XAPHeader::XAPHeader()
    : XAPBlock("xap-header")
{
    append(XAPNameValuePair("v", "12"));
    append(XAPNameValuePair("hop", "1"));
    append(XAPNameValuePair("uid", ""));
    append(XAPNameValuePair("class", ""));
    append(XAPNameValuePair("source", ""));
    append(XAPNameValuePair("target", ""));
}

//----------------------------------------------------------------------------

XAPHeader::XAPHeader(const QString &source
                     , const QString &xapclass
                     , const QString &uid
                     , int hop
                     , const QString &version)
    : XAPBlock("xap-header")
{
    append(XAPNameValuePair("v", version));
    append(XAPNameValuePair("hop", QString::number(hop)));
    append(XAPNameValuePair("uid",  uid));
    append(XAPNameValuePair("class", xapclass));
    append(XAPNameValuePair("source", source));
    append(XAPNameValuePair("target", ""));
}

//----------------------------------------------------------------------------

XAPHeader::XAPHeader(const QString & source
                     , const QString & target
                     , const QString & xapclass
                     , const QString & uid
                     , int hop
                     , const QString & version)
    : XAPBlock("xap-header")
{
    append(XAPNameValuePair("v", version));
    append(XAPNameValuePair("hop", QString::number(hop)));
    append(XAPNameValuePair("uid",  uid));
    append(XAPNameValuePair("class", xapclass));
    append(XAPNameValuePair("source", source));
    append(XAPNameValuePair("target", target));
}

//----------------------------------------------------------------------------

XAPHeader::XAPHeader(const XAPHeader & other) : XAPBlock()
{

    this->setBlockname("xap-header");
    append(XAPNameValuePair("v", other.getVersion()));
    append(XAPNameValuePair("hop", QString("1")));
    append(XAPNameValuePair("uid",  other.getUid()));
    append(XAPNameValuePair("class", other.getClass()));
    append(XAPNameValuePair("source", other.getSource()));
    append(XAPNameValuePair("target", other.getTarget()));
}

//----------------------------------------------------------------------------

const QString& XAPHeader::getClass() const {
    for(int i = 0; i < this->count(); i ++) {
        if(at(i).getName() == "class")
            return at(i).getValue();
    }
    return "";
}

//----------------------------------------------------------------------------

void XAPHeader::setClass(const QString &value) {
    for(int i = 0; i < this->count(); i ++) {
        if(this->at(i).getName() == STR_XAPCLASS) {
            nvlist->takeAt(i);
            break;
        }
    }
    this->nvlist->append(XAPNameValuePair(STR_XAPCLASS, value));
}

//----------------------------------------------------------------------------

int XAPHeader::getHop() const {
    int rslt = -1;
    for(int i = 0; i < count(); i++) {
        if(at(i).getName() == STR_XAPHOP) {
            bool ok;
            rslt = at(i).getValue().toInt(&ok);
            if(!ok) rslt = -1;
        }
    }
    return rslt;
}

//----------------------------------------------------------------------------

void XAPHeader::setHop(int hop) {
    for(int i = 0; i < count(); i++){
        if(at(i).getName() == STR_XAPHOP) {
            nvlist->takeAt(i);
            break;
        }
    }
    nvlist->append(XAPNameValuePair(STR_XAPHOP, QString::number(hop)));
}

//----------------------------------------------------------------------------

const QString & XAPHeader::getSource() const {
    for(int i = 0; i < count(); i++) {
        if(at(i).getName() == STR_XAPSOURCE)
            return at(i).getValue();
    }
    return "";
}

//----------------------------------------------------------------------------

void XAPHeader::setSource(const QString &source) {
    for(int i = 0; i < count(); i++) {
        if(at(i).getName() == STR_XAPSOURCE) {
            nvlist->takeAt(i);
            break;
        }
    }
    nvlist->append(XAPNameValuePair(STR_XAPSOURCE, source));
}

//----------------------------------------------------------------------------

const QString & XAPHeader::getTarget() const{
    for(int i = 0; i < count(); i++)
    {
        if(at(i).getName() == STR_XAPTARGET)
            return at(i).getValue();
    }
    return "";
}

//----------------------------------------------------------------------------

void XAPHeader::setTarget(const QString &target) {
    for(int i = 0; i < count(); i++) {
        if(at(i).getName() == STR_XAPTARGET) {
            nvlist->takeAt(i);
            break;
        }
    }
    nvlist->append(XAPNameValuePair(STR_XAPTARGET, target));
}

//----------------------------------------------------------------------------

const QString & XAPHeader::getUid() const{
    for(int i = 0; i < count(); i++) {
        if(at(i).getName() == (STR_XAPUID))
            return at(i).getValue();
    }
    return "";
}

//----------------------------------------------------------------------------

void XAPHeader::setUid(const QString &uid) {
    for(int i = 0; i < count(); i++) {
        if(at(i).getName() == STR_XAPUID) {
            nvlist->takeAt(i);
            break;
        }
    }
    nvlist->append(XAPNameValuePair(STR_XAPUID, uid));
}

//----------------------------------------------------------------------------

const QString & XAPHeader::getVersion() const{
    for(int i = 0; i < count(); i++) {
        if(at(i).getName() == STR_XAPVERSION)
            return at(i).getValue();
    }
    return "";
}

//----------------------------------------------------------------------------

void XAPHeader::setVersion(const QString &version) {
    for(int i = 0; i < count(); i++) {
        if(at(i).getName() == STR_XAPVERSION) {
            nvlist->takeAt(i);
            break;
        }
    }
    nvlist->append(XAPNameValuePair(STR_XAPVERSION, version));
}

//----------------------------------------------------------------------------

XAPHeader& XAPHeader::operator =(const XAPHeader& other) {
    this->setClass(other.getClass());
    this->setVersion(other.getVersion());
    this->setHop(other.getHop());
    this->setSource(other.getSource());
    this->setTarget(other.getTarget());
    this->setUid(other.getUid());
    return *this;
}

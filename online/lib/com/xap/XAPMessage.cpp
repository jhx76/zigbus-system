
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

#include "XAPMessage.h"
#include "XAPNameValuePair.h"

//---------------------------------------------------------

XAPAddress::XAPAddress() {
    this->vendor = "";
    this->type = "";
    this->location = "";
    this->instance = "";
   // qDebug() << "Builde XAPAddress: getVendor() = " << getVendor();
}

//---------------------------------------------------------

XAPAddress::XAPAddress(const QString &vendor, const QString &type, const QString &location, const QString &instance) {
    this->vendor = vendor;
    this->type = type;
    this->location = location;
    this->instance = instance;
}

//---------------------------------------------------------

XAPAddress::XAPAddress(const XAPAddress& other) {
    this->vendor = other.vendor;
    this->type = other.type;
    this->location = other.location;
    this->instance = other.instance;
}

//---------------------------------------------------------

XAPAddress& XAPAddress::operator=(const XAPAddress& other) {

    this->vendor = other.vendor;
    this->type = other.type;
    this->location = other.location;
    this->instance = other.instance;
    return *this;
}

//---------------------------------------------------------

XAPAddress XAPAddress::fromString(const QString &src) {
    QString vendor = utils::getSousChaine(src, ".", 0);
    QString type = utils::getSousChaine(src, ".", 1);
    QString location = utils::getSousChaine(src, ".", 2).trimmed();
    if(location.contains(":"))
        location = utils::getSousChaine(location, ":", 0);
    QString instance = "";
    if(src.contains(":"))
        instance = utils::getSousChaine(src, ":", 1).trimmed();
    return XAPAddress(vendor, type, location, instance);
}

//---------------------------------------------------------

bool operator==(const XAPAddress& a, const XAPAddress& b) {
    return a.isEqual(b);
}

//---------------------------------------------------------

XAPMessage::XAPMessage() {

    this->blockList = new QList<XAPBlock>;
    header = new XAPHeader();
    this->header->setHop(1);
    this->header->setVersion("12");
    this->header->setUid("FF123400");
}

//---------------------------------------------------------

XAPMessage::XAPMessage(const QString & xapclass
                       , const QString & source
                       , const QString & target
                       , const QString & uid
                       , int hop
                       , const QString & version)
{
    blockList = new QList<XAPBlock>;
    header = new XAPHeader();
    header->setClass(xapclass);
    header->setSource(source);
    header->setTarget(target);
    header->setUid(uid);
    header->setHop(hop);
    header->setVersion(version);
}

//---------------------------------------------------------

XAPMessage::XAPMessage(const XAPMessage & other){
    header = new XAPHeader(*(other.header));
    this->blockList = new QList<XAPBlock>;
    for(int i = 0; i < other.blockList->count(); i++) {
        XAPBlock b = other.blockList->at(i);
        this->blockList->append(b);
    }
}

//---------------------------------------------------------

XAPMessage XAPMessage::fromString(const QString &str)
{

    XAPMessage rsltMessage;
    QString buff = str.trimmed();
    if(!buff.isEmpty()
            && buff.contains("\n")
            && (utils::getSousChaine(buff, "\n", 0) == "xap-header" || utils::getSousChaine(buff, "\n", 0) == "xap-hbeat")
            && utils::getSousChaine(buff, "\n", 1) == "{"
            && buff.contains("}"))
    {

        QString tmp;
        int i;

        /* Construction du xap-header */
        for(i = 0; tmp != STR_BRACE_RIGHT && i < MAX_XAPHEADER_LINE; i++)
        {
            tmp = utils::getSousChaine(buff, STR_LF, i);
            if(tmp.contains(STR_BRACE_RIGHT)) break;
            if(tmp.contains(STR_LF)) tmp = tmp.left(tmp.indexOf(STR_LF));
            if(tmp == "xap-hbeat") rsltMessage.getHeader().setBlockname("xap-hbeat");
            XAPNameValuePair nvpair;
            if(utils::getSousChaine(str,STR_LF, i).contains(STR_EQUALS)) {
                nvpair = XAPNameValuePair::fromString(utils::getSousChaine(buff, STR_LF, i));
            }
            if( nvpair.getName() == STR_XAPVERSION)
                rsltMessage.setVersion(nvpair.getValue());
            else if(nvpair.getName() == STR_XAPHOP) {
                bool ok;
                rsltMessage.setHopCount(nvpair.getValue().toInt(&ok));
                if(!ok)
                    throw XAPMessageException(str, "bad hop count value", AT);
            }
            else if(nvpair.getName() == STR_XAPUID)
                rsltMessage.setUid(nvpair.getValue());
            else if(nvpair.getName() == STR_XAPCLASS)
                rsltMessage.setClass(nvpair.getValue());
            else if(nvpair.getName() == STR_XAPSOURCE)
                rsltMessage.setSource(nvpair.getValue());
            else if(nvpair.getName() == STR_XAPTARGET)
                rsltMessage.setTarget(nvpair.getValue());
            else {
                if(rsltMessage.getClass() == "xap-hbeat.alive" && nvpair.getName() == "interval")
                    rsltMessage.getHeader().append("interval", nvpair.getValue());
                else if(rsltMessage.getClass() == "xap-hbeat.alive" && nvpair.getName() == "port")
                    rsltMessage.getHeader().append("port", nvpair.getValue());
            }
        }

        if( i <= MAX_XAPHEADER_LINE )  {
            int blockcount = buff.count(STR_BRACE_RIGHT) - 1;
            for(int j = 0; j < blockcount; j++)
            {
                XAPBlock tmpblock = XAPBlock(utils::getSousChaine(buff, STR_LF, ++i));
                while(utils::getSousChaine(buff, STR_LF, ++i) != STR_BRACE_RIGHT)
                {
                    if(utils::getSousChaine(buff, STR_LF, i) == STR_BRACE_LEFT) continue;
                    XAPNameValuePair nvpair = XAPNameValuePair::fromString(utils::getSousChaine(buff, STR_LF, i));
                    if(!nvpair.getName().isEmpty() && !nvpair.getValue().isEmpty()) tmpblock.append(nvpair);
                }
                rsltMessage.append(tmpblock);
            }
        }
    }
    else
        throw XAPMessageException(str, "Cannot build the XAPMessage", AT);
    return rsltMessage;
}

//---------------------------------------------------------

XAPMessage::~XAPMessage(){
    this->clear();
    delete blockList;
    delete header;
}

//---------------------------------------------------------

bool XAPMessage::contains(const QString & blockname) const {
    for(int i=0; i < blockList->count(); i++)
        if(blockList->at(i).getBlockname() == blockname)
            return true;
    return false;
}

//---------------------------------------------------------

bool XAPMessage::isEmpty() const {
    return blockList->isEmpty();
}

//---------------------------------------------------------

void XAPMessage::append(const XAPBlock & block) const {
    blockList->append(block);
}

//---------------------------------------------------------

int XAPMessage::count() const {
    return blockList->count();
}

//---------------------------------------------------------

const XAPBlock & XAPMessage::at(int i) const {
    return blockList->at(i);
}

//---------------------------------------------------------

XAPBlock& XAPMessage::elementAt(int i) {
    //return blockList[i];
    return this->blockList->operator [](i);
}

//---------------------------------------------------------

void XAPMessage::removeAt(int i) const {
    blockList->removeAt(i);
}

//---------------------------------------------------------

QString XAPMessage::toString() const {
    QString rslt = "";
    rslt += header->toString();
    for(int i = 0; i < blockList->count(); i++)
        rslt += this->blockList->at(i).toString();
    return rslt;
}

//---------------------------------------------------------

void XAPMessage::clear() {
    //delete header;
    while(!blockList->isEmpty())
        blockList->takeFirst();
}

//---------------------------------------------------------

XAPAddress XAPMessage::getXAPSource() const {
    XAPAddress xapsource;
    xapsource.setVendor(utils::getSousChaine(getSource(), ".", 0));
    if(xapsource.getVendor().isEmpty())
        throw error::SysException("error: empty vendor in xap source address", AT);
    xapsource.setType(utils::getSousChaine(getSource(), ".", 1));
    if(xapsource.getType().isEmpty())
        throw error::SysException("error: empty type in xap source address", AT);
    xapsource.setLocation(utils::getSousChaine(getSource(), ".", 2));
    if(xapsource.getLocation().isEmpty())
        throw error::SysException("error: empty location in xap source address", AT);
    if(xapsource.getLocation().contains(":"))
        xapsource.setLocation(utils::getSousChaine(xapsource.getLocation(), ":", 0));
    xapsource.setInstance(utils::getSousChaine(getSource(), ":", 1, false));
    return xapsource;
}

//---------------------------------------------------------

XAPAddress XAPMessage::getXAPTarget() const {
    XAPAddress xaptarget;
    xaptarget.setVendor(utils::getSousChaine(getTarget(), ".", 0));
    if(xaptarget.getVendor().isEmpty())
        throw error::SysException("error: empty vendor in xap target address", AT);
    xaptarget.setType(utils::getSousChaine(getTarget(), ".", 1));
    if(xaptarget.getType().isEmpty())
        throw error::SysException("error: empty type in xap target address", AT);
    xaptarget.setLocation(utils::getSousChaine(getTarget(), ".", 2));
    if(xaptarget.getLocation().isEmpty())
        throw error::SysException("error: empty location in xap target address", AT);
    if(xaptarget.getLocation().contains(":"))
        xaptarget.setLocation(utils::getSousChaine(xaptarget.getLocation(), ":", 0));
    xaptarget.setInstance(utils::getSousChaine(getTarget(), ":", 1));
    return xaptarget;
}

//---------------------------------------------------------

QString XAPMessage::valueOf(const QString &blockName, const QString &nvname) {
    if(blockName == "xap-header" || blockName == "xap-hbeat") {
        for(int i = 0; i < header->count(); i++) {
            if(header->at(i).getName() == nvname)
                return header->at(i).getValue();
        }
    }
    else {
        for(int iblock = 0; iblock < count(); iblock++) {
            if(at(iblock).getBlockname() == blockName) {
                for(int ipair = 0; ipair < at(iblock).count(); ipair++) {
                    if(at(iblock).at(ipair).getName() == nvname)
                        return at(iblock).at(ipair).getValue();
                }
            }
        }
    }
    return "";
}

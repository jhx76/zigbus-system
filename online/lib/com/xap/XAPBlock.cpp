
#include "XAPBlock.h"
#include "XAPNameValuePair.h"

XAPBlock::XAPBlock(){
   nvlist = new QList<XAPNameValuePair>;
}

//----------------------------------------------------------------------------

XAPBlock::XAPBlock(const QString & blockname){
    this->blockname = blockname;
    nvlist = new QList<XAPNameValuePair>;
}

//----------------------------------------------------------------------------

XAPBlock::XAPBlock(const XAPBlock & other){
    this->blockname = other.blockname;
    nvlist = new QList<XAPNameValuePair>;
    for(int i = 0; i < other.count(); i++)
        this->append(XAPNameValuePair(other.at(i).getName(), other.at(i).getValue()));
}

//----------------------------------------------------------------------------

XAPBlock::~XAPBlock(){
   /* for(int i = 0; i < nvlist->count(); i++)
        nvlist->removeAt(i);*/
    while(!nvlist->isEmpty())
        nvlist->takeFirst();
    delete nvlist;
}

//----------------------------------------------------------------------------

int XAPBlock::count() const {
    return nvlist->count();
}

//----------------------------------------------------------------------------

bool XAPBlock::isEmpty() const {
    return nvlist->isEmpty();
}

//----------------------------------------------------------------------------

void XAPBlock::clear() {
    nvlist->clear();
}

//----------------------------------------------------------------------------

bool XAPBlock::contains(const QString & nvname) const  {
    for(int i = 0; i < nvlist->count(); i++)
        if(nvlist->at(i).getName() == nvname)
            return true;

    return false;
}

//----------------------------------------------------------------------------

const XAPNameValuePair & XAPBlock::at(int i) const {
    return nvlist->at(i);
}

//----------------------------------------------------------------------------

void XAPBlock::removeAt(int i) {
//    nvlist->removeAt(i);
    nvlist->takeAt(i);
}

//----------------------------------------------------------------------------

void XAPBlock::append(const XAPNameValuePair & nvpair) {
    nvlist->append(nvpair);
}

//----------------------------------------------------------------------------

void XAPBlock::append(const QString & nvname, const QString & nvvalue) {
    append(XAPNameValuePair(nvname, nvvalue));
}

//----------------------------------------------------------------------------

QString XAPBlock::toString() const {
    QString str = "";
    if(blockname.isEmpty()) return "";
    str += blockname;
    str += "\n";
    str += "{\n";
    for(int i = 0; i < nvlist->count(); i++)
        if(!nvlist->at(i).getValue().isEmpty()) str += nvlist->at(i).toString();
    str += "}\n";
    return str;
}

//----------------------------------------------------------------------------

XAPNameValuePair& XAPBlock::elementAt(int i) {
    return nvlist->operator [](i);
}

#include "SysUtils.h"


namespace utils {

QString getSousChaine(const QString& base, const QString& separator, int position, bool returnbase) {
    QString tmp = "";
    QString rslt = "";
    int cursor1 = -1, cursor2 = -1;
    if(!base.contains(separator)) {
        if(returnbase)
            return base;
        return rslt;
    }
    if(base.count(separator) < position)  {
        if(returnbase)
            return base;
        return rslt;
    }

    int i = 0;
    while(i <= position)
    {
        cursor1 = cursor2 + 1;
        cursor2 = base.indexOf(separator, cursor1 + 1);
        i++;
    }
    if(cursor2 == -1)
        tmp = base.right(base.count() - cursor1);
    else
        tmp = base.mid(cursor1, cursor2 - cursor1);
    return tmp;
}




}




//----------------------------------------------------------------------------



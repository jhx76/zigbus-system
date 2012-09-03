#include "XAPUtils.h"

QString XAPUtils::getLine(QString _str, int line)
{
    QString rslt = "";
    if(line > 0 && !_str.isEmpty() && line <= _str.count(STR_LF))
    {
        QString tmp = "";
        for(int i = 0, cursor1 = 0, cursor2 = 0; i < line || cursor2 == -1; i++)
        {
            tmp = _str.left(tmp.indexOf(STR_LF, cursor2));
            tmp = tmp.mid(cursor1, cursor2 - cursor1);
            cursor1 = cursor2 + 1;
            cursor2 = _str.indexOf(STR_LF, cursor1);
        }
        rslt = tmp;
    }
    return rslt;
}

//----------------------------------------------------------------------------

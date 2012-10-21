#ifndef SINGLEDAT_H
#define SINGLEDAT_H

#include <QString>
#include <QList>
#include <QDebug>

#include <core/Module.h>
#include <core/Device.h>
#include <core/QueryBean.h>
#include <core/Error.h>

#include <com/common/GenAddress.h>
#include <com/zbp/ZbpAddress.h>

class SingleDAT
{
private:
    QList<Module> moduleList;
    QueryBean* queryBean;

public:
    SingleDAT();

    SingleDAT(QueryBean* bean);

    ~SingleDAT();

    void initialize();

    inline const QList<Module>& getModuleList() const { return moduleList; }

    inline void setModuleList(const QList<Module>& moduleList) { this->moduleList = moduleList; }

    GenAddress find(const ZbpAddress& src);

    ZbpAddress find(const GenAddress& src, const QString& mainPin = "", const QString& optionalPin = "", const QString& pinType = "");


};

#endif // SINGLEDAT_

#ifndef QUERYBEAN_H
#define QUERYBEAN_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include <Device.h>
#include <Module.h>
#include <QList>

class QueryBean
{
private:
    QSqlDatabase* database;

public:
    /**

      */
    QueryBean(QSqlDatabase* database);

    /**

      */
    QList<Module> buildModuleList(const QString& networkId);



};

#endif // QUERYBEAN_H

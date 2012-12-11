#ifndef APPLICATIONINFORMATION_H
#define APPLICATIONINFORMATION_H
#include <QString>
#include <QDate>
#include <core/SysUtils.h>


#include <QCoreApplication>

/**

*/
class ApplicationInformation
{
private:
    QDate versionDate;
    QString versionNumber;
    QString info;
    QString evolution;
    QString appName;

public:
    ApplicationInformation(const QString& applicationName, const QString& evolution);
    const QDate& getVersionDate() const { return versionDate; }
    void setVersionDate(const QDate& date) { versionDate = date; }
    const QString& getVersionNumber() const { return versionNumber; }
    void setVersionNumber(const QString& versionNumber) { this->versionNumber = versionNumber; }
    const QString& getInfo() const { return info; }
    void setInfo(const QString& info) { this->info = info; }
    const QString& getEvolution() const { return evolution; }
    void setEvolution(const QString& evolution) { this->evolution = evolution; }
    const QString& applicationName() const { return appName; }
    void setApplicationName(const QString& applicationName) { appName = applicationName; }
    const QString& applicationVersion() const { return versionNumber; }

};

//extern ApplicationInformation *zAppInfo;

#endif // APPLICATIONINFORMATION_H

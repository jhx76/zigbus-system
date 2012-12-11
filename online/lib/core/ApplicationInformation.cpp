#include "ApplicationInformation.h"

ApplicationInformation::ApplicationInformation(const QString& applicationName, const QString& _evolution) {
    this->appName = applicationName;
    evolution = _evolution;
    int count = evolution.count("\n");
    QString lastEvolution = utils::getSousChaine(evolution, STR_LF, count-1, false);
    if(!lastEvolution.isEmpty()) {
        QString strDate = utils::getSousChaine(lastEvolution, STR_PIPE, 0, false);
        this->versionDate = QDate(utils::getSousChaine(strDate, STR_SLASH, 0, false).toInt(),
                                  utils::getSousChaine(strDate, STR_SLASH, 1).toInt(),
                                  utils::getSousChaine(strDate, STR_SLASH, 2).toInt());
        this->versionNumber = utils::getSousChaine(lastEvolution, STR_PIPE, 1, false);
        this->info = utils::getSousChaine(lastEvolution, STR_PIPE, 2, false);
    }
    qApp->setApplicationName(this->applicationName());
    qApp->setApplicationVersion(this->applicationVersion());
}

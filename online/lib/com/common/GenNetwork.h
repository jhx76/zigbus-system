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

#ifndef GENNETWORK_H
#define GENNETWORK_H

#include <QObject>
#include <QThread>
#include <QString>
#include <com/common/GenMessage.h>
#include <core/Module.h>
#include <core/Device.h>
/**

  */
class GenNetwork : public QThread
{
    Q_OBJECT
private:
    /**

      */
    QString networkId;


public:
    /**

      */
    GenNetwork(const QString& id = "00", QObject* parent = 0);


    /**

      */
    virtual void run() {
        exec();
    }

    /**

      */
    virtual void initialize(const QString& str) = 0;

    /**

      */
    virtual bool startListening() = 0;

    /**

      */
    virtual bool isListening() = 0;

    /**

      */
    virtual void stopListening() = 0;

    /**

      */
    const QString& getNetworkId() const { return networkId; }

    /**

      */
    void setNetworkId(const QString& id) { networkId = id; }


public slots:
    /**

      */
    virtual void sendMessage(GenMessage* message) = 0;

signals:
    /**

      */
    void messageReceived(GenMessage* message, QString networkId);
};

#endif // GENNETWORK_H

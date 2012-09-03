#ifndef MODULE_H
#define MODULE_H

#include <QString>
#include <QList>
#include "Device.h"

/**

  @todo Module class documentation
  */
class Module
{

private:
    /**

      */
    QString label;

    /**

      */
    int analogIOCount;

    /**

      */
    int numericIOCount;

    /**

      */
    QList<Device> deviceList;

public:
    /**

      */
    Module();

    /**

      */
    Module(const QString& label, int analogicIOCount = 10, int numericIOCount = 10);

    /**

      */
    Module(const Module& other);

    /**

      */
    void append(const Device& device) {

        this->deviceList.append(device);
    }

    /**

      */
    int deviceCount() const { return deviceList.count(); }

    /**

      */
    void removeAt(int index) { deviceList.removeAt(index); }

    /**

      */
    Device& elementAt(int index) { return deviceList[index]; }

    /**

      */
    const Device& at(int index) { return deviceList.at(index); }

    /**

      */
    const QString& getLabel() const { return label; }

    /**

      */
    void setLabel(const QString& label) { this->label = label; }

    /**

      */
    int getAnalogIOCount() const { return analogIOCount; }

    /**

      */
    void setAnalogIOCount(int count) { this->analogIOCount = count; }

    /**

      */
    int getNumericIOCount() const { return numericIOCount; }

    /**

      */
    void setNumericIOCount(int count) { this->numericIOCount = count; }

    /**

      */
    QString toString() const;

};

#endif // MODULE_H

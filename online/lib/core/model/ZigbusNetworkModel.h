#ifndef ZIGBUSNETWORKMODEL_H
#define ZIGBUSNETWORKMODEL_H

#include <QString>

class ZigbusNetworkModel
{
private:
    int id;
    QString label;
    QString description;


public:
    ZigbusNetworkModel();

    ZigbusNetworkModel(const QString& label, const QString& description, int id);

    ZigbusNetworkModel(const ZigbusNetworkModel& other);

    bool isEqual(const ZigbusNetworkModel& other) const;

    ZigbusNetworkModel& operator=(const ZigbusNetworkModel& other);

    const QString& getLabel() const { return label; }

    void setLabel(const QString& label) { this->label = label; }

    const QString& getDescription() const { return description; }

    void setDescription(const QString& description) { this->description = description; }

    int getId() const { return id; }

    void setId(int id) { this->id = id; }
};

bool operator==(const ZigbusNetworkModel& a, const ZigbusNetworkModel& b);


#endif // ZIGBUSNETWORKMODEL_H

#ifndef HARDWARESUBTYPEMODEL_H
#define HARDWARESUBTYPEMODEL_H

#include <QString>

class HardwareSubTypeModel
{
private:
    int id;
    QString subtype;
    QString correspondingType;
    QString description;

public:
    HardwareSubTypeModel();
    HardwareSubTypeModel(int id, const QString& subtype, const QString& correspondingType, const QString& description);
    HardwareSubTypeModel(const HardwareSubTypeModel& other);

    int getId() const { return id; }

    void setId(int id) { this->id = id; }

    const QString& getSubtype() const { return subtype; }

    void setSubtype(const QString& type) { subtype = type; }

    const QString& getCorrespondingType() const { return correspondingType; }

    void setCorrespondingType(const QString& type) { correspondingType = type; }

    const QString& getDescription() const { return description; }

    void setDescription(const QString& description) { this->description = description; }

};

#endif // HARDWARESUBTYPEMODEL_H

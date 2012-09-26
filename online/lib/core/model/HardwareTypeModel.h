#ifndef HARDWARETYPEMODEL_H
#define HARDWARETYPEMODEL_H

#include <QString>

class HardwareTypeModel
{
private:
    int id;
    QString label;
    QString description;


public:
    HardwareTypeModel();

    HardwareTypeModel(const QString& label, const QString& description, int id);

    HardwareTypeModel(const HardwareTypeModel& other);

    bool isEqual(const HardwareTypeModel& other) const;

    HardwareTypeModel& operator=(const HardwareTypeModel& other);

    const QString& getLabel() const { return label; }

    void setLabel(const QString& label) { this->label = label; }

    const QString& getDescription() const { return description; }

    void setDescription(const QString& description) { this->description = description; }

    int getId() const { return id; }

    void setId(int id) { this->id = id; }
};

bool operator==(const HardwareTypeModel& a, const HardwareTypeModel& b);

#endif // HARDWARETYPEMODEL_H

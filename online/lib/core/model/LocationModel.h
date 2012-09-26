#ifndef LOCATIONMODEL_H
#define LOCATIONMODEL_H
#include <QString>
class LocationModel
{
private:
    int id;
    QString label;
    QString description;


public:
    LocationModel();

    LocationModel(const QString& label, const QString& description, int id);

    LocationModel(const LocationModel& other);

    bool isEqual(const LocationModel& other) const;

    LocationModel& operator=(const LocationModel& other);

    const QString& getLabel() const { return label; }

    void setLabel(const QString& label) { this->label = label; }

    const QString& getDescription() const { return description; }

    void setDescription(const QString& description) { this->description = description; }

    int getId() const { return id; }

    void setId(int id) { this->id = id; }
};

bool operator==(const LocationModel& a, const LocationModel& b);

#endif // LOCATIONMODEL_H

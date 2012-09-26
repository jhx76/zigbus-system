#ifndef SYMBOLICTYPEMODEL_H
#define SYMBOLICTYPEMODEL_H
#include <QString>

class SymbolicTypeModel
{
private:
    QString label;
    QString description;
    int id;

public:
    SymbolicTypeModel();

    SymbolicTypeModel(const QString& label, const QString& description, int id);

    SymbolicTypeModel(const SymbolicTypeModel& other);

    bool isEqual(const SymbolicTypeModel& other) const;

    SymbolicTypeModel& operator=(const SymbolicTypeModel& other);

    const QString& getLabel() const { return label; }

    void setLabel(const QString& label) { this->label = label; }

    const QString& getDescription() const { return description; }

    void setDescription(const QString& description) { this->description = description; }

    int getId() const { return id; }

    void setId(int id) { this->id = id; }

};

bool operator==(const SymbolicTypeModel& a, const SymbolicTypeModel& b);

#endif // SYMBOLICTYPEMODEL_H

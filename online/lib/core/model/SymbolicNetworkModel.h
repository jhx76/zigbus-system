#ifndef SYMBOLICNETWORKMODEL_H
#define SYMBOLICNETWORKMODEL_H

#include <QString>

class SymbolicNetworkModel
{
private:
    int id;
    QString label;
    QString description;


public:
    SymbolicNetworkModel();

    SymbolicNetworkModel(const QString& label, const QString& description, int id);

    SymbolicNetworkModel(const SymbolicNetworkModel& other);

    bool isEqual(const SymbolicNetworkModel& other) const;

    SymbolicNetworkModel& operator=(const SymbolicNetworkModel& other);

    const QString& getLabel() const { return label; }

    void setLabel(const QString& label) { this->label = label; }

    const QString& getDescription() const { return description; }

    void setDescription(const QString& description) { this->description = description; }

    int getId() const { return id; }

    void setId(int id) { this->id = id; }
};

bool operator==(const SymbolicNetworkModel& a, const SymbolicNetworkModel& b);
#endif // SYMBOLICNETWORKMODEL_H

#ifndef LOCATIONCREATIONDIALOG_H
#define LOCATIONCREATIONDIALOG_H

#include <QDialog>
#include <QList>
#include <QMessageBox>
#include <core/QueryBean.h>
#include <core/model/LocationModel.h>


namespace Ui {
    class LocationCreationDialog;
}

class LocationCreationDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::LocationCreationDialog *ui;

    QList<LocationModel> locationList;

    LocationModel newLocation;

    QueryBean* queryBean;

public:
    explicit LocationCreationDialog(QueryBean* queryBean, QWidget *parent = 0);

    ~LocationCreationDialog();

    void initialize();

public slots:
    void saveAndAccept();


};

#endif // LOCATIONCREATIONDIALOG_H

#ifndef LOCATIONMANAGEMENTDIALOG_H
#define LOCATIONMANAGEMENTDIALOG_H

#include <QDialog>
#include <QList>
#include <QMessageBox>
#include <QStringListModel>
#include <QStringList>
#include <core/Error.h>
#include <core/QueryBean.h>
#include <core/model/LocationModel.h>
#include <LocationCreationDialog.h>

namespace Ui {
    class LocationManagementDialog;
}

class LocationManagementDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::LocationManagementDialog *ui;
    QueryBean* queryBean;
    QList<LocationModel> locationList;
    QStringListModel locationModel;
    QStringList stringList;

public:
    explicit LocationManagementDialog(QueryBean* queryBean, QWidget *parent = 0);
    ~LocationManagementDialog();

public slots:
    void initialize();
    void onAddButtonClick();
    void onRemoveButtonClick();
    void onEditButtonClick();
};

#endif // LOCATIONMANAGEMENTDIALOG_H

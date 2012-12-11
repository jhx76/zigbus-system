#ifndef TYPESMANAGEMENTDIALOG_H
#define TYPESMANAGEMENTDIALOG_H

#include <QDialog>
#include <QList>
#include <QStringListModel>
#include <QStringList>
#include <QMessageBox>
#include <core/QueryBean.h>
#include <core/Error.h>
#include <core/model/SymbolicTypeModel.h>
#include <TypeCreationDialog.h>

namespace Ui {
    class TypesManagementDialog;
}

class TypesManagementDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::TypesManagementDialog *ui;
    QueryBean* queryBean;
    QList<SymbolicTypeModel> typeList;
    QStringList labelList;
    QStringListModel labelListModel;

public:
    explicit TypesManagementDialog(QueryBean* queryBean, QWidget *parent = 0);

    ~TypesManagementDialog();

public slots:
    void initialize();

    void onAddButtonClick();

    void onRemoveButtonClick();

    void onEditButtonClick();
};

#endif // TYPESMANAGEMENTDIALOG_H

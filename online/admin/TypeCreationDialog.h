#ifndef TYPECREATIONDIALOG_H
#define TYPECREATIONDIALOG_H

#include <QDialog>
#include <QList>
#include <QMessageBox>
#include <core/model/SymbolicTypeModel.h>
#include <core/QueryBean.h>
#include <core/Error.h>

namespace Ui {
    class TypeCreationDialog;
}

class TypeCreationDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::TypeCreationDialog *ui;
    QueryBean* queryBean;
    QList<SymbolicTypeModel> typeList;
    SymbolicTypeModel newType;

public:
    explicit TypeCreationDialog(const QString& windowTitle, QueryBean* queryBean, QWidget *parent = 0);

    ~TypeCreationDialog();

public slots:
    void initialize();

    void saveAndAccept();

};

#endif // TYPECREATIONDIALOG_H

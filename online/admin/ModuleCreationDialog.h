#ifndef MODULECREATIONDIALOG_H
#define MODULECREATIONDIALOG_H

#include <QDialog>
#include <QList>

#include <core/model/ZigbusNetworkModel.h>
#include <core/Module.h>
#include <core/QueryBean.h>
#include <core/Error.h>

namespace Ui {
    class ModuleCreationDialog;
}

class ModuleCreationDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::ModuleCreationDialog *ui;

    QueryBean* queryBean;

    QList<Module>* moduleList;

    QList<ZigbusNetworkModel> zigbusNetworkList;


public:
    explicit ModuleCreationDialog(QueryBean* queryBean, QList<Module>* moduleList, QWidget *parent = 0);

    ~ModuleCreationDialog();

    void initialize();



public slots:
    void saveAndAccept();



};

#endif // MODULECREATIONDIALOG_H

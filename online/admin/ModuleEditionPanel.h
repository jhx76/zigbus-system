#ifndef MODULEEDITIONPANEL_H
#define MODULEEDITIONPANEL_H

#include <QWidget>
#include <QDebug>
#include <QList>

#include <core/Module.h>
#include <core/QueryBean.h>
#include <core/Error.h>
#include <core/model/ZigbusNetworkModel.h>


namespace Ui {
    class ModuleEditionPanel;
}

class ModuleEditionPanel : public QWidget
{
    Q_OBJECT

private:
    Ui::ModuleEditionPanel *ui;

    Module* module;

    Module tmpModule;

    QueryBean* queryBean;

    QList<ZigbusNetworkModel> zigbusNetworkList;

public:
    explicit ModuleEditionPanel(QWidget *parent = 0);

    ModuleEditionPanel(Module* ptrModule, QueryBean* queryBean, QWidget* parent = 0);

    ~ModuleEditionPanel();

    void initialize();

    Module *getPtrModule() { return module; }

    void setPtrModule(Module *ptr) { module = ptr; }

public slots:
    void onSaveButtonClick();
    void onCancelButtonClick();
    void onQuitButtonClick();

signals:
    void um_panel_closed();
    void um_refresh();

};

#endif // MODULEEDITIONPANEL_H

#ifndef MODULEEDITIONPANEL_H
#define MODULEEDITIONPANEL_H

#include <QWidget>
#include <core/Module.h>

namespace Ui {
    class ModuleEditionPanel;
}

class ModuleEditionPanel : public QWidget
{
    Q_OBJECT

private:
    Ui::ModuleEditionPanel *ui;

    Module* module;

public:
    explicit ModuleEditionPanel(QWidget *parent = 0);

    ModuleEditionPanel(Module* ptrModule, QWidget* parent = 0);

    ~ModuleEditionPanel();

    Module *getPtrModule() { return module; }

    void setPtrModule(Module *ptr) { module = ptr; }
};

#endif // MODULEEDITIONPANEL_H

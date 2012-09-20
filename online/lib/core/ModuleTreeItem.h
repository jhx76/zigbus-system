#ifndef MODULETREEITEM_H
#define MODULETREEITEM_H

#include <QStandardItem>
#include <core/Module.h>
#include <core/DeviceTreeItem.h>
#include <QDebug>

class ModuleTreeItem : public QStandardItem
{
private:
    Module *module;

public:
    ModuleTreeItem();

    ModuleTreeItem(Module* module);

    ModuleTreeItem(const ModuleTreeItem& other);

    Module* getPtrModule() { return module; }

    void setPtrModule(Module* module) { this->module = module; }


};

#endif // MODULETREEITEM_H

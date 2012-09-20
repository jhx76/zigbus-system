#include "ModuleTreeItem.h"

ModuleTreeItem::ModuleTreeItem() : QStandardItem() {
    this->module = NULL;
}

ModuleTreeItem::ModuleTreeItem(Module *module) : QStandardItem("Module"+module->getLabel()) {
    this->module = module;
}

ModuleTreeItem::ModuleTreeItem(const ModuleTreeItem &other) : QStandardItem(other) {
    module = other.module;
}

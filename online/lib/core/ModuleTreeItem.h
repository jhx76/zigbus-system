/*
    This file is part of Zigbus Home Automation API. 
    Copyright (C) 2012 jhx

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

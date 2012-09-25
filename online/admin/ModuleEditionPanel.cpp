#include "ModuleEditionPanel.h"
#include "ui_ModuleEditionPanel.h"

ModuleEditionPanel::ModuleEditionPanel(QWidget *parent) : QWidget(parent), ui(new Ui::ModuleEditionPanel)
{
    ui->setupUi(this);
    module = NULL;
}


ModuleEditionPanel::ModuleEditionPanel(Module *ptrModule, QWidget *parent) : QWidget(parent), ui(new Ui::ModuleEditionPanel)
{
    ui->setupUi(this);
    module = ptrModule;

}



ModuleEditionPanel::~ModuleEditionPanel()
{
    delete ui;
    module = NULL; //On ne delete pas l'object car il ne nous appartient pas.
}

#include "branch_editor.h"
#include "ui_branch_editor.h"
#include "utmanager.h"

branch_editor::branch_editor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::branch_editor)
{
    ui->setupUi(this);

    BrancheMap brMap = sUTManager->getAllBranches();

    for(auto it = brMap.begin() ; it != brMap.end() ; it++)
    {
        ui->brancheList->addItem(it.value()->getNom());
    }
}

branch_editor::~branch_editor()
{
    delete ui;
}

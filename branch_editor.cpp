#include "branch_editor.h"
#include "ui_branch_editor.h"
#include "utmanager.h"
#include <QListWidgetItem>
#include <QMessageBox>
#include "brancheeditor_dialog.h"

branch_editor::branch_editor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::branch_editor)
{
    ui->setupUi(this);

    BrancheMap brMap = sUTManager->getAllBranches();

    for(auto it = brMap.begin() ; it != brMap.end() ; it++)
    {
        ui->brancheList->addItem(it.key());
    }
}

branch_editor::~branch_editor()
{
    delete ui;
}

void branch_editor::on_brancheList_itemDoubleClicked(QListWidgetItem *it)
{
    QString branche = it->text();

    Branche* br = sUTManager->getBranche(branche);

    if(!br)
    {
        QMessageBox::critical(this, "Branche introuvable", "La branche " + branche + " est introuvable");
        return;
    }

    BrancheEditor_dialog editor(br, this);
    editor.exec();
}

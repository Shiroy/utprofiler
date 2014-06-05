#include "brancheeditor_dialog.h"
#include "ui_brancheeditor_dialog.h"
#include "branche.h"

BrancheEditor_dialog::BrancheEditor_dialog(Branche* br, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrancheEditor_dialog), m_br(br)
{
    ui->setupUi(this);

    ui->sigle->setText(m_br->getSigle());
    ui->nom->setText(m_br->getNom());

    update_psf();
}

void BrancheEditor_dialog::update_psf()
{
    ui->psfList->clear();
    QMap<QString, Profil*> &allPSF = m_br->getPSF();
    for(auto it = allPSF.begin() ; it != allPSF.end() ; it++)
    {
        ui->psfList->addItem(it.key());
    }
}

BrancheEditor_dialog::~BrancheEditor_dialog()
{
    delete ui;
}

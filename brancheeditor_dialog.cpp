#include "brancheeditor_dialog.h"
#include "ui_brancheeditor_dialog.h"
#include "branche.h"
#include "utmanager.h"
#include "utprofilerexception.h"
#include "profile_editor.h"
#include <QListWidgetItem>

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

void BrancheEditor_dialog::on_psfList_itemDoubleClicked(QListWidgetItem *item)
{
    QString filiere = item->text();
    Profil* prfl = sUTManager->getProfile(filiere);
    if(!prfl)
        UTPROFILER_EXCEPTION("Filière introuvable");

    Profile_Editor *prflEditor = new Profile_Editor(prfl, this);
    prflEditor->exec();
    prflEditor->deleteLater();
}

void BrancheEditor_dialog::on_editPcb_clicked()
{
    Profil* prfl = m_br->getPCB();
    Profile_Editor *prflEditor = new Profile_Editor(prfl, this);
    prflEditor->exec();
    prflEditor->deleteLater();
}

BrancheEditor_dialog::~BrancheEditor_dialog()
{
    delete ui;
}

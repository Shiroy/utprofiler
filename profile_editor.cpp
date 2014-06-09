#include "profile_editor.h"
#include "ui_profile_editor.h"

#include "profil.h"

Profile_Editor::Profile_Editor(Profil* profil, QWidget *parent) :
    QDialog(parent),
    profilToEdit(profil),
    ui(new Ui::Profile_Editor)
{
    ui->setupUi(this);

    ui->titreFiliere->setText(profilToEdit->getNomProfile());

    QVBoxLayout *layout = new QVBoxLayout(ui->predicatList);
    const QVector<Predicat*> &allPredicat = profilToEdit->getAllPredicat();
    for(auto it = allPredicat.begin() ; it != allPredicat.end() ; it++)
    {
        QWidget *predicatEditor = (*it)->getEditorWidget(ui->predicatList);
        layout->addWidget(predicatEditor);
    }
}

Profile_Editor::~Profile_Editor()
{
    delete ui;
}

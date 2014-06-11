#include "profile_editor.h"
#include "ui_profile_editor.h"

#include "profil.h"
#include "utprofilerexception.h"

#include <QToolButton>
#include <QInputDialog>

Profile_Editor::Profile_Editor(Profil* profil, QWidget *parent) :
    QDialog(parent),
    profilToEdit(profil),
    ui(new Ui::Profile_Editor)
{
    mapper = new QSignalMapper(this);
    ui->setupUi(this);

    ui->titreFiliere->setText(profilToEdit->getNomProfile());

    QWidget *predicatEditorsContainer = new QWidget(this);
    ui->predicatList->setWidget(predicatEditorsContainer);

    QVBoxLayout *layout = new QVBoxLayout(predicatEditorsContainer);
    predicatEditorsContainer->setLayout(layout);

    const QVector<Predicat*> &allPredicat = profilToEdit->getAllPredicat();
    for(auto it = allPredicat.begin() ; it != allPredicat.end() ; it++)
    {
        layout->addLayout(addPredicatEditor(*it));
    }

    connect(mapper, SIGNAL(mapped(QObject*)), this, SLOT(deletePredicat(QObject*)));
    predicatEditorsContainer->show();
}

void Profile_Editor::deletePredicat(QObject *predicat)
{
    Predicat *prdct = qobject_cast<Predicat*>(predicat);

    if(!predicat)
        UTPROFILER_EXCEPTION("Suppression d'un prédicat invalide");

    profilToEdit->delPredicat(prdct);
}

void Profile_Editor::on_addPredicat_clicked()
{
    //TODO : Enlever cette duplication de code
    QStringList predicatTypeList;
    predicatTypeList << "UV obligatoire" << "Obtenir X UV parmis" << "Obtenir un minimum de credit de type" << "Obtenir un minimum de credit";

    bool ok = false;
    QString cond = QInputDialog::getItem(this, "Ajouter une condition", "Selectioner le type de condition", predicatTypeList, 0, false, &ok);

    if(!ok)
        return;

    Predicat* newPredicat = PredicatFactory(PredicatDescriptionToInt(cond));
    profilToEdit->addPredicat(newPredicat);
    qobject_cast<QBoxLayout*>(ui->predicatList->widget()->layout())->addLayout(addPredicatEditor(newPredicat));
}

QLayout* Profile_Editor::addPredicatEditor(Predicat *predicat)
{
    QWidget *predicatEditor = predicat->getEditorWidget(ui->predicatList->widget());
    QHBoxLayout *lay = new QHBoxLayout(ui->predicatList->widget());
    QToolButton *delButton = new QToolButton(ui->predicatList->widget());
    delButton->setText("X");

    mapper->setMapping(delButton, predicat);
    connect(delButton, SIGNAL(clicked()), mapper, SLOT(map()));

    //Par un jeu de signaux sloat, la destruction du predicat entraine la destruction du widget editor qui entraine la destruction du layout et du delButton
    connect(predicatEditor, SIGNAL(destroyed()), lay, SLOT(deleteLater()));
    connect(predicatEditor, SIGNAL(destroyed()), delButton, SLOT(deleteLater()));

    lay->addWidget(predicatEditor);
    lay->addWidget(delButton);
    return lay;
}

Profile_Editor::~Profile_Editor()
{
    delete ui;
}

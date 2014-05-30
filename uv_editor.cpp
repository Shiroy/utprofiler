#include "uv_editor.h"
#include "utmanager.h"
#include "ui_uv_editor.h"
#include <QMessageBox>
#include <QCheckBox>


UV_Editor::UV_Editor(UV* ptUV, QWidget *parent) :
    ptUVEditee(ptUV),
    QDialog(parent),
    ui(new Ui::UV_Editor)
{
    ui->setupUi(this);

    this->setWindowTitle(ptUV->getCode());
    ui->uvCode->setText(ptUVEditee->getCode());

    for (unsigned int i=1; i<NB_CATEGORIE; i++)
    {
        ui->comboCategorie->addItem(UTManager::categorieUVEnumToText(static_cast<CategorieUV>(i)), QVariant(i));
    }

    BrancheMap& toutesLesBranches=sUTManager->getAllBranches();
    for(auto i=toutesLesBranches.begin(); i!=toutesLesBranches.end(); i++)
    {

        QCheckBox* caseBranche = new QCheckBox(i.value()->getNom(), this);
        ui->casesBranche->addWidget(caseBranche);
    }
}



UV_Editor::~UV_Editor()
{
    delete ui;
}

void UV_Editor::on_buttonBox_accepted()

{


    /* Le test concernant les valeurs entrées par l'utilisateur
      necessite d'etre enrichi

      */
    if(ui->lineTitre->text().isEmpty())
    {
        QMessageBox::critical (this, ptUVEditee->getCode(), "Veuillez saisir les informations necessaires a la creation de l'UV "+ptUVEditee->getCode());
    }

    else
    {
        //ptUVEditee->setCode(ui);

        ptUVEditee->setTitre(ui->lineTitre->text());

        // Verifier par la suite si la conversion implicite de QString en int se passe correctement :
        ptUVEditee->setNombreCredit(ui->spinCredits->value());

        /* Necessite que l'indexation du type enumere Categorie corresponde exactement
          a celui du comboBox comboCategorie :
          */
        ptUVEditee->setCategorie(static_cast<CategorieUV>(ui->comboCategorie->currentIndex()));

        // Meme remarque ici :
        //ptUVEditee->setBrancheStr(ui->comboBranche->currentText());

        this->hide();



    }

}

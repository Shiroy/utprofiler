#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utmanager.h"
#include <QFileDialog>
#include <QMessageBox>
#include "utstreamxml.h"
#include "etudiantstreamxml.h"
#include "utprofilerexception.h"
#include "uv_editor.h"
#include "branch_editor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_searchModel = new UVSearchModel(this);
    ui->uvPanel->setModel(m_searchModel);
}

MainWindow::~MainWindow()
{
    delete ui;
    UTManager::destroy();
}

void MainWindow::on_quickSearch_textChanged(const QString &txt)
{
    if(txt.isEmpty())
        return;

    m_searchModel->clearAllUV();
    UVMap& allUvs = sUTManager->getAllUVs();

    for(auto it = allUvs.begin() ; it != allUvs.end() ; it++)
    {
        if(it.key().contains(txt, Qt::CaseInsensitive))
            m_searchModel->addUv(*(it.value()));
    }
}

void MainWindow::on_ac_data_loadFromXML_triggered()
{
    UTStreamXML *xmlStream = new UTStreamXML;
    try
    {
        sUTManager->charger(xmlStream);
    }
    catch(const UTProfilerException &e)
    {
        QMessageBox::critical(this, "Erreur au chargement des données", e.what());
    }
}

void MainWindow::on_ac_data_saveToXML_triggered()
{
    UTStreamXML *xmlStream = new UTStreamXML();

    try
    {
        sUTManager->sauver(xmlStream);
    }
    catch(const UTProfilerException &e)
    {
        QMessageBox::critical(this, "Erreur à la sauvegarde des données", e.what());
    }
}

void MainWindow::on_ac_etu_loadFromXML_triggered()
{
    //TODO Reinitialiser la classe Etudiant
    QString filename = QFileDialog::getOpenFileName(this, "Fichier de donnée", QString(), "Fixhier XML *.xml");
    if(filename.isEmpty())
        return;

    EtudiantStreamXML stream(filename, m_etu);

    try
    {
        stream.load();
    }
    catch(const UTProfilerException &e)
    {
        QMessageBox::critical(this, "Erreur au chargement des données", e.what());
    }


}

void MainWindow::on_createUv_clicked()
{
    bool ok = false;
    QString code = QInputDialog::getText(this, "Saisie du code", "Quel est le code de l'UV a creer ?", QLineEdit::Normal, "code", &ok);

    if (ok && !code.isEmpty())
    {
        // Recuperation d'un pointeur d'UV donne par le singleton UTManager :
        UV* ptUV = sUTManager->nouvelleUV(code);
        ptUV->setCode(code);
        ptUV->setCategorie(CS); //Par défaut

        // On peut alors envoyer ce pointeur au constructeur de UV_Editor :

        UV_Editor* fenetre = new UV_Editor(ptUV, this);
        fenetre->exec();

        on_quickSearch_textChanged(ui->quickSearch->text());

    }
    else
    {
        QMessageBox::critical (this,"Saisie du Code", "Veuillez saisir une chaine de caracteres correspondant au code de l'UV.");
    }
}

void MainWindow::on_uvPanel_doubleClicked(const QModelIndex &i)
{
    UV* uvToEdit = m_searchModel->getUVAtRow(i.row());
    if(uvToEdit)
    {
        if(ui->uvEditable->isChecked())
        {
            UV_Editor *diaEdition = new UV_Editor(uvToEdit, this);
            diaEdition->exec();
        }

        on_quickSearch_textChanged(ui->quickSearch->text());
    }
    else
    {
        QMessageBox::information(this, "Erreur d'édition", "L'UV selectionnée n'existe pas");
    }
}

void MainWindow::on_ac_editBranches_triggered()
{
    branch_editor editor(this);
    editor.exec();
}

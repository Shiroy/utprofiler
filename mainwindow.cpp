#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utmanager.h"
#include <QFileDialog>
#include <QMessageBox>
#include "utstreamxml.h"
#include "utprofilerexception.h"

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
    QString filename = QFileDialog::getOpenFileName(this, "Fichier de donnée", QString(), "Fixhier XML *.xml");

    if(filename.isEmpty())
        return;

    UTStreamXML *xmlStream = new UTStreamXML(filename);
    sUTManager->setUTStream(xmlStream);
    try
    {
        sUTManager->charger();
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
        UV* ptUV = UTManager::getInstance()->nouvelleUV(code);
        UV




    }
    else
    {
        QMessageBox::critical (this,"Saisie du Code", "Veuillez saisir une chaine de caracteres correspondant au code de l'UV.");
    }
}

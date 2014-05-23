#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utmanager.h"

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
}

void MainWindow::on_quickSearch_textChanged(const QString &txt)
{
    UVMap& allUvs = sUTManager->getAllUVs();

    for(auto it = allUvs.begin() ; it != allUvs.end() ; it++)
    {
        if(it.key().contains(txt, Qt::CaseInsensitive))
            m_searchModel->addUv(*(it.value()));
    }
}

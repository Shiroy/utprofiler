#include "mainwindow.h"
#include "utmanager.h"
#include "utstreamxml.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    try
    {
        QString file = QFileDialog::getOpenFileName(0, QString(), "donne_test.xml", QString());
        UTStreamXML *stream = new UTStreamXML(file);
        sUTManager->setUTStream(stream);
        if(!sUTManager->charger())
        {
            QMessageBox::critical(0, "Erreur au chargement des UVs", stream->getError());
        }

        UV* lo21 = sUTManager->getUV("LO21");

        if(lo21)
        {
            QMessageBox::critical(0, "Erreur au chargement des UVs", "LO21 n'existe pas");
        }


    }
    catch(const std::exception &e)
    {
        std::cout << e.what();
    }

    UTManager::destroy();
    return a.exec();
}

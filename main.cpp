#include "mainwindow.h"
#include "utmanager.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*MainWindow w;
    w.show();*/

    try
    {
        if(!UTManager::getInstance()->getUV("LO21"))
            std::cerr << "UV LO21 introuvable\n";
    }
    catch(const std::exception &e)
    {
        std::cout << e.what();
    }
}

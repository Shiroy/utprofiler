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
        UTManager::getInstance()->getUV("LO21");
    }
    catch(const std::exception &e)
    {
        std::cout << e.what();
    }
}

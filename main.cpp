#include "mainwindow.h"
#include "utmanager.h"
#include "utstreamxml.h"
#include "utprofilerexception.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try
    {
        MainWindow w;
        w.show();
        return a.exec();
    }
    catch(const std::exception &e)
    {
        std::cout << e.what();
    }

    return 1;
}

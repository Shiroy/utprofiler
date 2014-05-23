#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "autocompletion.h"
#include "uvsearchmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_quickSearch_textChanged(const QString& txt);

private:
    Ui::MainWindow *ui;
    StrategieAutocompletion* Completion;

    UVSearchModel *m_searchModel; //Utiliser pou l'affichage des résultat de recherche
};

#endif // MAINWINDOW_H

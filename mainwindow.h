#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QString>
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

    void on_ac_data_loadFromXML_triggered();
    void on_ac_etu_loadFromXML_triggered();
    void on_createUv_clicked();

private:
    Etudiant m_etu;
    Ui::MainWindow *ui;
    StrategieAutocompletion* Completion;

    UVSearchModel *m_searchModel; //Utiliser pou l'affichage des résultat de recherche
};

#endif // MAINWINDOW_H

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

///Cette classe fournit l'interface de la fenêtre principale
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    ///Ce slot permet de mettre à jour la liste des UVs quand on rentre une recherche dans la barre de recherche en bas de la fenêtre
    void on_quickSearch_textChanged(const QString& txt);

    ///Ce slot déclenche de le chargement des UVs, branches, profils, au format XML
    void on_ac_data_loadFromXML_triggered();
    ///Ce slot déclenche le chargement d'un étudiant au format XML
    void on_ac_etu_loadFromXML_triggered();
    ///Ce slot déclenche la sauvegarde des UVs, branches et profils au format XML
    void on_ac_data_saveToXML_triggered();
    ///Ce slot déclenche la procédure de création d'une UV
    /// Fonctionne uniquement si le mode édition est activé
    void on_createUv_clicked();
    ///Ce slot déclenche la procédure d'édition d'une UV.
    /// Fonctionne uniquement si le mode édition est activé
    void on_uvPanel_doubleClicked(const QModelIndex& i);

    ///Ce slot ouvre la boîte de dialogue d'édition des branches
    void on_ac_editBranches_triggered();

private:
    Etudiant m_etu;
    Ui::MainWindow *ui;
    StrategieAutocompletion* Completion;

    UVSearchModel *m_searchModel; //Utilisé pour l'affichage des résultats de recherche
};

#endif // MAINWINDOW_H

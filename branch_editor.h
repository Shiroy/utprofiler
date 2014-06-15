#ifndef BRANCH_EDITOR_H
#define BRANCH_EDITOR_H

#include <QDialog>
class QListWidgetItem;

namespace Ui {
class branch_editor;
}

///Cette classe fournis l'interface permettant d'éditer l'ensemble des branches de l'application.
/// Elle permet également de les créer et des les supprimer
class branch_editor : public QDialog
{
    Q_OBJECT

public:
    ///Construit la boite de dialogue à l'aide de l'UTManager. La fonction récupère la liste des branches et les affiches dans une liste selectionnable
    explicit branch_editor(QWidget *parent = 0);
    ~branch_editor();

public slots:
    ///Appelé quand une branche est double-cliquée
    /// Ouvre la boite de dialogue d'édition de branche
    void on_brancheList_itemDoubleClicked(QListWidgetItem* it);
    ///Appelé quand le bouton "Créer une une branche" est cliqué
    ///Déclenche la procédure de création d'une branche
    void on_addBranch_clicked();

private:
    Ui::branch_editor *ui;
};

#endif // BRANCH_EDITOR_H

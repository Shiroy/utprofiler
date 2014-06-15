#ifndef BRANCHEEDITOR_DIALOG_H
#define BRANCHEEDITOR_DIALOG_H

#include <QDialog>

class Branche;
class QListWidgetItem;

namespace Ui {
class BrancheEditor_dialog;
}

class BrancheEditor_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit BrancheEditor_dialog(Branche *br, QWidget *parent = 0);
    ~BrancheEditor_dialog();

public slots:
    ///Appelée quand une filière a été double-cliquée. Cette méthode ouvre la fenêtre d'édition des profils
    void on_psfList_itemDoubleClicked(QListWidgetItem * item);
    ///Appelée quand on le bouton "Editer le PCB" est cliqué. Cette méthode ouvre la boîte d'édition des profils pour éditer le PCB.
    void on_editPcb_clicked();
    ///Cette méthode déclenche la procédure de création d'un profil
    void on_addPsf_clicked();

private:
    ///Cette méthode met à jour la liste des filières
    void update_psf();
    Ui::BrancheEditor_dialog *ui;

    ///Pointeur vers la branche à éditer
    Branche *m_br;
};

#endif // BRANCHEEDITOR_DIALOG_H

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
    void on_psfList_itemDoubleClicked(QListWidgetItem * item);
    void on_editPcb_clicked();
    void on_addPsf_clicked();

private:
    void update_psf();
    Ui::BrancheEditor_dialog *ui;

    Branche *m_br;
};

#endif // BRANCHEEDITOR_DIALOG_H

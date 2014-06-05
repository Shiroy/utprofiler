#ifndef BRANCHEEDITOR_DIALOG_H
#define BRANCHEEDITOR_DIALOG_H

#include <QDialog>

class Branche;

namespace Ui {
class BrancheEditor_dialog;
}

class BrancheEditor_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit BrancheEditor_dialog(Branche *br, QWidget *parent = 0);
    ~BrancheEditor_dialog();

private:
    void update_psf();
    Ui::BrancheEditor_dialog *ui;

    Branche *m_br;
};

#endif // BRANCHEEDITOR_DIALOG_H

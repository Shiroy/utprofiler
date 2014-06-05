#ifndef BRANCH_EDITOR_H
#define BRANCH_EDITOR_H

#include <QDialog>

namespace Ui {
class branch_editor;
}

class branch_editor : public QDialog
{
    Q_OBJECT

public:
    explicit branch_editor(QWidget *parent = 0);
    ~branch_editor();

private:
    Ui::branch_editor *ui;
};

#endif // BRANCH_EDITOR_H

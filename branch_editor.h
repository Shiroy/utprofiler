#ifndef BRANCH_EDITOR_H
#define BRANCH_EDITOR_H

#include <QDialog>
class QListWidgetItem;

namespace Ui {
class branch_editor;
}

class branch_editor : public QDialog
{
    Q_OBJECT

public:
    explicit branch_editor(QWidget *parent = 0);
    ~branch_editor();

public slots:
    void on_brancheList_itemDoubleClicked(QListWidgetItem* it);
    void on_addBranch_clicked();

private:
    Ui::branch_editor *ui;
};

#endif // BRANCH_EDITOR_H

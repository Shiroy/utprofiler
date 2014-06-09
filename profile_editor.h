#ifndef PROFILE_EDITOR_H
#define PROFILE_EDITOR_H

#include <QDialog>

namespace Ui {
class Profile_Editor;
}

class Profil;

class Profile_Editor : public QDialog
{
    Q_OBJECT

public:
    explicit Profile_Editor(Profil *profil, QWidget *parent = 0);
    ~Profile_Editor();

private:
    Ui::Profile_Editor *ui;
    Profil* profilToEdit;
};

#endif // PROFILE_EDITOR_H

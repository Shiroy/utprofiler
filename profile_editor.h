#ifndef PROFILE_EDITOR_H
#define PROFILE_EDITOR_H

#include <QDialog>
#include <QSignalMapper>

namespace Ui {
class Profile_Editor;
}

class Profil;
class Predicat;

class Profile_Editor : public QDialog
{
    Q_OBJECT

public:
    explicit Profile_Editor(Profil *profil, QWidget *parent = 0);
    ~Profile_Editor();

private slots:
    void deletePredicat(QObject *predicat);
    void on_addPredicat_clicked();

private:
    QLayout *addPredicatEditor(Predicat *predicat);
    Ui::Profile_Editor *ui;
    Profil* profilToEdit;

    QSignalMapper *mapper;
};

#endif // PROFILE_EDITOR_H

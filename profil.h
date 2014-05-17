#ifndef PROFIL_H
#define PROFIL_H

#include <QVector>
#include "uv.h"
#include <QString>

/**
 * @brief Classe représentant une condition de validation pour un profil (strategie)
 */
class Predicat
{
public:
    ///À partir de la liste des UV valiéee, détermine si la condition géré par ce prédicat est satisfaite ou non
    virtual bool predicatSatifait(QVector<UV> uvValidee) = 0;
};

class Profil
{
    QString nomProfile;
    QVector<Predicat> conditions;
public:
    Profil();

    ///Renvoie le nom du profil
    const QString& getNomProfile() const { return nomProfile; }
    ///Vérifie si toutes les conditions du profil sont satisfaites ou non
    /// @return Renvoie false si une des conditions n'est pas satisfaite.
    bool profileValide(QVector<UV> uvValidee);
};

#endif // PROFIL_H

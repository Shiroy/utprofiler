#ifndef ETUDIANT_H
#define ETUDIANT_H

#include <QString>
#include "cursus.h"

class Etudiant
{
    QString nom, prenom;

    Cursus cursus;
public:
    Etudiant();

    ///Renvoie le Cursus de l'étudiant
    const Cursus& getCursus() const { return cursus; }
    ///Renvoie le Cursus de l'étudiant
    Cursus& getCursus() { return cursus; }

    void setNom(const QString& n_nom) { nom = n_nom; }
    void setPrenom(const QString& n_prenom) { prenom = n_prenom; }

    const QString& getNom() const { return nom; }
    const QString& getPrenom() const { return prenom; }
};

#endif // ETUDIANT_H

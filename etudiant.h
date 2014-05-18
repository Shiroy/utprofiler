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

    const Cursus& getCursus() const { return cursus; }
    Cursus& getCursus() { return cursus; }
};

#endif // ETUDIANT_H

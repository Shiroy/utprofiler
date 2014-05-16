#ifndef CURSUS_H
#define CURSUS_H

#include <QVector>
#include "semestrecours.h"

class Cursus
{
    QVector<SemestreCours> semestreAValider;
    QVector<Branche> brancheAValider;

public:
    Cursus();

    /**
      *@brief Renvoie tous les smestres que l'étudiant doit valider
      */
    QVector<SemestreCours>& getTousLesSemestres() { return semestreAValider; }
    /**
      *@brief Ajoute un semestre d'étude au cursus
      */
    void ajouterSemestre(const SemestreCours& sme);

    /**
      *@brief Renvoie toutes les branches auxquelles l'étudiant est inscrit
      */
    QVector<Branche> &getAllBranche() { return brancheAValider; }
    /**
      *@brief Ajoute une branche au cursus de l'étudiant
      */
    void ajouterBranche(const Branche& brch);
};

#endif // CURSUS_H

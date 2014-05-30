#ifndef CURSUS_H
#define CURSUS_H

#include <QVector>
#include "semestrecours.h"
#include "branche.h"

class Cursus
{
    QVector<SemestreCours*> tousLesSemestres;
    QString brancheAValider;
    QStringList filieres;

public:
    Cursus();

    /**
      *@brief Renvoie tous les smestres que l'étudiant doit valider
      */
    QVector<SemestreCours*>& getTousLesSemestres() { return tousLesSemestres; }
    /**
      *@brief Ajoute un semestre d'étude au cursus
      */
    void ajouterSemestre(SemestreCours* sme) { tousLesSemestres.push_back(sme); }

    void ajouterFiliere(const QString& filiere);
    QStringList& getFiliere() { return filieres; }
    const QStringList& getFiliere() const { return filieres; }

    /**
      *@brief Renvoie toutes les branches auxquelles l'étudiant est inscrit
      */
    const QString& getBrancheAValider() { return brancheAValider; }
    void setBrancheAValider(const QString& branche) { brancheAValider = branche; }

    bool uvDejaValidee(const UV* uv);
    QVector<const UV *> &getAllUV();
};

#endif // CURSUS_H

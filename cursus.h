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

    ///Ajoute une filière à valider au Cursus. Si la filière n'existe pas, une exception est déclenchée
    ///@param filiere Nom de la filière à ajouter
    void ajouterFiliere(const QString& filiere);
    ///Renvoie la liste des filières à valider
    QStringList& getFiliere() { return filieres; }
    ///Renvoie la liste des filières à valider
    const QStringList& getFiliere() const { return filieres; }

    ///Renvoie la branche que l'étudiant doit valider
    const QString& getBrancheAValider() { return brancheAValider; }
    ///Définie la branche que l'étudiant doit valider. Si la branche n'existe pas, une exception est levée
    /// @param branche Sigle de la branche à valider
    void setBrancheAValider(const QString& branche) { brancheAValider = branche; }

    ///Paracour le cursus et regarde si une UV donnée à été validée ou non
    /// @param uv Pointeur vers l'UV a vérifier
    bool uvDejaValidee(const UV* uv);
    ///Renvoie toutes les UV qui ont été validée
    QVector<const UV *> &getAllUV();
};

#endif // CURSUS_H

#ifndef SEMESTRECOURS_H
#define SEMESTRECOURS_H

#include <QVector>
#include "inscription.h"

enum Saison
{
    Automne,
    Printemps
};

struct Semestre
{
    Saison s;
    unsigned short annee;
};

class SemestreCours
{
    Semestre date;
    QVector<Inscription> inscription;

public:
    SemestreCours(Semestre date);

    void ajouterInscription(const Inscription& i);
    const QVector<Inscription> &getInscriptions();
};

#endif // SEMESTRECOURS_H

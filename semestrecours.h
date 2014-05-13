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

/**
 * @brief Classe représentant un semestre de cours
 */
class SemestreCours
{
    Semestre date;
    QVector<Inscription> inscription;

public:
    /**
     * @brief Unique constructeur
     * @param date
     */
    SemestreCours(Semestre date);

    /**
     * @brief Ajoute une inscription au semestre
     * @param i
     */
    void ajouterInscription(const Inscription& i);
    /**
     * @brief Renvoie une référence vers toutes les inscriptions du semestre
     * @return
     */
    const QVector<Inscription> &getInscriptions() { return inscription; }
};

#endif // SEMESTRECOURS_H

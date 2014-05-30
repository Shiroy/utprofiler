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
    Semestre(const QString& date);
    QString toString() const;

    Saison s;
    unsigned short annee;
};

/**
 * @brief Classe représentant un semestre de cours
 */
class SemestreCours
{
    Semestre date;
    QVector<Inscription*> inscription;

public:
    /**
     * @brief Unique constructeur
     * @param date
     */
    SemestreCours(Semestre d) : date(d) {}
    ~SemestreCours();

    /**
     * @brief Ajoute une inscription au semestre
     * @param i
     */
    void ajouterInscription(Inscription* i) { inscription.append(i); }
    /**
     * @brief Renvoie une référence vers toutes les inscriptions du semestre
     * @return
     */
    const QVector<Inscription*> &getInscriptions() { return inscription; }

    bool uvEnCours(const UV* uv);
    QVector<const UV *> getUVs();
};

#endif // SEMESTRECOURS_H

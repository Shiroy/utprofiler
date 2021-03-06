#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include "uv.h"

class SemestreCours;

enum Resultat
{
    A, B, C, D, E, F, FX, RES, EN_COURS
};

/**
 * @brief Classe représentant une inscription à une UV
 */
class Inscription
{
    const UV* m_uv;
    const SemestreCours& semestre;
    Resultat m_resultat;

    //Inscription(const Inscription& o);
public:
    /**
     * @brief Unique constructeur
     * @param uv UV pour laquelle l'inscription est créée
     * @param smstr Semestre de l'inscription
     * @param res Résultat éventuel de l'inscription. Par défaut l'inscription est considérée comme EN_COURS.
     */
    Inscription(const UV* uv, const SemestreCours *smstr, Resultat res = EN_COURS) : m_uv(uv), semestre(*smstr), m_resultat(res) {}

    /**
     * @brief Renvoie les semestre
     * @return
     */
    const SemestreCours& getSemestre() const { return semestre; }
    /**
     * @brief Renvoie l'UV
     * @return
     */
    const UV* getUV() const { return m_uv; }
    /**
     * @brief Renvoie le résultat
     * @return
     */
    Resultat getResultat() const {return m_resultat;}

    /**
     * @brief Modifie le résultat de l'inscription
     * @param res
     */
    void SetResultat(Resultat res) {m_resultat = res;}

    ///Convertie une note du format chaine de caractère en Resultat. Cette méthode déclenche une exception en cas de problème
    static Resultat noteTextToEnum(const QString& note);
    ///Convertie un Resultat en son équivalent en chaine de caractère. Cette méthode déclenche une exception en cas de problème
    static QString noteEnumToText(Resultat res);
};

#endif // INSCRIPTION_H

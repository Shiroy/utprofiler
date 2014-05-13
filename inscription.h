#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include "uv.h"

enum Resultat
{
    A, B, C, D, E, F, FX, RES, EN_COURS
};

class Inscription
{
    const UV& m_uv;
    const SemestreCours& semestre;
    Resultat m_resultat;

    Inscription(const Inscription& o);
public:
    Inscription(const UV& uv, const SemestreCours &semestre, Resultat res = EN_COURS);

    SemestreCours *getSemestre() const { return smestre; }
    const UV& getUV() const { return m_uv; }
    Resultat getResultat() const {return m_resultat;}

    void SetResultat(Resultat res) {m_resultat = res;}
};

#endif // INSCRIPTION_H

#include "cursus.h"

Cursus::Cursus()
{
}

bool Cursus::uvDejaValidee(const UV *uv)
{
    for(auto it = tousLesSemestres.begin() ; it != tousLesSemestres.end() ; it++)
    {
        SemestreCours* sem = *it;
        if(sem->uvEnCours(uv))
            return true;
    }

    return false;
}

QVector<const UV*>& Cursus::getAllUV()
{
    QVector <const UV*> touteLesUv;
    for(auto it = tousLesSemestres.begin() ; it != tousLesSemestres.end() ; it++)
    {
        SemestreCours* sem = *it;
        touteLesUv += sem->getUVs();
    }

    return touteLesUv;
}

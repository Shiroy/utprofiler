#include "semestrecours.h"

bool SemestreCours::uvEnCours(const UV *uv)
{
    for(auto it = inscription.begin() ; it != inscription.end() ; it++)
    {
        if((*it)->getUV()->getCode() == uv->getCode())
            return true;
    }

    return false;
}

QVector<const UV*> SemestreCours::getUVs()
{
    QVector <const UV*> toutesLesUvsDuSemestre;
    for(auto it = inscription.begin() ; it != inscription.end() ; it++)
    {
        toutesLesUvsDuSemestre.push_back((*it)->getUV());
    }
}

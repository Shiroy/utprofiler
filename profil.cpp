#include "profil.h"

Profil::Profil()
{
}

Profil::~Profil()
{
    for(auto it = conditions.begin() ; it != conditions.end() ; it++)
        delete *it;
}

void Profil::delPredicat(Predicat *prcdt)
{
    if(conditions.contains(prcdt))
    {
        conditions.remove(conditions.indexOf(prcdt));
        delete prcdt;
    }
}

#include "profil.h"

Profil::Profil()
{
}

Profil::~Profil()
{
    for(auto it = conditions.begin() ; it != conditions.end() ; it++)
        delete *it;
}

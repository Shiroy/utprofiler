#include "predicats.h"

Predicat* PredicatFactory(int type)
{
    switch (type) {
    case PREDICAT_UV_OBLIGATOIRE:
        return new PredicatUVObligatoire;
        break;
    case PREDICAT_X_UV_PARMIS:
        return new PredicatXUVParmis;
        break;
    case PREDICAT_MINIMUM_CREDIT_IN_CATEGORY:
        return new PredicatMinimumCreditInCategory;
        break;
    case PREDICAT_MINIMUM_CREDIT:
        return new PredicatMinimumCredit;
        break;
    default:
        return 0;
        break;
    }
}

PredicatUVObligatoire::PredicatUVObligatoire() : Predicat() {}
bool PredicatUVObligatoire::predicatSatifait(QVector<const UV*> uvValidee)
{
    //Merci auto :-)
    for(auto it = uvValidee.begin() ; it != uvValidee.end() ; it++)
    {
        if((*it)->getCode() == uv)
            return true;
    }

    return false;
}
bool PredicatUVObligatoire::chargerParametres(QStringList &list)
{
    uv = list.first();
    return true;
}

PredicatXUVParmis::PredicatXUVParmis() : Predicat() {}
bool PredicatXUVParmis::predicatSatifait(QVector<const UV *> uvValidee)
{
    int nbUvValider = 0;
    for(auto it = uvValidee.begin() ; it != uvValidee.end() ; it++)
    {
        if(candidats.contains((*it)->getCode()))
            nbUvValider++;
    }

    return nbUvValider >= minimumUV;
}
bool PredicatXUVParmis::chargerParametres(QStringList &list)
{
    candidats = list;
    return true;
}

PredicatMinimumCreditInCategory::PredicatMinimumCreditInCategory() : Predicat() {}
bool PredicatMinimumCreditInCategory::predicatSatifait(QVector<const UV *> uvValidee)
{
    unsigned int total = 0;

    for(auto it = uvValidee.begin() ; it != uvValidee.end() ; it++)
    {
        const UV* current = (*it);
        if(current->getCategorie() == cat)
            total += current->getNombreCredit();
    }

    return total >= minimum;
}
bool PredicatMinimumCreditInCategory::chargerParametres(QStringList &list)
{
    bool ok = true;

    cat = static_cast<CategorieUV>(list[0].toInt(&ok));
    if(!ok)
        return false;
    minimum = list[1].toInt(&ok);
    if(!ok)
        return false;

    return true;
}

PredicatMinimumCredit::PredicatMinimumCredit() : Predicat() {}
bool PredicatMinimumCredit::predicatSatifait(QVector<const UV *> uvValidee)
{
    unsigned int total = 0;

    for(auto it = uvValidee.begin() ; it != uvValidee.end() ; it++)
    {
        const UV* current = (*it);
        total += current->getNombreCredit();
    }

    return total >= minimum;
}
bool PredicatMinimumCredit::chargerParametres(QStringList &list)
{
    bool ok = true;
    list.first().toInt(&ok);
    if(!ok)
        return false;

    return true;
}

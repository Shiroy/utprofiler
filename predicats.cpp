#include "predicats.h"

PredicatUVObligatoire::PredicatUVObligatoire(const QString &codeUV) : Predicat(), uv(codeUV) {}
PredicatUVObligatoire::PredicatUVObligatoire(const UV &uv) : PredicatUVObligatoire(uv.getCode()) {}
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

PredicatXUVParmis::PredicatXUVParmis(const QStringList &candidat, unsigned int minimumAValider) : Predicat(), candidats(candidat), minimumUV(minimumAValider) {}
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

PredicatMinimumCreditInCategory::PredicatMinimumCreditInCategory(CategorieUV categorie, unsigned int min) : Predicat(), cat(categorie), minimum(min) {}
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

PredicatMinimumCredit::PredicatMinimumCredit(unsigned int min) : Predicat(), minimum(min) {}
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

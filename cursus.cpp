#include "cursus.h"
#include "utmanager.h"
#include "utprofilerexception.h"

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

void Cursus::ajouterFiliere(const QString &filiere)
{
    if(!sUTManager->getProfile(filiere))
        UTPROFILER_EXCEPTION(QString("La filiere %1 n'existe pas").arg(filiere).toStdString().c_str());

    filieres << filiere;
}

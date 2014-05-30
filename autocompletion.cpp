#include "autocompletion.h"
#include "utmanager.h"
#include "utprofilerexception.h"

void StrategieAutocompletionConcreteSujet::Completer()
{
    UVMap &allUvs = sUTManager->getAllUVs();

    Cursus &cursus = refEtu.getCursus();

    const QString &branche = cursus.getBrancheAValider();

    Branche *ptBranche = sUTManager->getBranche(branche);
    if(!ptBranche)
        UTPROFILER_EXCEPTION(QString("Branche %1 inconnue").arg(branche).toStdString().c_str());

    QVector<Predicat*> allPredicat;
    Profil* PCB = ptBranche->getPCB();
    allPredicat += PCB->getAllPredicat();

    QVector<const UV*> uvCandidate;

    for(auto it = allUvs.begin() ; it != allUvs.end() ; it++)
    {
        UV* candiat = *it;

        if(cursus.uvDejaValidee(candiat))
            continue;

        Branche *brancheUvCandidate = candiat->getBranche();
        if(!brancheUvCandidate) //TODO lancer une exception quand toutes les branches auront été crées
            continue;

        if(brancheUvCandidate->getSigle() != ptBranche->getSigle())
            continue;

        //TODO gérer les priorité

        QVector<const UV*> parcourPotentiel = cursus.getAllUV() + uvCandidate;

        for(auto predicatIt = allPredicat.begin() ; predicatIt != allPredicat.end() ; it++)
        {
            if(!(*predicatIt)->predicatSatifait(parcourPotentiel))
            {
                if((*predicatIt)->recommanderUv() == candiat->getCode()) //UV recommander par un predicat (i.e UV obligatoire ou quasi obligatoire)
                {
                    uvCandidate.push_back(candiat);
                    break;
                }

                if((*predicatIt)->peutAmeliorerLeCursus(candiat->getCode()))
                {
                    uvCandidate.push_back(candiat);
                    break;
                }
            }
        }
    }
}

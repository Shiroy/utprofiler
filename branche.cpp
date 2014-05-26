#include "branche.h"
#include "utmanager.h"
#include "utprofilerexception.h"

Branche::Branche()
{
}

void Branche::link()
{
    PCB = sUTManager->getProfile(PCBString);
    if(!PCB)
        UTPROFILER_EXCEPTION(QString("Le PCB de la branche %1 n'existe pas").arg(getNom()).toStdString().c_str());

    PSF.clear();
    for(auto it = psfString.begin() ; it != psfString.end() ; it++)
    {
        Profil *psf = sUTManager->getProfile(*it);
        if(!psf)
            UTPROFILER_EXCEPTION(QString("Le PSF %1 de la branche %2 n'existe pas").arg(*it).arg(getNom()).toStdString().c_str());
        PSF.push_back(psf);
    }
}

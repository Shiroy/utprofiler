#include "uv.h"
#include "utmanager.h"

void UV::linkInformation()
{
    branche = sUTManager->getBranche(brancheStr);

    //TODO gerer les anomalie de donnée
}


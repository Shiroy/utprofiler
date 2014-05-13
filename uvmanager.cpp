#include "uvmanager.h"

UVManager* UVManager::getInstance()
{
    if(!instance)
        instance = new UVManager;
    return instance;
}

void UVManager::destroy()
{
    if(instance)
        delete instance;
    instance = 0;
}

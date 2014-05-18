#include "utmanager.h"
#include "utprofilerexception.h"

UTManager* UTManager::instance = 0;

UTManager::~UTManager()
{
    for(auto it = m_uvs.begin() ; it != m_uvs.end() ; it++)
        delete it.value();

    for(auto it = m_branches.begin() ; it != m_branches.end() ; it++)
        delete it.value();
}

UTManager* UTManager::getInstance()
{
    if(!instance)
        instance = new UTManager;
    return instance;
}

void UTManager::destroy()
{
    if(instance)
        delete instance;
    instance = 0;
}

UV *UTManager::getUV(const QString &code)
{
    auto uvIterator = m_uvs.find(code);
    if(uvIterator == m_uvs.end())
        return 0;
    return uvIterator.value();
}

Branche* UTManager::getBranche(const QString &sigle)
{
    auto brancheIterator = m_branches.find(sigle);
    if(brancheIterator == m_branches.end())
        return 0;
    return brancheIterator.value();
}

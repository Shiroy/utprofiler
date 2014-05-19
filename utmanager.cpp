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

Profil* UTManager::getProfile(const QString &nom)
{
    auto profilIterator = m_profils.find(nom);
    if(profilIterator == m_profils.end())
        return 0;
    return profilIterator.value();
}

UV* UTManager::nouvelleUV(const QString &code)
{
    UV* result = getUV(code);
    if(result)
        return result;
    else
    {
        result = new UV;
        m_uvs[code] = result;
        return result;
    }
}

Branche* UTManager::nouvelleBranche(const QString &sigle)
{
    Branche *result = getBranche(sigle);
    if(result)
        return result;
    else
    {
        result = new Branche;
        m_branches[sigle] = result;
        return result;
    }
}

Profil* UTManager::nouveauProfil(const QString &nom)
{
    Profil *result = getProfile(nom);
    if(result)
        return result;
    else
    {
        result = new Profil;
        m_profils[nom] = result;
        return result;
    }
}

bool UTManager::charger()
{
    if(!loader->prepareLoading())
        return false;

    if(!loader->load())
    {
        loader->clearAfterLoad();
        return false;
    }
    loader->clearAfterLoad();

    return true;
}

CategorieUV UTManager::categorieUVTextToEnum(const QString &txt)
{
    if(txt == "CS")
        return CS;
    if(txt == "TM")
        return TM;
    if(txt == "TSH")
        return TSH;
    if(txt == "SP")
        return SP;
    else
        UTPROFILER_EXCEPTION(QString("Catégorie d'UV inconnue : %1").arg(txt).toStdString().c_str());
}

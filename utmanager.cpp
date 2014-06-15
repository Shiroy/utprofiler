#include "utmanager.h"
#include "utprofilerexception.h"
#include <QMessageBox>

UTManager* UTManager::instance = 0;

UTManager::~UTManager()
{
    clearAll();
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

bool UTManager::charger(UTStream* loader)
{
    try
    {
        if(!loader->prepareLoading())
            return false;

        if(!loader->load())
        {
            loader->clearAfterLoad();
            return false;
        }
        loader->clearAfterLoad();

        lierLesElements();
    }
    catch(UTProfilerException &e)
    {
        clearAll();
        QMessageBox::critical(0, QString("Erreur au chargement"), QString(e.what()));
        return false;
    }

    return true;
}

bool UTManager::sauver(UTStream *saver)
{
    try
    {
        if(!saver->prepareSaving())
            return false;

        if(!saver->save())
        {
            saver->clearAfterSave();
            return false;
        }
        saver->clearAfterSave();
    }
    catch(UTProfilerException &e)
    {
        clearAll();
        QMessageBox::critical(0, QString("Erreur à la sauvegarde"), QString(e.what()));
        return false;
    }

    return true;
}

UVMap& UTManager::getAllUVs()
{
    return m_uvs;
}

BrancheMap& UTManager::getAllBranches()
{
    return m_branches;

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

QString UTManager::categorieUVEnumToText(CategorieUV cat)
{
    switch(cat)
    {
    case CS:
        return "CS";
        break;
    case TM:
        return "TM";
        break;
    case TSH:
        return "TSH";
        break;
    case SP:
        return "SP";
        break;
    default:
        UTPROFILER_EXCEPTION("UTManager::categorieUVEnumToText : catégorie d'UV inconnue");
        break;
    }
}

void UTManager::lierLesElements()
{
    /*UVMap allUvs = getAllUVs();
    for(auto it = allUvs.begin() ; it != allUvs.end() ; it++)
    {

    }*/

    for(auto it = m_branches.begin() ; it != m_branches.end() ; it++)
    {
        Branche* br = it.value();
        br->link();
    }
}

void UTManager::clearAll()
{
    for(auto it = m_uvs.begin() ; it != m_uvs.end() ; it++)
        delete it.value();

    m_uvs.clear();

    for(auto it = m_branches.begin() ; it != m_branches.end() ; it++)
        delete it.value();

    m_branches.clear();

    for(auto it = m_profils.begin() ; it != m_profils.end() ; it++)
        delete it.value();

    m_profils.clear();
}

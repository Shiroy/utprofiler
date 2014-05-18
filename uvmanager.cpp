#include "uvmanager.h"
#include "utprofilerexception.h"

UVManager* UVManager::instance = 0;

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

UV &UVManager::getUV(const QString &code)
{
    auto uvIterator = m_uvs.find(code);
    if(uvIterator == m_uvs.end())
        UTPROFILER_EXCEPTION(QString("UV %1 introuvable").arg(code).toStdString().c_str())
    return uvIterator.value();
}

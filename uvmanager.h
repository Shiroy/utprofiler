#ifndef UVMANAGER_H
#define UVMANAGER_H

#include <QVector>
#include "uv.h"
#include "uvstream.h"

/**
 * @brief The UVManager class
 * Cette classe à la responsabilité de la création et de la destruction des objets UV. C'est un singleton.
 */
class UVManager
{
public:    

    /**
     * @brief Renvoie l'instance actuelle de l'objet UVManager. Si aucune instance existe une nouvelle est créé.
     * @return
     */
    static UVManager* getInstance();
    /**
     * @brief Détruit l'instance actuelle de l'UVManager
     */
    static void destroy();

    /**
     * @brief Renvoie une référence constante sur un objet UV
     * @param code Code de l'UV désirée
     * @return
     */
    const UV& getUV(const QString& code);
    /**
     * @brief Charge les UV
     * @return
     */
    bool chargerUV();
    /**
     * @brief Permet de spécifier une méthode de chargement des UVs. Tous les chargeurs sont des classe UVStream spécialisée.
     * @param stream Le chargeur
     */
    void setUVStream(UVStream const* stream) { loader = stream; }

private:
    static UVManager* instance;

    UVStream* loader;

    QVector<UV> m_uvs;
};

UVManager* UVManager::instance = 0;

#endif // UVMANAGER_H

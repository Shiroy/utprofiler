#ifndef UVMANAGER_H
#define UVMANAGER_H

#include <QMap>
#include "uv.h"
#include "branche.h"
#include "etudiant.h"
#include "profil.h"
#include "utstream.h"

typedef QMap<QString, UV*> UVMap;

/**
 * @brief The UTManager class
 * Cette classe �  la responsabilité de la création et de la destruction des toutes les données utilisées par le programme. C'est un singleton.
 */
class UTManager
{
    friend class UTStream;

public:    

    /**
     * @brief Renvoie l'instance actuelle de l'objet UTManager. Si aucune instance existe une nouvelle est créé.
     * @return
     */
    static UTManager* getInstance();
    /**
     * @brief Détruit l'instance actuelle de l'UVManager
     */
    static void destroy();

    /**
     * @brief Renvoie une référence constante sur un objet UV
     * @param code Code de l'UV désirée
     * @return
     */
    UV* getUV(const QString& code);
    Branche* getBranche(const QString& sigle);

    /**
     * @brief Charge les donnée
     * @return
     */
    bool charger();
    /**
     * @brief Permet de spécifier une méthode de chargement des données. Tous les chargeurs sont des classe UVStream spécialisée.
     * @param stream Le chargeur
     */
    void setUTStream(UTStream* stream) { loader = stream; }

    UV* nouvelleUV(const QString& code);
    Branche* nouvelleBranche(const QString& sigle);
    Profil* nouveauProfil(const QString& nom);

    UVMap& getAllUVs();

    static CategorieUV categorieUVTextToEnum(const QString& txt);
    static QString categorieUVEnumToText(CategorieUV cat);

private:
    Profil* getProfile(const QString& nom);
    static UTManager* instance;
    ~UTManager();

    UTStream* loader;

    QMap<QString, UV*> m_uvs;
    QMap<QString, Branche*> m_branches;
    QMap<QString, Profil*> m_profils;
};

#define sUTManager UTManager::getInstance()

#endif // UVMANAGER_H

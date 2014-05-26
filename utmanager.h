#ifndef UVMANAGER_H
#define UVMANAGER_H

#include <QMap>
#include "uv.h"
#include "branche.h"
#include "etudiant.h"
#include "profil.h"
#include "utstream.h"

typedef QMap<QString, UV*> UVMap;
typedef QMap<QString, Branche*> BrancheMap;
typedef QMap<QString, Profil*> ProfilMap;

/**
 * @brief The UTManager class
 * Cette classe Ã  la responsabilitÃ© de la crÃ©ation et de la destruction des toutes les donnÃ©es utilisÃ©es par le programme. C'est un singleton.
 */
class UTManager
{
    friend class UTStream;

public:    

    /**
     * @brief Renvoie l'instance actuelle de l'objet UTManager. Si aucune instance existe une nouvelle est crÃ©Ã©.
     * @return
     */
    static UTManager* getInstance();
    /**
     * @brief DÃ©truit l'instance actuelle de l'UVManager
     */
    static void destroy();

    /**
     * @brief Renvoie une rÃ©fÃ©rence constante sur un objet UV
     * @param code Code de l'UV dÃ©sirÃ©e
     * @return
     */
    UV* getUV(const QString& code);
    Branche* getBranche(const QString& sigle);
    Profil* getProfile(const QString& nom);

    /**
     * @brief Charge les donnÃ©e
     * @return
     */
    bool charger();
    /**
     * @brief Permet de spÃ©cifier une mÃ©thode de chargement des donnÃ©es. Tous les chargeurs sont des classe UVStream spÃ©cialisÃ©e.
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
    void lierLesElements();
    void clearAll();

    static UTManager* instance;
    ~UTManager();

    UTStream* loader;

    QMap<QString, UV*> m_uvs;
    QMap<QString, Branche*> m_branches;
    QMap<QString, Profil*> m_profils;
};

#define sUTManager UTManager::getInstance()

#endif // UVMANAGER_H

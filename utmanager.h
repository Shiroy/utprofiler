#ifndef UVMANAGER_H
#define UVMANAGER_H

#include <QMap>
#include "uv.h"
#include "branche.h"
#include "etudiant.h"
#include "profil.h"
#include "uvstream.h"

/**
 * @brief The UTManager class
 * Cette classe à la responsabilité de la création et de la destruction des toutes les données utilisées par le programme. C'est un singleton.
 */
class UTManager
{
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
    void setUTStream(UVStream* stream) { loader = stream; }

private:
    static UTManager* instance;

    UVStream* loader;

    QMap<QString, UV*> m_uvs;
    QMap<QString, Branche*> m_branches;
};

#endif // UVMANAGER_H

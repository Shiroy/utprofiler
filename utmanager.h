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

    ///Renvoie un pointeur sur l'UTManager actuel
    static UTManager* getInstance();
    ///Detruit l'UTManager
    static void destroy();

    /**
     * @brief Renvoie un pointeur sur un objet UV
     * @param code Code de l'UV dÃ©sirÃ©e
     * @return
     */
    UV* getUV(const QString& code);
    Branche* getBranche(const QString& sigle);
    Profil* getProfile(const QString& nom);

    /**
     * @brief Charge les données à partir d'un chargeur
     * @return
     */
    bool charger(UTStream *loader);
    ///Sauve les donnée dans un "saver"
    bool sauver(UTStream* saver);

    ///Créer une nouvelle UV en utilisant ce code.
    /// Si l'UV existe déjà un pointeur vers l'UV existante est renvoyé.
    /// Les UVs sont détruite à la destruction de l'UTManager
    /// @return Pointeur vers la nouvelle UV
    UV* nouvelleUV(const QString& code);
    ///Créer une nouvelle branche en utilisant ce sigle.
    /// Si la branche existe déjà, un pointeur vers la branche existante est renvoyé
    /// Les branches sot détruite à la destruction de l'UTManager
    /// @return Pointeur vers la nouvelle branche
    Branche* nouvelleBranche(const QString& sigle);
    ///Créer une nouveau profil en utilisant ce nom (ie : PCB_GI, PHITECO, ADEL, etc)
    /// Si le profil existe déja, un pointeur vers le profil existant est retourné
    /// Les profils sont détruit lors de la destruction de l'UTManager
    /// @return Le pointeur ver le nouveau profil
    Profil* nouveauProfil(const QString& nom);

    ///Renvoie la map de toutes les UV
    UVMap& getAllUVs();
    ///Renvoie la map de toutes les Branche
    BrancheMap& getAllBranches();
    ///Renvoie la map de tous les Profil
    ProfilMap& getAllProfiles() { return m_profils; }

    ///Convertie une  CategorieUV en sa réprésentation littéral (ex: CS => "CS"). En cas d'échec, une exception est levée.
    static CategorieUV categorieUVTextToEnum(const QString& txt);
    ///Convertie une chaine de caractères en CategorieUV (ex : "CS" => CS). En cas d'échec, une exception est levée.
    static QString categorieUVEnumToText(CategorieUV cat);

private:
    ///Cette fonction lie les UV au branches (non-implémenté) et les branches à leurs profils.
    /// Cette méthode DOIT être appelé après un chargement
    void lierLesElements();
    ///Cette méthode efface toutes les données de l'UTManager
    void clearAll();

    static UTManager* instance;
    UTManager() {}
    ~UTManager();

    QMap<QString, UV*> m_uvs;
    QMap<QString, Branche*> m_branches;
    QMap<QString, Profil*> m_profils;
};

///Cette macro permet de créer un raccourcie. On a l'impression d'utiliser l'UTManager comme une variable globale sans perdre le principe d'encapsulation.
#define sUTManager UTManager::getInstance()

#endif // UVMANAGER_H

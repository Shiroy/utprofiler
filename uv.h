#ifndef UV_H
#define UV_H

#include <QString>
/**
 * @brief CategorieUV Toutes les catégories d'UV
 */
enum CategorieUV
{
    CS=1, /*!< Connaissances scientifiques*/
    TM=2, /*!< Techniques et méthodes*/
    TSH=3, /*!< Technologies et science de l'homme*/
    SP=4 /*!< Stages et projets*/
};
#define NB_CATEGORIE 4


class Branche;

/**
 * @brief Représente une UV
 */

class UV
{
    QString code, titre;
    unsigned int nombreCredit;
    CategorieUV categorie;
    Branche* branche;
    QString brancheStr;
    bool a, p;

public:
    /**
     * @brief Construit un objet de type UV. Les paramètres sont recopiés dans les attributs de l'objet     
     */

    UV() : a(false), p(false) {}

    /**
     * @brief Renvoie le code de l'UV
     * @return
     */
    const QString& getCode() const {return code;}
    /**
     * @brief Renvoie le titre de l'UV
     * @return
     */
    const QString& getTitre() const { return titre; }
    /**
     * @brief Renvoie le nombre de crédits rapportés par l'UV
     * @return
     */
    unsigned int getNombreCredit() const { return nombreCredit; }
    /**
     * @brief Renvoie la catégorie à laquelle appartient l'UV
     * @return
     */
    CategorieUV getCategorie() const { return categorie; }

    /**
     * @brief Modifie le titre de l'UV
     * @param ttr
     */
    void setTitre(const QString& ttr) { titre = ttr; }
    /**
     * @brief Modifie le code de l'UV
     * @param cde
     */
    void setCode(const QString& cde) { code = cde; }
    /**
     * @brief Modifie le nombre de crédit de l'UV
     * @param nbCrdt
     */
    void setNombreCredit(unsigned int nbCrdt) { nombreCredit = nbCrdt; }
    /**
     * @brief Modifie la catégorie de l'UV
     * @param cat
     */
    void setCategorie(CategorieUV cat) { categorie = cat; }

    ///Permet de définir la branche pour laquelle l'UV est diplômante
    void setBrancheStr(const QString& str) { brancheStr = str; }
    ///Permet de récupérer un pointeur vers la branche diplômante depuis l'UTManager
    void linkInformation();
    ///Renvoie la branche diplômante
    const Branche* getBranche() const { return branche; }
    ///Renvoie la branche diplômante
    Branche* getBranche() { return branche; }

    ///Définit si l'UV est enseigné à l'automne
    void setAutomne(bool b) { a = b; }
    ///Définit si l'UV est enseigner au printemps
    void setPrintemps(bool b) { p = b; }

    ///Permet de savoir si l'UV est enseignée à l'automne
    bool automne() { return a; }
    ///Permet de savoir si l'UV est enseignée au printemps
    bool printemps() { return p; }
};

#endif // UV_H

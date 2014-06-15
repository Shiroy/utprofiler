#ifndef UV_H
#define UV_H

#include <QString>
/**
 * @brief CategorieUV Toutes les catÃ©gories d'UV
 */
enum CategorieUV
{
    CS=1, /*!< Connaissance scientifique*/
    TM=2, /*!< Technique et mÃ©thode*/
    TSH=3, /*!< Technologie et science de l'homme*/
    SP=4 /*!< Stage et projet*/
};
#define NB_CATEGORIE 4


class Branche;

/**
 * @brief RÃ©prÃ©sente une UV
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
     * @brief Renvoie le nombre de crédit rapporté par l'UV
     * @return
     */
    unsigned int getNombreCredit() const { return nombreCredit; }
    /**
     * @brief Renvoie la catÃ©gorie à  laquelle appartient l'UV
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

    void setBrancheStr(const QString& str) { brancheStr = str; }
    void linkInformation();
    const Branche* getBranche() const { return branche; }
    Branche* getBranche() { return branche; }

    void setAutomne(bool b) { a = b; }
    void setPrintemps(bool b) { p = b; }

    bool automne() { return a; }
    bool printemps() { return p; }
};

#endif // UV_H

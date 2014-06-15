#ifndef PROFIL_H
#define PROFIL_H

#include <QVector>
#include <QString>
#include <QObject>
#include <QDomElement>

class UV;

/**
 * @brief Classe représentant une condition de validation pour un profil (stratégie)
 */
class Predicat : public QObject
{
    Q_OBJECT
public:
    Predicat() {}
    virtual ~Predicat() {}
    ///À partir de la liste des UV validées, détermine si la condition gérée par ce prédicat est satisfaite ou non
    virtual bool predicatSatifait(QVector<const UV*> uvValidee) = 0;
    ///Permet de charger la liste des paramètres à partir d'une liste de chaîne de caractères fournie à partir du fichier XML des UVs
    virtual bool chargerParametres(QStringList& param) = 0;
    ///Cette méthode crée un QWidget d'édition qui permet de modifier le Predicat
    virtual QWidget* getEditorWidget(QWidget *parent) = 0;
    ///Cette fonction configure un QDomElement pour pouvoir sauvegarder les paramètres du Predicat
    virtual void sauverParametre(QDomElement& elem) = 0;

    ///Cette fonction permet au prédicat de suggérer, ou non, une UV pour sa réalisation est qui placée en priorité lors de l'autocomplétion
    virtual const QString recommanderUv() { return QString(); }

    ///Cette fonction permet de déterminer si une UV peut améliorer le Cursus vis-à-vis de ce Predicat. Si cette fonction est appelée c'est que la liste des UVs actuelles ne permet pa encore de réaliser le Predicat.
    virtual bool peutAmeliorerLeCursus(const QString& uv) = 0;
};

///Cette fonction permet de construire un nouveau prédicat à partir de son type énuméré
Predicat* PredicatFactory(int type);
///Cette fonction convertit le nom d'une énumération de prédicat en son équivalent énuméré.
int PredicatDescriptionToInt(const QString& desc);


/// Classe représentant un profil à valider pour le diplôme
/// C'est elle qui a la responsabilité de la destruction des Predicat
class Profil
{
    QString nomProfile;
    QVector<Predicat*> conditions;
public:
    Profil();
    ~Profil();

    ///Renvoie le nom du profil
    const QString& getNomProfile() const { return nomProfile; }
    void setNom(const QString& new_name) { nomProfile = new_name; }

    ///Ajoute un Predicat au Profil
    void addPredicat(Predicat* prdct) { conditions.push_back(prdct); }
    ///Supprime un Predicat du Profil.
    /// Quand un prédicat est supprimé, toute son interface d'édition, si elle existe, l'est aussi.
    void delPredicat(Predicat* prcdt);

    const QVector<Predicat*>& getAllPredicat() const { return conditions; }
    QVector<Predicat*> &getAllPredicat() { return conditions; }

    ///Vérifie si toutes les conditions du profil sont satisfaites ou non
    /// @return Renvoie false si l'une des conditions n'est pas satisfaite.
    bool profileValide(QVector<UV*> uvValidee);
};

#endif // PROFIL_H

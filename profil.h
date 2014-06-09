#ifndef PROFIL_H
#define PROFIL_H

#include <QVector>
#include <QString>
#include <QObject>

class UV;

/**
 * @brief Classe représentant une condition de validation pour un profil (strategie)
 */
class Predicat : public QObject
{
    Q_OBJECT
public:
    Predicat() {}
    virtual ~Predicat() {}
    ///À partir de la liste des UV valiéee, détermine si la condition géré par ce prédicat est satisfaite ou non
    virtual bool predicatSatifait(QVector<const UV*> uvValidee) = 0;    
    virtual bool chargerParametres(QStringList& param) = 0;
    virtual QWidget* getEditorWidget(QWidget *parent) = 0;

    virtual const QString recommanderUv() { return QString(); }

    virtual bool peutAmeliorerLeCursus(const QString& uv) = 0;
};

Predicat* PredicatFactory(int type);

/**
 * @brief Classe représentant un profil à valider pour le diplome
 */
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

    void addPredicat(Predicat* prdct) { conditions.push_back(prdct); }

    const QVector<Predicat*>& getAllPredicat() const { return conditions; }
    QVector<Predicat*> getAllPredicat() { return conditions; }

    ///Vérifie si toutes les conditions du profil sont satisfaites ou non
    /// @return Renvoie false si une des conditions n'est pas satisfaite.
    bool profileValide(QVector<UV*> uvValidee);
};

#endif // PROFIL_H

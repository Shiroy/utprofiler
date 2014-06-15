#ifndef UVSTREAM_H
#define UVSTREAM_H

#include <QString>

class UTStream
{
public:
    UTStream() {}

    virtual ~UTStream() {}

    /**
     * @brief Hook appelé avant le chargement, permettant de faire des préparations (ex : connexion à une base de données).
     * @return Si le retour est false, le chargement est avorté
     * @sa prepareSaving()
     */
    virtual bool prepareLoading() { return true; }
    /**
     * @brief Hook appelé au moment du chargement, pour la lecture des données.
     * @return Si le retour est false, le hook clearAfterLoad() est appelé et le chargement est avorté
     * @sa save()
     */
    virtual bool load() = 0;
    /**
     * @brief Hook appelé pour libérer les ressources après le chargement.
     *
     * Hook appelé pour libérer les ressources après le chargement. (ex: fermeture de fichiers, de connexions)
     * @sa clearAfterSave()
     */
    virtual void clearAfterLoad() {}

    /**
     * @brief Hook appelé avant la sauvegarde, permettant de faire des préparations (ex : connexion à une base de données).
     * @return Si le retour est false, la sauvegarde est avortée
     * @sa prepareLoading()
     */
    virtual bool prepareSaving() { return true; }
    /**
     * @brief Hook appelé au moment de la sauvegarde, pour la lecture des données.
     * @return Si le retour est false, le hook clearAfterSave() est appelé et le chargement est avorté
     * @sa load()
     */
    virtual bool save() = 0;
    /**
     * @brief Hook appelé pour libérer les ressources après la sauvegarde.
     *
     * Hook appelé pour libérer les ressources après la sauvegarde. (ex: fermeture de fichiers, de connexions)
     * @sa clearAfterLoad()
     */
    virtual void clearAfterSave() {}

    const QString& getError() { return error; }

protected:
    void setError(const QString& newError) { error = newError; }

private:
    QString error;
};

#endif // UVSTREAM_H

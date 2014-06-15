#ifndef ETUDIANTSTREAMXML_H
#define ETUDIANTSTREAMXML_H

#include "etudiantstream.h"
#include <QString>

class Etudiant;
class QDomElement;
class SemestreCours;

///Cette classe permet de gérer les données étudiantes au format XML (Stratégie)
class EtudiantStreamXML : public EtudiantStream
{
    QString filename;

    Etudiant &refEtu;

public:
    EtudiantStreamXML(const QString &file, Etudiant& etu);

    ///Charge les données
    /// Cette méthode ouvre le fichier, analyse les données XML et remplit l'étudiant et son cursus
    bool load() override;
    ///Sauvegarge les données
    /// Cette méthode sauvegarde les données de l'étudiant au format XML (info personelles, cursus, semestre, etc)
    bool save() override;

    ///Procédure analysant la section parcours du fichier XML
    void analyserParcours(const QDomElement &elem);
    ///Procédure analysant la section préférence du fichier XML
    /// Cette section stocke les préférences d'UV pour l'autocomplétion
    void analyserPreference(const QDomElement &elem);
    ///Cette procédure analyse un semestre d'étude
    void analyserSemestre(SemestreCours *semCours, const QDomElement& elem);
};

#endif // ETUDIANTSTREAMXML_H

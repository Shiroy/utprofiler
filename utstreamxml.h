#ifndef UTSTREAMXML_H
#define UTSTREAMXML_H

#include "utstream.h"
#include <QString>
#include <QDomNode>

///Permet de charger/sauver les UV, branches et profils au format XML
class UTStreamXML : public UTStream
{
    QString file;
public:
    UTStreamXML() : UTStream(){}

    ///Demande le fichier à ouvrir à l'utlisateur
    bool prepareLoading();
    ///Analyse le fichier XML et remplit l'UTManager
    bool load();

    ///Analyse les branches
    void brancheSection(QDomNode& e);
    ///Analyse les UVs
    void uvSection(QDomNode& e);
    ///Analyse les profils
    void profilSection(QDomNode& e);

    ///Demande à l'utilisateur le nom du fichier dans lequel les informations doivent être enregistrées.
    bool prepareSaving();
    ///Sauvegarde les informations
    bool save();
};

#endif // UTSTREAMXML_H

#ifndef ETUDIANTSTREAM_H
#define ETUDIANTSTREAM_H

///Cette classe abstraite permet d'implémenter le chargement et la sauvegarde d'un étudiant
class EtudiantStream
{
public:
    EtudiantStream();
    virtual ~EtudiantStream() {}

    ///Réimplementer cette fonction pour définir une nouvelle méhode de chargement
    virtual bool load() = 0;
    ///Réimplementer cette fonction pour définir une nouvelle méhode de sauvegarde
    virtual bool save() = 0;
};

#endif // ETUDIANTSTREAM_H

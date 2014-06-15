#ifndef BRANCHE_H
#define BRANCHE_H

#include <QString>
#include <QVector>
#include <QMap>
#include "uv.h"
#include "profil.h"
#include <QStringList>

/**
  *@brief Classe représentant une branche
  *
  *TSH est également considérée comme une branche, au même tritre que le GI ou le TC. Pour valider le diplome, il faut avoir valider la où on est inscrit plus la branche TSH.
  */
class Branche
{
    QString nom;
    QString sigle;
    Profil *PCB;
    QMap<QString, Profil*> PSF;

    QStringList psfString;
    QString PCBString;

public:
    Branche();

    ///Renvoie le nom de la branche (ex: Tronc commun)
    const QString& getNom() const { return nom; }
    ///Renvoie le sigle de la branche (ex: TC)
    const QString& getSigle() const { return sigle; }
    ///Renvoie le pointeur vers le PCB
    const Profil* getPCB() const { return PCB; }
    ///Renvoie le pointeur vers le PCB
    Profil* getPCB() { return PCB; }
    ///Renvoie la map de tous les PSF
    QMap<QString, Profil*>& getPSF() { return PSF; }
    ///Créer un PCB.
    /// Cette méthode déclenche une exception dans deux cas : soit le PCB existe déja, soit la branche n'a pas de sigle
    void createPCB();

    void setNom(const QString& nNom) { nom = nNom; }
    void setSigle(const QString& nSigle) { sigle = nSigle; }
    void setPCB(const QString& pcbStr) { PCBString = pcbStr; }
    ///Ajoute une filière
    /// @param newPsf Nom de la filière (tel qu'enregistré dans UTManager)
    /// @param Pointeur vers la filière. Si le pointeur vaut 0, alors la méthode link devra être appelée pour mettre à jour le pointeur de PSF interne à la classe. Cette façon de faire est utilisée au chargement, quand toutes les filières n'ont pas encore été créées.
    void addPsf(const QString& newPsf, Profil* psf = 0)
    {
        if(!psfString.contains(newPsf))
            psfString << newPsf;

        if(psf)
        {
            PSF[newPsf] = psf;
        }
    }
    ///Cette méthode permet de récupérer les pointeurs de PCB et filière à partir de l'UTManager (c'est un peu comme si on faisait une édition de lien). Cette méthode déclenche une exception à la moindre anomalie de donnée.
    void link();
};

#endif // BRANCHE_H

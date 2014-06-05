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
    const Profil* getPCB() const { return PCB; }
    Profil* getPCB() { return PCB; }
    QMap<QString, Profil*>& getPSF() { return PSF; }

    void setNom(const QString& nNom) { nom = nNom; }
    void setSigle(const QString& nSigle) { sigle = nSigle; }
    void setPCB(const QString& pcbStr) { PCBString = pcbStr; }
    void addPsf(const QString& newPsf)
    {
        if(!psfString.contains(newPsf))
            psfString << newPsf;
    }

    void link();
};

#endif // BRANCHE_H

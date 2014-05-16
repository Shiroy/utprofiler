#ifndef BRANCHE_H
#define BRANCHE_H

#include <QString>
#include <QVector>
#include <QMap>
#include "uv.h"

/**
  *@brief Classe représentant une branche
  *
  *TSH est également considérée comme une branche, au même tritre que le GI ou le TC. Pour valider le diplome, il faut avoir valider la où on est inscrit plus la branche TSH.
  */
class Branche
{
    QString nom;
    QString sigle;
    //Profil PCB;
    //QVector<Profil> PSF;
    QMap<CategorieUV, unsigned int> minimumCredit;

public:
    Branche();

    ///Renvoie le minimum de crédit CS nécessaires pour valider la branche
    unsigned int getMinimumCS() const { return minimumCredit[CS]; }
    ///Renvoie le minimum de crédit TM nécessaires pour valider la branche
    unsigned int getMinimumTM() const { return minimumCredit[TM]; }
    ///Renvoie le minimum de crédit TSH nécessaires pour valider la branche
    unsigned int getMinimumTSH() const { return minimumCredit[TSH]; }
    ///Renvoie le minimum de crédit SP nécessaires pour valider la branche
    unsigned int getMinimumSP() const { return minimumCredit[SP]; }
};

#endif // BRANCHE_H

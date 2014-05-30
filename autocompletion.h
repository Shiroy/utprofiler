#ifndef AUTOCOMPLETION_H
#define AUTOCOMPLETION_H

#include "etudiant.h"

/**
  *@brief Classe implémentant les outils d'autocompletion
  *
  */
/* Prise en compte de la classe abstraite Predicat pour gerer toutes les conditions de validation de l'autocompletion generees par les classes filles de cette classe abstraite.

    */


enum ExigenceUV {
    JeVeuxPas = -2,
    SiIlLeFaut = -1,
    PasDAvis = 0,
    PourquoiPas = 1,
    Imperatif = 2,
};


class StrategieAutocompletion
{
    // Pour l'instant la classe Etudiant n'est pas implementee -> attribut principal : pointeur sur un Cursus
protected :
    Etudiant& refEtu; //Et on respecte bien la relation d'agrégation entre StrategieAutocompletion et Etudiant
    StrategieAutocompletion(Etudiant& e) : refEtu(e){}
    virtual ~StrategieAutocompletion(){}
    /**
      *@brief
      *@param
      */
public :
    virtual void Completer() = 0;

    virtual void ConstruireCursus(const QList<UV*>& candidat) {/*TODO*/}
};

class StrategieAutocompletionConcreteSujet : protected StrategieAutocompletion
{
public :
    void Completer();
};




#endif // AUTOCOMPLETION_H

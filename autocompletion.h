#ifndef AUTOCOMPLETION_H
#define AUTOCOMPLETION_H

#include "cursus.h"
/**
  *@brief Classe implémentant les outils d'autocompletion
  *
  */
   /* Prise en compte de la classe abstraite Predicat pour gerer toutes les conditions de validation de l'autocompletion generees par les classes filles de cette classe abstraite.

    */


    //enum ExigenceUV {(-3), (-2), (-1) ,0 ,1 ,2};
    /*
      Signication des notes :
      -3 : l'etudiant refuse de faire l'UV
      -2 : l'etudiant souhaite reporter l'UV le plus tard possible
      -1 : l'etudiant souhaite reporter l'UV d'un semestre
       0 : neutre (valeur par defaut)
       1 : l'etudiant souhaite faire cette UV le plus tot possible
       2 : l'etudiant veut faire cette UV au prochain semestre
    */



class StrategieAutocompletion {
    // Pour l'instant la classe Etudiant n'est pas implementee -> attribut principal : pointeur sur un Cursus
    Cursus* ptCursus;
    StrategieAutocompletion(Cursus* c) : ptCursus(c){};
    /**
      *@brief
      *@param
      */
        public :
    void EmettreExigenceUV();
    void FigerChoixUV();
    virtual void Completer() = 0;
};

class StrategieAutocompletionConcreteSujet : protected StrategieAutocompletion {

public :
    void Completer();
};




#endif // AUTOCOMPLETION_H

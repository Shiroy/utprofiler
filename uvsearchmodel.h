#ifndef UVSEARCHMODEL_H
#define UVSEARCHMODEL_H

#include <QStandardItemModel>
#include "uv.h"

///Cette classe définit le modèle permettant l'affichage d'un résultat de recherche d'UV
class UVSearchModel : public QStandardItemModel
{
public:
    UVSearchModel(QObject *parent = 0);

    ///Ajoute une UV aux résultats
    void addUv(const UV& uv);
    ///Efface la liste de résutats
    void clearAllUV();
    ///Renvoie l'UV à la ligne row. Cette fonction déclenche une exception en cas d'erreur.
    UV *getUVAtRow(int row);
};

#endif // UVSEARCHMODEL_H

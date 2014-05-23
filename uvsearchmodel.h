#ifndef UVSEARCHMODEL_H
#define UVSEARCHMODEL_H

#include <QStandardItemModel>
#include "uv.h"

class UVSearchModel : public QStandardItemModel
{
public:
    UVSearchModel(QObject *parent = 0);

    void addUv(const UV& uv);
    void clearAllUV();
};

#endif // UVSEARCHMODEL_H
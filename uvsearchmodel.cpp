#include "uvsearchmodel.h"
#include "utmanager.h"

UVSearchModel::UVSearchModel(QObject *parent) : QStandardItemModel(parent)
{
    QStringList headers;
    headers << "UV" << "Description" << "Catégorie" << "Crédit" << "J'en veux";
    setHorizontalHeaderLabels(headers);
}

void UVSearchModel::addUv(const UV &uv)
{
    Q_ASSERT(false);
    /*QList<QStandardItem*> newRow;
    newRow.push_back(new QStandardItem(uv.getCode()));
    newRow.push_back(new QStandardItem(uv.getTitre()));
    newRow.push_back(new QStandardItem(UTManager::categorieUVEnumToText(uv.getCategorie())));
    newRow.push_back(new QStandardItem(QString::number(uv.getNombreCredit())));
    newRow.push_back(new QStandardItem("NYI"));
    appendRow(newRow);*/

    int row = rowCount();
    setItem(row, 0, new QStandardItem(uv.getCode()));
    setItem(row, 1, new QStandardItem(uv.getTitre()));
    setItem(row, 2, new QStandardItem(UTManager::categorieUVEnumToText(uv.getCategorie())));
    setItem(row, 3, new QStandardItem(QString::number(uv.getNombreCredit())));
    setItem(row, 4, new QStandardItem("NYI"));
}

void UVSearchModel::clearAllUV()
{
    removeRows(0, rowCount());
}

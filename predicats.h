#ifndef PREDICATS_H
#define PREDICATS_H

#include <QStringList>

#include "profil.h"
#include "uv.h"

class PredicatUVObligatoire : public Predicat
{
    QString uv;

public:
    explicit PredicatUVObligatoire(const QString& codeUV);
    explicit PredicatUVObligatoire(const UV& uv);

    bool predicatSatifait(QVector<const UV*> uvValidee) override;
};

class PredicatUneUVParmis : public Predicat
{
    QStringList candidats;

public:
    explicit PredicatUneUVParmis(const QStringList& candidat);

    bool predicatSatifait(QVector<const UV *> uvValidee) override;
};

class PredicatMinimumCreditInCategory : Predicat
{
    unsigned int minimum;
    CategorieUV cat;

public:
    PredicatMinimumCreditInCategory(CategorieUV categorie, unsigned int min);
    bool predicatSatifait(QVector<const UV *> uvValidee) override;
};

class PredicatMinimumCredit : public Predicat
{
    unsigned int minimum;

public:
    PredicatMinimumCredit(unsigned int min);
    bool predicatSatifait(QVector<const UV *> uvValidee);
};

#endif // PREDICATS_H

#ifndef PREDICATS_H
#define PREDICATS_H

#include <QStringList>

#include "profil.h"
#include "uv.h"

enum
{
    PREDICAT_UV_OBLIGATOIRE=1,
    PREDICAT_X_UV_PARMIS=2,
    PREDICAT_MINIMUM_CREDIT_IN_CATEGORY=3,
    PREDICAT_MINIMUM_CREDIT=4
};

class PredicatUVObligatoire : public Predicat
{
    QString uv;

public:
    explicit PredicatUVObligatoire();
    explicit PredicatUVObligatoire(const UV& uv);

    bool predicatSatifait(QVector<const UV*> uvValidee) override;
    bool chargerParametres(QStringList &list);
};

class PredicatXUVParmis : public Predicat
{
    QStringList candidats;
    unsigned int minimumUV;

public:
    explicit PredicatXUVParmis();

    bool predicatSatifait(QVector<const UV *> uvValidee) override;
    bool chargerParametres(QStringList &list);
};

class PredicatMinimumCreditInCategory : public Predicat
{
    unsigned int minimum;
    CategorieUV cat;

public:
    PredicatMinimumCreditInCategory();
    bool predicatSatifait(QVector<const UV *> uvValidee) override;
    bool chargerParametres(QStringList &list);
};

class PredicatMinimumCredit : public Predicat
{
    unsigned int minimum;

public:
    PredicatMinimumCredit();
    bool predicatSatifait(QVector<const UV *> uvValidee);
    bool chargerParametres(QStringList &list);
};

#endif // PREDICATS_H

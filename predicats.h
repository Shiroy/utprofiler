#ifndef PREDICATS_H
#define PREDICATS_H

#include <QStringList>

#include "profil.h"
#include "uv.h"
#include "utmanager.h"

enum
{
    PREDICAT_UV_OBLIGATOIRE=1,
    PREDICAT_X_UV_PARMIS=2,
    PREDICAT_MINIMUM_CREDIT_IN_CATEGORY=3,
    PREDICAT_MINIMUM_CREDIT=4
};

class PredicatUVObligatoire : public Predicat
{
    Q_OBJECT
    QString uv;

public:
    explicit PredicatUVObligatoire();
    explicit PredicatUVObligatoire(const UV& uv);

    bool predicatSatifait(QVector<const UV*> uvValidee) override;
    bool chargerParametres(QStringList &list) override;
    QWidget* getEditorWidget(QWidget *parent) override;

    const QString recommanderUv() override;

    bool peutAmeliorerLeCursus(const QString &uv) override;

private slots:
    void updateUv(const QString& str) { uv = str; }
};

class PredicatXUVParmis : public Predicat
{
    Q_OBJECT

    QStringList candidats;
    unsigned int minimumUV;

public:
    explicit PredicatXUVParmis();

    bool predicatSatifait(QVector<const UV *> uvValidee) override;
    bool chargerParametres(QStringList &list) override;
    QWidget* getEditorWidget(QWidget *parent) override;

    const QString recommanderUv() override;

    bool peutAmeliorerLeCursus(const QString &uv) override;

private slots:
    void addUv();
    void delUv();
    void updateMinimumUv(const int& newVal) { minimumUV = newVal; }
};

class PredicatMinimumCreditInCategory : public Predicat
{
    Q_OBJECT

    unsigned int minimum;
    CategorieUV cat;

public:
    PredicatMinimumCreditInCategory();
    bool predicatSatifait(QVector<const UV *> uvValidee) override;
    bool chargerParametres(QStringList &list) override;
    QWidget* getEditorWidget(QWidget *parent) override;

    bool peutAmeliorerLeCursus(const QString &uv) override;

private slots:
    void updateMinimum(int newMin) { minimum = newMin; }
    void updateCat(const QString& text) { cat = UTManager::categorieUVTextToEnum(text); }
};

class PredicatMinimumCredit : public Predicat
{
    Q_OBJECT

    unsigned int minimum;

public:
    PredicatMinimumCredit();
    bool predicatSatifait(QVector<const UV *> uvValidee) override;
    bool chargerParametres(QStringList &list) override;
    QWidget* getEditorWidget(QWidget *parent) override;

    bool peutAmeliorerLeCursus(const QString &uv) override { return true; } //Toute UV raporte des crédit

private slots:
    void updateMinimum(const int newMin) { minimum = newMin; }
};

#endif // PREDICATS_H

#include "semestrecours.h"
#include "utprofilerexception.h"

Semestre::Semestre(const QString &date)
{
    QChar char_saison = date[0];

    if(char_saison == 'A')
        s = Automne;
    else if(char_saison == 'P')
        s = Printemps;
    else
        UTPROFILER_EXCEPTION("Format de date de semestre invalide");

    QString anne = date;
    anne.remove(0, 1);
    bool conversionOk = true;
    annee = anne.toInt(&conversionOk);
    if(!conversionOk)
        UTPROFILER_EXCEPTION("Format de date de semestre invalide");

    annee %= 100; //On ramene le tout dans [0 ; 99]
}

QString Semestre::toString() const
{
    QString result;

    if(s == Automne)
        result = "A";
    else if(s == Printemps)
        result = "P";
    else
        UTPROFILER_EXCEPTION("Non, mais là si vous arrivez à planter ça, c'est vraiment que vous avez codé comme une grosse...bouse (Info utilie quand même, parce qu'on ne sait jamais, votre Semestre a une saison différente de Automne ou Printemps)");

    result += QString::number(annee);

    return result;
}

SemestreCours::~SemestreCours()
{
    for(auto it = inscription.begin() ; it != inscription.end() ; it++)
    {
        delete *it;
    }
}

bool SemestreCours::uvEnCours(const UV *uv)
{
    for(auto it = inscription.begin() ; it != inscription.end() ; it++)
    {
        if((*it)->getUV()->getCode() == uv->getCode())
            return true;
    }

    return false;
}

QVector<const UV*> SemestreCours::getUVs()
{
    QVector <const UV*> toutesLesUvsDuSemestre;
    for(auto it = inscription.begin() ; it != inscription.end() ; it++)
    {
        toutesLesUvsDuSemestre.push_back((*it)->getUV());
    }
}

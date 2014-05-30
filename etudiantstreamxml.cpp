#include "etudiantstreamxml.h"
#include "utprofilerexception.h"
#include "etudiant.h"
#include "utmanager.h"
#include <QFile>
#include <QDomDocument>

EtudiantStreamXML::EtudiantStreamXML(const QString &file, Etudiant &etu) : filename(file), refEtu(etu)
{
}

bool EtudiantStreamXML::load()
{
    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly))
        UTPROFILER_EXCEPTION("Impossible d'ouvrir le fichier de donnée étudiant");

    QDomDocument doc;

    QString error;
    int l, c;

    if(!doc.setContent(&f, &error, &l, &c))
        UTPROFILER_EXCEPTION(QString("Erreur lors de l'analyse du fichier étudiant : l %1 col %2 %3").arg(l).arg(c).arg(error).toStdString().c_str());

    QDomNode etuNode = doc.elementsByTagName("etudiant").at(0);

    if(etuNode.isNull())
        UTPROFILER_EXCEPTION("Fichier étudiant non valide");

    QDomNodeList etuChildNode = etuNode.childNodes();

    for(int i = 0 ; i < etuChildNode.size() ; i++)
    {
        QDomNode node = etuChildNode.at(i);

        QDomElement currentElement = node.toElement();
        if(currentElement.isNull())
            continue;

        if(currentElement.tagName() == "nom")
            refEtu.setNom(currentElement.text());

        if(currentElement.tagName() == "prenom")
            refEtu.setPrenom(currentElement.text());

        if(currentElement.tagName() == "branche")
            refEtu.getCursus().setBrancheAValider(currentElement.text());

        if(currentElement.tagName() == "filiere")
            refEtu.getCursus().ajouterFiliere(currentElement.text());

        if(currentElement.tagName() == "parcours")
            analyserParcours(currentElement);

        if(currentElement.tagName() == "preference")
            analyserPreference(currentElement);
    }


    return true;
}

bool EtudiantStreamXML::save()
{
    return true;
}

void EtudiantStreamXML::analyserParcours(const QDomElement &elem)
{
    QDomNodeList semestreList = elem.elementsByTagName("semestre");

    for(int i = 0 ; i < semestreList.size() ; i++)
    {
        QDomNode node = semestreList.at(i);

        QDomElement semestre = node.toElement();

        if(semestre.isNull())
            UTPROFILER_EXCEPTION("Un element <parcours> ne doit contenir que des <semestre>");

        if(!semestre.hasAttribute("date"))
            UTPROFILER_EXCEPTION("Un semestre doit forcement avoir une date");

        SemestreCours* sem = new SemestreCours(Semestre(semestre.attribute("date"))); //TODO détruire ça dans le destructeur de Cursus

        refEtu.getCursus().ajouterSemestre(sem);

        analyserSemestre(sem, semestre);
    }
}

void EtudiantStreamXML::analyserSemestre(SemestreCours *semCours, const QDomElement &elem)
{
    QDomNodeList inscriptionList = elem.elementsByTagName("resultat");
    for(int i = 0 ; i < inscriptionList.size() ; i++)
    {
        QDomNode inscriptionNode = inscriptionList.at(i);

        QDomElement inscription = inscriptionNode.toElement();
        if(inscription.isNull())
            continue;

        if(!inscription.hasAttribute("uv"))
            UTPROFILER_EXCEPTION("Une inscription doit avoir une UV");
        if(!inscription.hasAttribute("note"))
            UTPROFILER_EXCEPTION("Une inscription doit avoir une note");

        UV* uv = sUTManager->getUV(inscription.attribute("uv"));


        Inscription *insc = new Inscription(uv, semCours, Inscription::noteTextToEnum(inscription.attribute("note"))); //TODO détruire ça à la destruction du semestre

        semCours->ajouterInscription(insc);
    }
}

void EtudiantStreamXML::analyserPreference(const QDomElement &elem)
{
    //NYI
}

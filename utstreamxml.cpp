#include "utstreamxml.h"
#include <QFileInfo>
#include <QFile>
#include <QDomDocument>
#include "utmanager.h"

bool UTStreamXML::prepareLoading()
{
    if(!QFileInfo(file).exists())
    {
        setError("Le fichier n'existe pas");
        return false;
    }

    return true;
}

bool UTStreamXML::load()
{
    QFile f(file);
    if(!f.open(QIODevice::ReadOnly))
    {
        setError("Impossible d'ouvrir le fichier");
        return false;
    }
    QDomDocument doc;
    if(!doc.setContent(&f))
    {
        setError("Erreur lors de l'analyse du XML");
        return false;
    }

    QDomNode uvs = doc.firstChildElement("UVSection");
    if(!uvs.isNull())
    {
        uvSection(uvs);
    }

    QDomNode branches = doc.firstChildElement("BrancheSection");
    if(!branches.isNull())
    {
        brancheSection(branches);
    }

    QDomNode profile = doc.firstChildElement("ProfileSection");
    if(!profile.isNull())
    {
        profilSection(profile);
    }

    return true;
}

void UTStreamXML::uvSection(QDomNode &e)
{
    QDomElement uv = e.nextSiblingElement("uv");
    while(!uv.isNull())
    {
        QDomElement name, credit, code, branche;

        name = uv.firstChildElement("nom");
        code = uv.firstChildElement("code");
        credit = uv.firstChildElement("credit");
        branche = uv.firstChildElement("branche");

        if(!name.isNull() && !code.isNull() && !credit.isNull() && !branche.isNull() && credit.hasAttribute("type"))
        {
            UV* nouvelleUv = sUTManager->nouvelleUV(code.text());
            nouvelleUv->setCode(code.text());
            nouvelleUv->setTitre(name.text());
            nouvelleUv->setCategorie(UTManager::categorieUVTextToEnum(credit.attribute("type")));
            nouvelleUv->setNombreCredit(credit.text().toInt());

            ///@todo Gerer les branches
        }

        uv = uv.nextSiblingElement("uv");
    }
}

void UTStreamXML::brancheSection(QDomNode &e)
{
    QDomElement branche = e.nextSiblingElement("branche");
    while(!branche.isNull())
    {
        QDomElement sigle, nom, PCB, PSF;

        sigle = branche.firstChildElement("sigle");
        nom = branche.firstChildElement("nom");
        PCB = branche.firstChildElement("PCB");

        if(!sigle.isNull() && !nom.isNull() && !PCB.isNull())
        {
            Branche* br = sUTManager->nouvelleBranche(sigle.text());
            br->setNom(nom.text());
            br->setSigle(sigle.text());
            br->setPCB(PCB.text());

            QDomElement psf = e.firstChildElement("PSF");
            while(!psf.isNull())
            {
                br->addPsf(psf.text());
                psf = psf.nextSiblingElement("PSF");
            }
        }

        branche = branche.nextSiblingElement("branche");
    }
}

void UTStreamXML::profilSection(QDomNode &e)
{
    QDomNode profil = e.nextSiblingElement("profil");
    while(!profil.isNull())
    {
        QDomElement nom = profil.firstChildElement("nom");
        if(!nom.isNull())
        {
            Profil* prfl = sUTManager->nouveauProfil(nom.text());
            prfl->setNom(nom.text());

            QDomElement predicat = profil.firstChildElement("predicat");
            while(!predicat.isNull())
            {
                if(predicat.hasAttribute("type") && predicat.hasAttribute("param"))
                {
                    Predicat *prdct = PredicatFactory(predicat.attribute("type").toInt());
                    QStringList param = predicat.attribute("param").split(",");
                    if(!prdct->chargerParametres(param))
                        delete prdct;
                    else
                        prfl->addPredicat(prdct);
                }

                predicat = predicat.nextSiblingElement("predicat");
            }
        }
    }
}



#include "utstreamxml.h"
#include <QFileInfo>
#include <QFile>
#include <QDomDocument>
#include "utmanager.h"
#include <QFileDialog>
#include <QString>

bool UTStreamXML::prepareLoading()
{
    file = QFileDialog::getOpenFileName(0, "Fichier de donnée", QString(), "Fixhier XML *.xml");

    if(file.isEmpty())
        return false;

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

    QDomElement docElem = doc.documentElement();
    QDomNode uvs = docElem.firstChildElement("UVSection");
    if(!uvs.isNull())
    {
        uvSection(uvs);
    }

    QDomNode branches = docElem.firstChildElement("BrancheSection");
    if(!branches.isNull())
    {
        brancheSection(branches);
    }

    QDomNode profile = docElem.firstChildElement("ProfileSection");
    if(!profile.isNull())
    {
        profilSection(profile);
    }

    return true;
}

void UTStreamXML::uvSection(QDomNode &e)
{
    QDomElement uv = e.firstChildElement();
    while(!uv.isNull())
    {
        QDomElement name, credit, code, branche;

        name = uv.firstChildElement("nom");
        credit = uv.firstChildElement("credit");
        code = uv.firstChildElement("code");
        branche = uv.firstChildElement("branche");

        if(!name.isNull() && !code.isNull() && !credit.isNull() && credit.hasAttribute("type") && (!branche.isNull() || credit.attribute("type") == "TSH"))
        {
            UV* nouvelleUv = sUTManager->nouvelleUV(code.text());
            nouvelleUv->setCode(code.text());
            nouvelleUv->setTitre(name.text());
            nouvelleUv->setCategorie(UTManager::categorieUVTextToEnum(credit.attribute("type")));
            nouvelleUv->setNombreCredit(credit.text().toInt());

            nouvelleUv->setAutomne(!(uv.firstChildElement("automne").isNull()));
            nouvelleUv->setPrintemps(!(uv.firstChildElement("printemps").isNull()));

            ///@todo Gerer les branches
        }

        uv = uv.nextSiblingElement();
    }
}

void UTStreamXML::brancheSection(QDomNode &e)
{
    QDomElement branche = e.firstChildElement();
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

            QDomElement psf = branche.firstChildElement("PSF");
            while(!psf.isNull())
            {
                br->addPsf(psf.text());
                psf = psf.nextSiblingElement("PSF");
            }
        }

        branche = branche.nextSiblingElement();
    }
}

void UTStreamXML::profilSection(QDomNode &e)
{
    QDomNode profil = e.firstChildElement("profil");
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

        profil = profil.nextSiblingElement("profil");
    }
}

bool UTStreamXML::prepareSaving()
{
    QString filename = QFileDialog::getSaveFileName(nullptr, "Sauvegarder", QString(), "XML *.xml");

    if(filename.isEmpty())
        return false;

    file = filename;

    return true;
}

bool UTStreamXML::save()
{
    QDomDocument doc;
    QDomElement root = doc.createElement("utprofiler");

    QDomElement uvSection = doc.createElement("UVSection");

    UVMap uvMap = sUTManager->getAllUVs();
    for(auto it = uvMap.begin() ; it != uvMap.end() ; it++)
    {
        UV* uvPtr = it.value();
        QDomElement uv = doc.createElement("uv");

        QDomElement code = doc.createElement("code");
        code.appendChild(doc.createTextNode(uvPtr->getCode()));
        uv.appendChild(code);

        QDomElement nom = doc.createElement("nom");
        nom.appendChild(doc.createTextNode(uvPtr->getTitre()));
        uv.appendChild(nom);

        QDomElement credit = doc.createElement("credit");
        credit.appendChild(doc.createTextNode(QString::number(uvPtr->getNombreCredit())));
        credit.setAttribute("type", UTManager::categorieUVEnumToText(uvPtr->getCategorie()));
        uv.appendChild(credit);

        if(uvPtr->automne())
            uv.appendChild(doc.createElement("automne"));
        if(uvPtr->printemps())
            uv.appendChild((doc.createElement("printemps")));

        //Rustine en attendant la gestion complète des branches par les UV
        QDomElement branche = doc.createElement("branche");
        branche.appendChild(doc.createTextNode("Unk"));
        uv.appendChild(branche);

        uvSection.appendChild(uv);
    }

    root.appendChild(uvSection);

    QDomElement brancheSection = doc.createElement("BrancheSection");

    BrancheMap &brancheMap = sUTManager->getAllBranches();

    for(auto it = brancheMap.begin() ; it != brancheMap.end() ; it++)
    {
        Branche* br = it.value();

        QDomElement brancheElem = doc.createElement("branche");

        QDomElement sigle = doc.createElement("sigle");
        sigle.appendChild(doc.createTextNode(br->getSigle()));
        brancheElem.appendChild(sigle);

        QDomElement nom = doc.createElement("nom");
        nom.appendChild(doc.createTextNode(br->getNom()));
        brancheElem.appendChild(nom);

        QDomElement pcb = doc.createElement("PCB");
        pcb.appendChild(doc.createTextNode(br->getPCB()->getNomProfile()));
        brancheElem.appendChild(pcb);

        QMap<QString, Profil*> &psf = br->getPSF();
        for(auto psfIt = psf.begin() ; psfIt != psf.end() ; psfIt++)
        {
            QDomElement psfElem = doc.createElement("PSF");
            psfElem.appendChild(doc.createTextNode(psfIt.key()));
            brancheElem.appendChild(psfElem);
        }

        brancheSection.appendChild(brancheElem);
    }

    root.appendChild(brancheSection);

    ProfilMap& allProfile = sUTManager->getAllProfiles();

    QDomElement profilSection = doc.createElement("ProfileSection");

    for(auto it = allProfile.begin() ; it != allProfile.end() ; it++)
    {
        Profil* prfl = it.value();

        QDomElement profil = doc.createElement("profile");

        QDomElement desc = doc.createElement("description");
        desc.appendChild(doc.createTextNode(""));
        profil.appendChild(desc);

        QDomElement nom = doc.createElement("nom");
        nom.appendChild(doc.createTextNode(prfl->getNomProfile()));
        profil.appendChild(nom);

        QVector<Predicat*> &allPredicat = prfl->getAllPredicat();
        for(auto predIt = allPredicat.begin() ; predIt != allPredicat.end() ; predIt++)
        {
            Predicat* pred = *predIt;

            QDomElement predElem = doc.createElement("predicat");
            pred->sauverParametre(predElem);
            profil.appendChild(predElem);
        }

        profilSection.appendChild(profil);
    }

    root.appendChild(profilSection);
    doc.appendChild(root);

    QFile f(file);
    if(!f.open(QIODevice::WriteOnly))
        return false;

    f.write(doc.toString().toStdString().c_str());
    f.close();
}




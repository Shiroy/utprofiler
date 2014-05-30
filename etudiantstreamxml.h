#ifndef ETUDIANTSTREAMXML_H
#define ETUDIANTSTREAMXML_H

#include "etudiantstream.h"
#include <QString>

class Etudiant;
class QDomElement;
class SemestreCours;

class EtudiantStreamXML : public EtudiantStream
{
    QString filename;

    Etudiant &refEtu;

public:
    EtudiantStreamXML(const QString &file, Etudiant& etu);

    bool load() override;
    bool save() override;

    void analyserParcours(const QDomElement &elem);
    void analyserPreference(const QDomElement &elem);
    void analyserSemestre(SemestreCours *semCours, const QDomElement& elem);
};

#endif // ETUDIANTSTREAMXML_H

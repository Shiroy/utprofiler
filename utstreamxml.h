#ifndef UTSTREAMXML_H
#define UTSTREAMXML_H

#include "utstream.h"
#include <QString>
#include <QDomNode>

class UTStreamXML : public UTStream
{
    QString file;
public:
    UTStreamXML(const QString& fileToOpen) : UTStream(), file(fileToOpen) {}

    bool prepareLoading();
    bool load();

    void brancheSection(QDomNode& e);
    void uvSection(QDomNode& e);
    void profilSection(QDomNode& e);

    bool save() { return true; }
};

#endif // UTSTREAMXML_H

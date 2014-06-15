#ifndef UTSTREAMXML_H
#define UTSTREAMXML_H

#include "utstream.h"
#include <QString>
#include <QDomNode>

class UTStreamXML : public UTStream
{
    QString file;
public:
    UTStreamXML() : UTStream(){}

    bool prepareLoading();
    bool load();

    void brancheSection(QDomNode& e);
    void uvSection(QDomNode& e);
    void profilSection(QDomNode& e);

    bool prepareSaving();
    bool save();
};

#endif // UTSTREAMXML_H

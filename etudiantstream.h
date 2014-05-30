#ifndef ETUDIANTSTREAM_H
#define ETUDIANTSTREAM_H

class EtudiantStream
{
public:
    EtudiantStream();
    virtual ~EtudiantStream() {}

    virtual bool load() = 0;
    virtual bool save() = 0;
};

#endif // ETUDIANTSTREAM_H

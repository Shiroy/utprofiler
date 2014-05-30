#include "inscription.h"
#include "utprofilerexception.h"

Resultat Inscription::noteTextToEnum(const QString &note)
{
    if(note == "A")
        return A;
    if(note == "B")
        return B;
    if(note == "C")
        return C;
    if(note== "D")
        return D;
    if(note == "E")
        return E;
    if(note == "F")
        return F;
    if(note == "FX")
        return FX;
    if(note == "EN_COURS")
        return EN_COURS;

    UTPROFILER_EXCEPTION("Note d'UV inconnue");
}

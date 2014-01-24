#ifndef TFILE_H
#define TFILE_H

#include "tliste.h"

typedef TListe tfile;

#define Enfiler_tfile(tfile, element) \
    Inserer_tliste(tfile, element, tfile->dernier_element)

#define Defiler_tfile(tfile, element) Supprimer_tliste(tfile, 0)

#define Raz_tfile Raz_tliste

#define Sommet_tfile(tfile) Acceder_tliste(tfile, 0)

#define Queue_tfile(tfile) Acceder_tliste(tfile, tfile.dernier_element)

#define Vide_tfile(tfile) Taille_tliste(tfile) == 0

#endif // TFILE_H

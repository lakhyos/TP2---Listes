#ifndef TPILE_H
#define TPILE_H

#include "tliste.h"

typedef TListe Tpile;

#define Empiler_tpile(tpile, element) Inserer_tliste(tpile, element, 0)

#define Depiler_tpile(tpile, element) Supprimer_tliste(tpile, 0)

#define Raz_tpile Raz_tliste

#define Sommet_tpile(tpile) Acceder_tliste(tpile, 0)

#define Vide_tpile(tpile) Taille_tliste(tpile) == 0

#endif // TPILE_H

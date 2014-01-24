#ifndef FILE_H
#define FILE_H

#include "dliste.h"

typedef Dliste File;

#define Enfiler_file(file, element) \
    Inserer_dliste(file, element, file->dernier_element)

#define Defiler_file(file, element) Supprimer_dliste(file, 0)

#define Raz_file Raz_dliste

#define Sommet_file(file) Acceder_dliste(file, 0)

#define Queue_file(file) Acceder_dliste(file, file.dernier_element)

#define Vide_file(file) Taille_dliste(file) == 0

#endif // FILE_H

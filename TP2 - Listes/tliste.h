#ifndef TLISTE_H
#define TLISTE_H

#include "tableau.h"

typedef Tableau Tliste;

#define Creer_tliste Creer_tableau

#define Detruire_tliste Detruire_tableau

#define Inserer_tliste Ajout_tableau

#define Acceder_tliste(tliste, position) tliste.donnee[position]

#define Supprimer_tliste Suppression_tableau

#define Suivant_tliste(tliste, position) tliste.donnee[position + 1]

#define Precedent_tliste(tliste, position) tliste.donnee[position - 1]

#define Taille_tliste Taille_tableau

/*
 * Nom de la fonction: Localiser_tliste
 * Entrées :
 *      Tliste tliste : La liste
 *      int element : L'element recherché
 * Sorties :
 *      int i : La première position de element si trouvé, sinon -1
 * Description:
 *      Recherche un element dans une liste et retourne sa position
 */
int Localiser_tliste(Tliste tliste, int element)
{
    int i;
    for(i = 0; i <= tliste.dernier_element; i++)
        if(i == element)
            return i;
    return -1;
}

/*
 * Nom de la fonction: Raz_tliste
 * Entrées :
 *      Tliste tliste : la liste
 * Description:
 *      Vide une liste
 */
void Raz_tliste(Tliste *tliste)
{
    tliste->dernier_element = -1;
}

/*
 * Nom de la fonction : Lister_tliste
 * Entrées  :
 *      Tliste tliste : La liste
 * Description:
 *      Affiche les elements de la liste
 */
void Lister_liste(Tliste tliste)
{
    int i = 0;
    for (int i; i <= tliste.dernier_element; ++i)
        printf("Element %d : %d\n", i, tliste.donnee[i]);
}

#endif // TLISTE_H

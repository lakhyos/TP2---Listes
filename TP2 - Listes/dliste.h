#ifndef DLISTE_H
#define DLISTE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*
 * Represente un element de la liste
 */
struct DlisteElement
{
    DlisteElement *suivant;
    DlisteElement *precedent;
    int valeur;
};
typedef struct DlisteElement DlisteElement;


/*
 * Represente la liste doublement chainee
 */
struct Dliste
{
    DlisteElement *premier;
    DlisteElement *dernier;
};
typedef struct Dliste Dliste;

/*
 * Nom de la fonction: Taille_dliste
 * Entrées :
 *      Dliste liste : La liste
 * Sorties :
 *      int taille : La taille de la liste
 * Description:
 *      Calcul la taille d'un liste doublement chainée
 */
int Taille_dliste(Dliste liste)
{
    if(!liste.premier)
        return 0;
    DlisteElement *actuel = liste.premier;
    int taille = 1;
    while(actuel->suivant) {
        actuel = actuel->suivant;
        taille++;
    }
    return taille;
}

/*
 * Nom de la fonction : Ajouter_debut_dliste
 * Entrées :
 *      Dliste liste : Une liste chainée
 *      int element : L'element à ajouter
 * Description:
 *      Ajoute un element en debut de liste
 */
void Ajouter_debut_dliste(Dliste *liste, int element)
{
    DlisteElement *dElement=(DlisteElement*)malloc(sizeof(DlisteElement));
    if(!dElement)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire");
        exit(1);
    }
    dElement->valeur = element;
    dElement->suivant = liste->premier;
    dElement->precedent = NULL;

    if(liste->premier)
        liste->premier->precedent = dElement->suivant;
    liste->premier = dElement;

    if(dElement->suivant == NULL)
        liste->dernier = dElement;
}

/*
 * Nom de la fonction : Ajouter_debut_dliste
 * Entrées :
 *      Dliste liste : Une liste chainée
 *      int element : L'element à ajouter
 * Description:
 *      Ajoute un element à la fin de la liste
 */
void Ajouter_fin_dliste(Dliste *liste, int element)
{
    if(liste->dernier)
    {
        DlisteElement *dElement = (DlisteElement*)
                malloc(sizeof(DlisteElement));
        if(!dElement)
        {
            fprintf(stderr, "Erreur d'allocation de mémoire");
            exit(1);
        }
        dElement->suivant = NULL;
        dElement->precedent = liste->dernier;
        dElement->valeur = element;
        liste->dernier->suivant  = dElement;
        liste->dernier = dElement;
    }
    else
        Ajouter_debut_dliste(liste, element);
}

/*
 * Nom de la fonction : Inserer_dliste
 * Entrées :
 *      Dliste* liste : La liste
 *      int element : L'element à inserer
 *      int position : La position
 * Description:
 *      Insere un element dans la liste à la position indiquée
 */
void Inserer_dliste(Dliste *liste, int element, int position)
{
    assert(position >= 0);
    assert(position <= Taille_dliste(*liste));

    if( position == 0)
        Ajouter_debut_dliste(liste, element);
    else
    {
        // Recherche de la position
        DlisteElement *actuel = liste->premier;
        int i;
        for(i=0; i < position - 1 ; i++)
            actuel = actuel->suivant;

        // Allocation dynamique de la mémoire pour element
        DlisteElement *dElement = (DlisteElement*) malloc(sizeof(DlisteElement));
        if(!dElement)
        {
            fprintf(stderr, "Erreur d'allocation de mémoire");
            exit(1);
        }
        dElement->suivant = NULL;
        dElement->precedent = NULL;
        dElement->valeur = element;

        // Liaison de element avec la liste
        dElement->suivant = actuel->suivant;
        dElement->precedent = actuel;
        if(dElement->suivant)
            dElement->suivant->precedent = dElement;
        actuel->suivant = dElement;
        if(dElement->suivant == NULL)
            liste->dernier = dElement;
    }
}

/*
 * Nom de la fonction : Acceder_dliste
 * Entrées :
 *      Dliste liste : La liste
 *      int position : La position de l'element cible
 * Sorties :
 *      DlisteElement element : L'element à la position donnée
 * Description:
 *      Retourne l'element à la position donnée
 */
DlisteElement Acceder_dliste(Dliste liste, int position)
{
    assert(position >= 0);
    assert(position < Taille_dliste(liste));

    if(position == 0)
        return *liste.premier;

    DlisteElement *actuel = liste.premier;
    int i;
    for (i=0; i<position ; i++)
        actuel = actuel->suivant;
    return *actuel;
}

/*
 * Nom de la fonction : Supprimer_debut_dliste
 * Entrées :
 *      Dliste liste : Une liste chainée
 * Description:
 *      Supprimer un element en debut de liste
 */
void Supprimer_debut_dliste(Dliste *liste)
{
    if(liste->premier->suivant)
    {
        DlisteElement *premier = liste->premier;
        liste->premier = liste->premier->suivant;
        liste->premier->precedent = NULL;
        free(premier);
    }
    else
    {
        liste->premier = NULL;
        liste->dernier = NULL;
    }
}

/*
 * Nom de la fonction : Supprimer_fin_dliste
 * Entrées :
 *      Dliste liste : Une liste chainée
 * Description:
 *      Supprimer le dernier element de la liste
 */
void Supprimer_fin_dliste(Dliste *liste)
{
    if(liste->premier)
    {
        DlisteElement *dernier = liste->dernier;
        liste->dernier = liste->dernier->precedent;
        liste->dernier->suivant = NULL;
        free(dernier);
    }
    else
    {
        Supprimer_debut_dliste(liste);
    }
}

/*
 * Nom de la fonction : Supprimer_dliste
 * Entrées :
 *      Dliste liste : La Liste
 *      int position : La position de l'element à supprimer
 * Description:
 *      Supprime l'element à la position indiquée
 */
void Supprimer_dliste(Dliste *liste, int position)
{
    assert(position >= 0);
    assert(position < Taille_dliste(*liste));

    if (position == 0) // Supression au debut
    {
        Supprimer_debut_dliste(liste);
    }
    else // Supression au milieu ou a la fin
    {
        // Recherche de la position
        DlisteElement *actuel = liste->premier;
        int i;
        for(i=0; i < position - 1 ; i++)
            actuel = actuel->suivant;

        // Liaisons
        DlisteElement* element = actuel->suivant;
        actuel->suivant = element->suivant;
        if(element->suivant)
            element->suivant->precedent = actuel;

        // Si element est le dernier element
        if(element->suivant == NULL)
            liste->dernier = element->precedent? element->precedent : NULL;

        free(element);
    }
}

/*
 * Nom de la fonction : Localiser_dliste
 * Entrées :
 *      Dliste liste : La liste
 *      int valeur : La valeur recherchée
 * Sorties :
 *      int position : La première position de la valeur recherchée, ou
 * -1 si elle n'est pas trouvée
 * Description:
 *      Recherche un element dans la liste et retourne sa position
 */
int Localiser_dliste(Dliste liste, int valeur)
{
    if(!liste.premier)
        return -1;
    DlisteElement *actuel = liste.premier;

    int position = 0;
    while (actuel) {
        if(actuel->valeur == valeur)
            return position;
        if(actuel->suivant)
        {
            actuel = actuel->suivant;
            position++;
        }
        else
            break;
    }
    return -1;
}

/*
 * Nom de la fonction : Raz_dliste
 * Entrées :
 *      Dliste liste : Une liste doublement chainée
 * Description:
 *      Vide la liste
 */
void Raz_dliste(Dliste *liste)
{
    while (liste->premier) {
        Supprimer_dliste(liste, 0);
    }
}

/*
 * Nom de la fonction : Lister_dliste
 * Entrées :
 *      Dliste liste : Une liste doublement chainée
 * Description:
 *      Affiche le contenu de la liste
 */
void Lister_dliste(Dliste liste)
{
    DlisteElement *actuel = liste.premier;
    int i;
    for(i=0; actuel; i++, actuel = actuel->suivant)
        printf("Element %d : %d\n", i, actuel->valeur );
}

#endif // DLISTE_H

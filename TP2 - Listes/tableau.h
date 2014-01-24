#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Déclaration des types et structures
struct Tableau
{
    int *donnee; // Données stockées dans le tableau
    int dernier_element; // l'indice du dernier element
    int taille_max; // Taille maximale du tableau
};
typedef struct Tableau Tableau;

// Déclaration des fonctions
/*
 * Le nom de la fonction : Creer_tableau
 * Entrées :
 *     int taille_max : La taille maximale du tableau
 * Sorties :
 *     Tableau* tableau : Le tableau creé
 * Déscription :
 *     Fait l'allocation dynamique d'un tableau dont la taille maximale
 * est taille_max
 */
Tableau Creer_tableau(int taille_max)
{
    Tableau tableau ;
    tableau.donnee = (int*) malloc(sizeof(int) * taille_max);
    tableau.dernier_element = -1; // Car le tableau est vide
    tableau.taille_max = taille_max;
    return tableau;
}

/*
 * Le nom de la fonction : Detruire_tableau
 * Entrées :
 *     Tableau* tableau : Le tableau à détruire
 * Description :
 *     Supprime la mémoire allouée pour le tableau
 */
void Detruire_tableau(Tableau *tableau)
{
    free(tableau->donnee);
    tableau->donnee = NULL;
    tableau->taille_max = 0;
}

/*
 * Nom de la fonction : Decalage_tableau
 * Entrées :
 *      Tableau* tableau : Le tableau contenant la partie à décaler
 *      int position : Position du premier element de la parite du tableau
 *   à décaler
 *      char sens : Le sens du decalage du tableau soit à gauche soit
 *   à droite
 * Description :
 *      Décale une partie du tableau soit à gauche soit à droite
 */
void Decalage_tableau(Tableau* tableau, int position, char sens)
{
    assert((sens == 'g' || sens == 'd'));
    assert(position > 0 || (position == 0 && sens == 'd'));
    assert(position <= tableau->dernier_element);
    if(sens == 'd')
    {
        int i;
        for (i = tableau->dernier_element; i >= position ; i--)
            tableau->donnee[i+1] = tableau->donnee[i];
        tableau->dernier_element++;
    }
    else
    {
        int i;
        for (i = position; i <= tableau->dernier_element ; i++)
            tableau->donnee[i-1] = tableau->donnee[i];
        tableau->dernier_element--;
    }
}

/*
 * Le nom de la fonction : Ajout_Tableau
 * Entrées :
 *     Tableau* tableau : Le tableau auquel on va ajouter
 *     int element : L'élément à ajouter
 *     int indice : L'indice de la case du tableau à la quelle sera ajouté
 *   l'élément
 * Description :
 *     Ajoute un élément dans un tableau
 */
void Ajout_tableau(Tableau *tableau, int element, int indice)
{
    assert(indice >= 0);
    assert(indice < tableau->taille_max);
    assert(tableau->dernier_element + 1 < tableau->taille_max);

    // Pas de décalage lors de l'ajout à la fin du tableau.
    if(indice <= tableau->dernier_element )
        Decalage_tableau(tableau, indice,'d');
    else
        // Cette  incrémentation se fait dans Decalage_tableau
        // pour les autres cas.
        tableau->dernier_element = indice ;
    tableau->donnee[indice] = element;
}

/*
 * Le nom de la fonction : Suppression_tableau
 * Entrées :
 *     Tableau* tableau : Le tableau dont un element sera détruit
 *     int indice : L'indice de la case dont l'élément sera détruit
 * Description :
 *     Supprime un élément d'un tableau
 */
void Suppression_tableau(Tableau *tableau, int indice)
{
    assert(tableau->dernier_element > -1);
    assert(indice >= 0);
    assert(indice <= tableau->dernier_element);
    // Supression au milieu ou au début
    if(indice != tableau->dernier_element)
        Decalage_tableau(tableau, indice + 1, 'g');
    // Supression du dernier élément
    else
        tableau->dernier_element--;
}

/*
 * Le nom de la fonction : Recherche_tableau
 * Entrées :
 *     Tableau tableau : Le tableau sur le quel on va effectuer
 *   la recherche
 *     int cible : l'élément recherché
 * Sorties :
 *     Tableau* resultat : Le tableau qui contient les emplacements de
 *   l'element recherché
 * Description :
 *     Fait la recherche d'un élément dans un tableau
 */
Tableau Recherche_tableau(Tableau tableau, int cible)
{
    Tableau resultat = Creer_tableau(tableau.taille_max);
    int i;
    for (i=0; i<=tableau.dernier_element; i++)
        if(tableau.donnee[i] == cible)
            Ajout_tableau(&resultat, i,resultat.dernier_element + 1);
    return resultat;
}

/*
 * Le nom de la fonction : Recherche_tableau
 * Entrées :
 *     Tableau tableau : Le tableau sur le quel on va effectuer
 *   la recherche
 *     int cible : l'élément recherché
 *     int min : Indice de la première borne
 *     int max : Indice de la deuxième borne
 * Sorties :
 *     Tableau* resultat : Le tableau qui contient les emplacements de
 *   l'element recherché
 * Description :
 *     Recherche dichotomique dans un tableau. Le tableau doit etre
 *   trié pour utiliser cette fonction.
 */
Tableau Recherche_dichotomique_tableau(Tableau tableau, int cible,
                                        int min, int max)
{
    Tableau resultat = Creer_tableau(tableau.taille_max);
    if(min > max)
        return resultat;
    else
    {
        int milieu = (min + max) / 2;

        if(cible > tableau.donnee[milieu])
            return Recherche_dichotomique_tableau(tableau, cible,
                                                  milieu + 1, max);
        else if(cible < tableau.donnee[milieu])
            return Recherche_dichotomique_tableau(tableau, cible,
                                                  min, milieu - 1);
        else
        {
            // Ajouter l'indice de l'element trouvé
            Ajout_tableau(&resultat, milieu, resultat.dernier_element + 1);
            // Recherche d'autre occurences
            int i;
            for (i = milieu - 1;
                 i >= 0 && tableau.donnee[i] == cible;
                 i--)
                Ajout_tableau(&resultat, i, 0);

            for(i = milieu + 1;
                i<=tableau.dernier_element && tableau.donnee[i] == cible;
                i++)
                Ajout_tableau(&resultat, i, resultat.dernier_element + 1);

            return resultat;
        }
    }
}

/*
 * Nom de la fonction: Taille_tableau
 * Entrées :
 *      Tableau tableau : Le tableau
 * Description:
 *      Retourne la taille du tableau
 */
int Taille_tableau(Tableau tableau)
{
    return tableau.dernier_element + 1;
}

#endif // FUNCTION_H

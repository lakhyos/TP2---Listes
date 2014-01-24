//
//  pile.h
//  TP2 - Listes
//
//  Created by Med Ayoub on 09/01/2014.
//  Copyright (c) 2014 Med Ayoub. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


typedef struct Pile{
    int val;
    struct Pile *suiv;
}Pile;

Pile *pile_creer(int val)
{
    Pile *pile = malloc(sizeof(Pile));
    if(!pile)
    {
        printf("Erreur d'allocation de mémoire\n");
        exit(1);
    }
    pile->val = val;
    return pile;
}

Pile *empiler(Pile *pile, int val)
{
    Pile *cellule = pile_creer(val);
    cellule = pile;
    return cellule;
}

int depiler(Pile *pile)
{
    int val = pile->val;
    pile = pile->suiv;
    return val;
}

int pile_taille(Pile *pile)
{
    Pile *tmp = NULL;
    int taille = 0;
    while(pile)
    {
        tmp = empiler(tmp, depiler(pile));
        taille++;
    }
    while(tmp) pile = empiler(pile, depiler(tmp));
    return taille;
}

Pile *ajout_position(Pile *pile, int val, int position)
{
    int deplacement = 0;
    Pile *tmp = NULL;
    
    if(position > pile_taille(pile)) return pile;
    
    while(pile && deplacement < position - 1)
        tmp = empiler(tmp, depiler(pile));
    
    pile = empiler(pile, val);
    
    while (tmp) pile = empiler(pile, depiler(tmp));
    
    return pile;
}

void affichage_pile(Pile *pile)
{
    Pile *tmp = NULL;
    while(pile)
    {
        tmp = empiler(tmp, depiler(pile));
        printf("%d ", tmp->val);
    }
    while(tmp) pile = empiler(pile, depiler(tmp));
}

void remplissage_pile(Pile **pile)
{
    int i, nombre_val, valeur;
    printf("Combient de valeurs voullez-vous ajouter ?");
    scanf("%d",&nombre_val);
    for (i = 0; i < nombre_val; i++)
    {
        printf("Donnez la valeur %d, a empiler ?", i);
        scanf("%d", &valeur);
        pile = empiler(*pile, valeur);
    }
}
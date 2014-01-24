//
//  main.c
//  TP2 - Listes
//
//  Created by Med Ayoub on 11/12/2013.
//  Copyright (c) 2013 Med Ayoub. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

int main()
{
    Pile *pile = NULL;
    printf("\n-----------------------\n");
    printf("taille pile = %d", pile_taille(pile));
    printf("\n-----------------------\n");
    remplissage_pile(pile);
    printf("\n-----------------------\n");
    affichage_pile(pile);
    printf("\n-----------------------\n");
    return 0;
}


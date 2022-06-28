#ifndef VAGUE_H
#define VAGUE_H

#include "general.h"
#include "affichage.h"

//void TotalAttaque(insecte_t tableauAttaque[TAILLEMAX], int *totalphysique, int *totalmagie, int nbrEnnemis);
void creationVague(spriteBase_t *spritesDeBase[NBRTEXTURES], combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], spriteCourant_t *listeCourant[tailleMaxSpritesCourants]); // il faut bien que listeCombattants soit vide à l'execution de cette fonction
//void extractionEnnemisVivants(spriteCourant_t *listeCourants[tailleMaxSpritesCourants], int nombreEnnemiParType[3]);

#endif
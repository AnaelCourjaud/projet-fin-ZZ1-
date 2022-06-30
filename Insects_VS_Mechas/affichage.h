#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "general.h"

void creationTexte(char texte[], char style[], char police[], SDL_Renderer *renderer, int taille, int x, int y, int opacite);
//void creationFond(SDL_Texture *my_texture,SDL_Window *window, SDL_Renderer *renderer, int x, int y);
void animation(SDL_Window *window, SDL_Renderer *renderer, spriteCourant_t *listeCourants[tailleMaxSpritesCourants]);
void creerAttaquant(spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], typeCombattant_t typeCombattant, etatCombattant_t etatArrivee, int indiceEmplacement, float posX, float posY);
void creerAttaquantSansSprite(combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], int indiceEmplacement);
int creerSpriteCourant(spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], indicesPNGs indicePNG, float posX, float posY);

void cleanListeCourants(spriteCourant_t *listeCourants[tailleMaxSpritesCourants]);
void cleanCombattantsDeListeCourants(spriteCourant_t *listeCourants[tailleMaxSpritesCourants]);
void cleanListeCombattants(combattant_t *tableauCombattants[NBRMAXCOMBATTANTS]);

void switchEtatCombattants(spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], typeCombattant_t familleCombattants, etatCombattant_t etatArrivee);
int retourIndicePNG(typeCombattant_t typeCombattants, etatCombattant_t etatArrivee);

int faireAvancerCombattants(combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], typeCombattant_t familleCombattants);

//void creationImage(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer, int longueur, int largeur, int x, int y);
//void Animation(SDL_Texture *, SDL_Texture *,SDL_Texture *, SDL_Renderer *renderer, SDL_Window *window, int longueur, int largeur, int x1, int x2, int y,int nbimage1,int nbimage2,int nbimageFond, int ite, int iteFond);

#endif
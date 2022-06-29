#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "general.h"

void creationTexte(char texte[], char style[], char police[], SDL_Renderer *renderer, int taille, int x, int y, int opacite);
//void creationFond(SDL_Texture *my_texture,SDL_Window *window, SDL_Renderer *renderer, int x, int y);
void animation(SDL_Renderer *renderer, spriteCourant_t *listeCourants[tailleMaxSpritesCourants]);
void creerAttaquant(SDL_Window *window, spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], combattant_t *tableauCombattants[NBRMAXCOMBATTANTS], indicesPNGs indicePNG, int indiceEmplacement);
int creerSpriteCourant(SDL_Window *window, spriteBase_t *spritesDeBase[NBRTEXTURES], spriteCourant_t *listeCourants[tailleMaxSpritesCourants], indicesPNGs indicePNG);

//void creationImage(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer, int longueur, int largeur, int x, int y);
//void Animation(SDL_Texture *, SDL_Texture *,SDL_Texture *, SDL_Renderer *renderer, SDL_Window *window, int longueur, int largeur, int x1, int x2, int y,int nbimage1,int nbimage2,int nbimageFond, int ite, int iteFond);

#endif
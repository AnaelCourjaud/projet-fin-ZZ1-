#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "general.h"

void init(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *tabPolices[nbrPolices], spriteBase_t *spritesDebase[nbrTextures]);
void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);
//void initSprite()

#endif
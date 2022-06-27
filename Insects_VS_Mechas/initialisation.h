#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "general.h"

void init(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture[nbrTextures], TTF_Font *tabPolices[nbrPolices]);
void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);
//void initSprite()

#endif
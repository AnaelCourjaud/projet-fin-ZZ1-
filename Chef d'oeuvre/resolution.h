#ifndef RESOLUTION_H
#define RESOLUTION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h>

#define ERREUR 10
#define ACCUEIL 20
#define JEU 30
#define FINJEU 40

#define EAU 0
#define FEU 1
#define TERRE 2
#define DEFENSE 3


int gagnant(int []);
void resolutionPV(int [], int , int []);
void changementEtatEnnemi(int []);
int defaite(int[]);
void reussitedefense(int [], int );
void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);

#endif
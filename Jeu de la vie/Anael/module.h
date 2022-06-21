#ifndef MODULE_H
#define MODULE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h>

#define ERREUR 10
#define MONDE 20
#define CONFIG 30
#define ITER 40
#define PAUSE 50
#define STABLE 60
#define FIN 70

#define HAUTEUR 25
#define LARGEUR 48

#define TAILLE_MAX 50

void end_sdl(char, char const *, SDL_Window *, SDL_Renderer *);
int chargerConfigInit(int[HAUTEUR][LARGEUR], int, char *);

#endif
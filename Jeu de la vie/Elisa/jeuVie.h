#ifndef JEUVIE_H
#define JEUVIE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h>


#define HAUTEUR 25
#define LARGEUR 48

void affichage(int grille[HAUTEUR][LARGEUR], SDL_Renderer *renderer);

#endif
#ifndef AFFICHAGE_H
#define AFFICHAGE_H

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

void creationTexte(char texte[], char style[], char police[], SDL_Renderer *renderer, int taille, int x, int y, int opacite);
void creationImage(char nom[], SDL_Renderer *renderer, int longueur, int largeur, int x, int y);

#endif
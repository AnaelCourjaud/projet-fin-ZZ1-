#ifndef GENERAL_H
#define GENERAL_H

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

#define nbrTextures 2
#define nbrPolices 2

#define nombreFichier 18
#define tailleMaxFichiers 50

#define nbrImageSpriteFini 10 //toutes les animations finies sont des sprites avec 10 images

#define coefReducEcran 0.8


#define indiceFond 3



typedef struct sprite {

    SDL_Texture * textureSprite;
    int wSource;
    int hSource;
    int xDestination;
    int yDestination;
    int wDestination;
    int hDestination;
    int animation;
    int nbrImages;
    int ralenti;
    //int personnage;
    //int PV;
    //int mortTerminee;

}sprite_t;


#endif
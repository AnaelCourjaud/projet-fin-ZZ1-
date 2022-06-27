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


#define nbrTextures 26
#define nbrPolices 2

#define nombreFichier 18
#define tailleMaxFichiers 50

#define nbrImageSpriteFini 10 //toutes les animations finies sont des sprites avec 10 images

#define coefReducEcran 0.8





#define indiceBatiment1 0
#define indiceBatiment2 1
#define indiceBatiment2coupe 2
#define indiceFond 3
#define indiceFondAccueil 4
#define indiceLore1 5
#define indiceLore2 6
#define indiceLore3 7 
#define indiceBugfirewalk 8
#define indiceBugfireattaque 9
#define indiceBugfiremort 10
#define indiceFlyvollant 11
#define indiceFlyattaque 12 
#define indiceFlymort 13
#define indiceMantiswalk 14
#define indiceMantismort 15
#define indiceRobot 16
#define indiceRobotattaque 17
#define indiceRobotmort 18 
#define indiceRobotmetal 19
#define indiceRobotmetalattaquedeb 20
#define indiceRobotmetalattaque 21
#define indiceRobotmetalmort 22 
#define indiceRobotpetit 23
#define indiceRobotpetitattaque 24
#define indiceRobotpetitmort 25


typedef struct sprite {

    SDL_Texture * textureSprite;
    SDL_Rect source;
    SDL_Rect destination;
    
    int animation;
    int nbrImages;
    int ralenti;
    //int personnage;
    //int PV;
    //int mortTerminee;

}sprite_t;


#endif
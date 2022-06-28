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
#define LORE1 30
#define LORE2 40
#define LORE3 50
#define VAGUE 60
#define ATTENTERIPOSTE 70
#define RIPOSTE 80
#define FINDEVAGUE 90
#define FINJEU 100


#define NBRTEXTURES 26
#define nbrPolices 2

//#define nombreFichier 18
#define tailleMaxFichiers 50

#define nbrImageSpriteFini 10 //toutes les animations finies sont des sprites avec 10 images

#define coefReducEcran 0.8

#define TAILLEMAX 4
#define tailleMaxSpritesCourants 20

#define ENNEMIVAGUE 3


typedef enum typePNG{
indicePasserelleFinie,
indiceBatiment2,
indiceBatiment2coupe,
indiceFond,
indiceFondAccueil,
indiceLore1,
indiceLore2,
indiceLore3, 
indiceBugfirewalk, 
indiceBugfireattaque,
indiceBugfiremort,
indiceFlyvolant,
indiceFlyattaque, 
indiceFlymort,
indiceMantiswalk,
indiceMantismort,
indiceRobot,
indiceRobotattaque,
indiceRobotMort, 
indiceRobotmetal,
indiceRobotmetalattaquedeb,
indiceRobotmetalattaque,
indiceRobotmetalmort,
indiceRobotpetitwalk,
indiceRobotpetitattaque,
indiceRobotpetitmort} indicesPNGs;

typedef enum typeS {DECOR, BUGFIRE, FLY, MANTIS, ROBOT, ROBOTPETIT, ROBOTMETAL}typesSprites;
typedef enum typePA {TOUTDEVANT, DEVANT, MILIEU, DERRIERE, TOUTDERRIERE}typesPrioritesaffichage;

int listeCompo[20][3] = {{BUGFIRE,NULL,NULL}, {FLY, NULL, NULL}, {MANTIS, NULL, NULL},
    {BUGFIRE,BUGFIRE,NULL}, {FLY, FLY, NULL}, {MANTIS, MANTIS, NULL}, {BUGFIRE,FLY,NULL}, {BUGFIRE,MANTIS,NULL}, {FLY, MANTIS, NULL},
    {BUGFIRE,BUGFIRE,BUGFIRE}, {FLY, FLY, FLY}, {MANTIS, MANTIS, MANTIS},
    {BUGFIRE,BUGFIRE,FLY}, {BUGFIRE,BUGFIRE,MANTIS}, {FLY, FLY, BUGFIRE}, {FLY, FLY, MANTIS}, {MANTIS, MANTIS, BUGFIRE}, {MANTIS, MANTIS, FLY}, {BUGFIRE,FLY,MANTIS}};

typedef struct spriteBase {

    SDL_Texture * textureSprite;
    enum typePNG indicePNG;
    enum typePA prioriteAffichage;
    
    int animation;
    int nbrImagesHorizontales;
    int nbrImagesVerticales;
    int ralenti;

    int vitesseX;

    //int personnage;
    //int PV;
    //int mortTerminee;

}spriteBase_t;

typedef struct spriteCourant{

    struct spriteBase *spriteDeBase;
    SDL_Rect source;
    SDL_Rect destination;

    int numImageEnCours;
    int retardateurRalenti;

}spriteCourant_t;

typedef struct combattant {

    struct spriteCourant *spriteCourant;

    enum typeS typeSprite;

    //int statPhysique;
    //int statMagie;

    int physiqueRestant;
    int magieRestante;

}combattant_t;


#endif
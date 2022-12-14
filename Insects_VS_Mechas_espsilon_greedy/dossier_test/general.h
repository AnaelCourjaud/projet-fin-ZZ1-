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

#define NBENNEMIVAGUE 3 //nb d'ennemis au debut de la vague
#define NBRMAXCOMBATTANTS 10
#define NBRTYPEINSECTES 3



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

typedef enum typeC {BUGFIRE, FLY, MANTIS, ROBOT, ROBOTPETIT, ROBOTMETAL}typesCombattants;
typedef enum typePA {TOUTDEVANT, DEVANT, MILIEU, DERRIERE, TOUTDERRIERE}typesPrioritesaffichage;


typedef struct spriteBase {

    SDL_Texture * textureSprite;
    enum typePNG indicePNG;
    //SDL_Rect source;
    //SDL_Rect destination;
    enum typePA prioriteAffichage;
    
    int animation;
    int nbrImagesHorizontales;
    int nbrImagesVerticales;
    int ralenti;
/*
    enum typeS typeSprite;
    int vitesseX;
    int statPhysique;
    int statMagie;

*/
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

    enum typeC typeCombattant;

    //int statPhysique;
    //int statMagie;

    int physiqueRestant;
    int magieRestante;

}combattant_t;
/*
typedef struct insecte {

    struct sprite spriteInsecte;
    enum typeI typeInsecte;
    int statPhysique;
    int statMagie;

}insecte_t;
*/

#endif
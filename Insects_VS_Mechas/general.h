#ifndef GENERAL_H
#define GENERAL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h> 
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h>


// extern int ETATJEU;

#define ERREUR 10
#define ACCUEIL 20
// #define TRAIN 130
#define LORE1 30
#define LORE2 40
#define LORE3 50
#define ARRIVEEVAGUE 60
#define ATTENTECHOIXRIPOSTE 70
#define ARRIVEERIPOSTE 80
#define ATTAQUESDEFENSEUR 120
#define ANIMATIONMORT 90
#define FINDEVAGUE 100
#define FINJEU 110


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
#define NBCOMPO 20 ///----/!\ 34 quand 4 ennemis par vague


#define NBPERCEPTION 19
#define PERCEPTIONMAX 35
#define NBDEFENSES 3
#define TAILLECHAR 5

#define NBRATTAQUESDEFENSEURAVANTMORT 3

#define NBRDEVAGUES 3
#define NBRVAGUESTRAIN 1000

// #define wHypothetiqueFenetre 1500
// #define hHypothetiqueFenetre 1000

#define xSponeDefenseur 0.2
#define ySponeDefenseur 0.7

typedef enum typePNG{
indicePasserelleAnimee,
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
indiceFlyWalk,
indiceFlyattaque, 
indiceFlymort,
indiceMantiswalk,
indiceMantisAttaque,
indiceMantismort,
indiceRobotGrosWalk,
indiceRobotGrosattaque,
indiceRobotGrosMort, 
indiceRobotmetalWalk,
indiceRobotmetalattaque,
indiceRobotmetalmort,
indiceRobotpetitwalk,
indiceRobotpetitattaque,
indiceRobotpetitmort} indicesPNGs;

typedef enum typeC {BUGFIRE, FLY, MANTIS, ROBOTGROS, ROBOTMETAL, ROBOTPETIT}typeCombattant_t;
typedef enum typePA {TOUTDEVANT, DEVANT, MILIEU, DERRIERE, TOUTDERRIERE}prioriteAffichage_t;
typedef enum typeE {WALK, ATTAQUE, MORT} etatCombattant_t;


typedef struct spriteBase {

    SDL_Texture * textureSprite;
    enum typePNG indicePNG;
    //SDL_Rect source;
    //SDL_Rect destination;
    enum typePA prioriteAffichage;

    float wCoefReductionDestination;
    float hCoefReductionDestination;

    int wImageSprite;
    int hImageSprite;
    
    // int animation;
    int animationInfinie;
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

    float xProportionPosFenetre;
    float yProportionPosFenetre;

    // SDL_Rect source;
    // SDL_Rect destination;

    int animationTerminee;
    int numImageEnCours;
    int retardateurRalenti;

}spriteCourant_t;

typedef struct combattant {

    struct spriteCourant *spriteCourant;

    enum typeC typeCombattant;
    enum typeE etatCombattant;

    //int statPhysique;
    //int statMagie;
    float speedX;
    float speedY;

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
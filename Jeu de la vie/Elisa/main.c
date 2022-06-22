#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h>

#include "jeuVie.h"

#define HAUTEUR 25
#define LARGEUR 48

#define CoinToriqueYHaut 540
#define CoinToriqueYBas 630
#define CoinToriqueXGauche 670 
#define CoinToriqueXDroit 1360

#define CoinNormalYHaut 710
#define CoinNormalYBas 800
#define CoinNormalXGauche 720 
#define CoinNormalXDroit 1320

#define TAILLE_MAX 1000


int main(int argc, char *argv[])
{
    /************** Initialisation de la SDL  + gestion de l'échec possible *********/
    /*                                                                              */
    /********************************************************************************/

    if(SDL_Init(SDL_INIT_VIDEO) !=0 ){
        SDL_Log("Error : SDL initialisation - %s\n",
            SDL_GetError());    // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }

    /*************************  Gestion des fenetres   *****************************/
    /*                                                                             */
    /*******************************************************************************/

    SDL_DisplayMode taille;
    SDL_GetCurrentDisplayMode(0, &taille);

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    
    /* Création de la fenêtre premiere fenetre*/
    window  = SDL_CreateWindow(
        "Fenetre 1",
        0, 0,
        taille.w, taille.h,
        SDL_WINDOW_RESIZABLE);
    
    
    if (window == NULL){
        SDL_Log("Error : SDL window 1 creation -%s\n",
            SDL_GetError());
        SDL_Quit();                              // On referme la SDL       
        exit(EXIT_FAILURE);
    }

    /* Creation de fond*/

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );

    if (renderer == 0) {
     fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
      /*faire ce qu'il faut pour quitter proprement */
    }
    
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);


    /***************************** Texte ********************************************/
    /*                                                                              */
    /********************************************************************************/

    /*****Initialisation*****/

    if (TTF_Init() < 0) fprintf(stderr, "Unable to initialize TTF:  %s\n", SDL_GetError());

    creationTexte("Bienvenue dans le jeu de la vie :", renderer, 70, 200, 100, 175); 
    creationTexte("Choix du Monde :", renderer, 100, 500, 400, 255); 
    creationTexte("~Torique~", renderer, 100, 700, 600, 200);  
    creationTexte("~NorMal~", renderer, 100, 740, 760, 200); 

    /*************************  Gestion du tableau *********************************/
    /*                                                                             */
    /*******************************************************************************/

    int i; int j;
    int grille[HAUTEUR][LARGEUR];

    for(i=0;i<HAUTEUR;i++){
        for(j=0;j<LARGEUR;j++){
            grille[i][j] = 0;
        }
    }

    affichage(grille, renderer);

    /*************************  Gestion des evenements *****************************/
    /*                                                                             */
    /*******************************************************************************/

    SDL_bool program_on = SDL_TRUE;               // Booléen pour dire que le programme doit continuer
    SDL_Event event;                              // c'est le type IMPORTANT !!

    int x; int y; int monde = 2; int e = 0;
    int modification = 0;
           

    char CONTROLE[] = "MONDE";
    int cadence = 0;

    int parametre = 0; // si parametre == 0, alors on considère que l'utilisateur n'a pas rentré de parametre, si ==1 si. 
    /*if (argc == 2){
        if (strlen(argv[1]) < TAILLE_MAX){
            parametre = chargerConfigInit(grille, argc, argv[1]);  // si il y a parametre, ça ouvre le fichier en question, si y a une erreur quelquepart, ça fait comme si il n'y avait pas de paramètre. retourne 0 si pas de parametre et 1 si il y a un parametre
        }
    }*/

    while (program_on)
    {
        int interessant = 0;
        while (interessant == 0 && SDL_PollEvent(&event)){
            // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
            // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type)
            {              // En fonction de la valeur du type de cet évènement
            case SDL_QUIT: // Un évènement simple, on a cliqué sur la x de la // fenêtre
                program_on = SDL_FALSE;
                interessant = SDL_TRUE; // Il est temps d'arrêter le programme
                break;
            case SDL_KEYDOWN: 
            switch (event.key.keysym.sym)
            {                // la touche appuyée est ...'
            case SDLK_SPACE: // ou 'SPC'
            // paused = !paused; // basculement pause/unpause
                break; 
            case SDLK_q:              // ou 'q'
                program_on = SDL_FALSE; // 'escape' ou 'q', d'autres façons de quitter le programme
                interessant = SDL_TRUE;
                break;
            default: // Une touche appuyée qu'on ne traite pas
                break;
            }
                break;
            case SDL_MOUSEBUTTONDOWN: // Click souris
                if (SDL_GetMouseState(NULL, NULL) &
                SDL_BUTTON(SDL_BUTTON_LEFT)){
                    //recupCoord = 1;
                    interessant = SDL_TRUE;
            }
            else if (SDL_GetMouseState(NULL, NULL) &
                    SDL_BUTTON(SDL_BUTTON_RIGHT))
            { // Si c'est un click droit
            // change_state(state, 2, window);           // Fonction à éxécuter lors d'un click droit
            }
                break;
            default: // Les évènements qu'on n'a pas envisagé
                break;
            }
        }

        switch (CONTROLE[0])
        {
            case 'E':
                break;
            case 'M':
                /*
                "Bienvenue dans le jeu de la vie, choisissez votre Monde :"
                bouton "monde torique " et bouton "monde normal"
                */
                if (SDL_MOUSEBUTTONDOWN){                    // Click souris   
                    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) ) {         // Si c'est un click gauche
                        SDL_GetMouseState(&x, &y);
                        if(((x > CoinToriqueXGauche) &&(x < CoinToriqueXDroit))&&((y > CoinToriqueYHaut) && (y < CoinToriqueYBas))){
                            monde = 1;
                            printf("monde :%d", monde);
                        }
                        if(((x > CoinNormalXGauche) &&(x < CoinNormalXDroit))&&((y > CoinNormalYHaut) && (y < CoinNormalYBas))){
                            monde = 0;
                            printf("monde :%d", monde);
                        }
                    }
                }
                if (monde != 2) {       
                    printf("yo");                
                    
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderClear(renderer);
 
                    affichage(grille, renderer);

                    if (parametre == 1)
                        strcpy(CONTROLE ,"ITER");
                    else if (parametre == 0)
                        strcpy(CONTROLE ,"CONFIG");
                    else
                        strcpy(CONTROLE ,"ERREUR");
                }
                break;
            case 'C':
                if (SDL_MOUSEBUTTONDOWN){                    // Click souris   
                    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {         // Si c'est un click gauche
                        SDL_GetMouseState(&x, &y);
                        grille[y/40][x/40] = 1;
                        affichage(grille, renderer);
                        
                    } 
                }  
                else  {
                    while (SDL_PollEvent(&event)){
                    switch (event.key.keysym.sym){                
                        case SDLK_s:
                            e = 1;}}}
                if ( e == 1) strcpy(CONTROLE ,"ITER");
                break;
            case 'I':
                printf("patate");
                //int modification = nouvgengrille(grille , grilletemp);
                if (modification == 0){
                    strcpy(CONTROLE ,"STABLE");
                }
                break;
            case 'S':
                printf(" s ");
                creationTexte("L'état est stable", renderer, 100, 700, 600, 200);  
                affichage(grille, renderer);
                break;
            case 'P':
                /*
                ça affiche l'écran de jeu avec, le nombre d'itérations, une bulle "Pause" et un bouton "au Boulot !"
                si tu fais 's' ou 'S' ça "sauvegarde"
                si t'appuies sur le bouton "au Boulot !" le jeu reprend.
                */
                break;   
            default:
                strcpy(CONTROLE ,"ERREUR");
                break;
        }

        SDL_Delay(20 + cadence);
    }

    /*while (program_on){                             // Voilà la boucle des évènements 

        if (SDL_PollEvent(&event)){                 // si la file d'évènements n'est pas vide : défiler l'élément en tête
                                                    // de file dans 'event'
            switch(event.type){                       // En fonction de la valeur du type de cet évènement
                case SDL_QUIT :                           // Un évènement simple, on a cliqué sur la x de la fenêtre
                    program_on = SDL_FALSE;                 // Il est temps d'arrêter le programme
                    break;
                default:                                  // L'évènement défilé ne nous intéresse pas
                    break;
                case SDL_MOUSEBUTTONDOWN:                     // Click souris   
                    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) ) {         // Si c'est un click gauche
                        SDL_GetMouseState(&x, &y);
                        if(((x > CoinToriqueXGauche) &&(x < CoinToriqueXDroit))&&((y > CoinToriqueYHaut) && (y < CoinToriqueYBas))){
                            monde = 1;
                            printf("monde :%d", monde);
                        }
                        if(((x > CoinNormalXGauche) &&(x < CoinNormalXDroit))&&((y > CoinNormalYHaut) && (y < CoinNormalYBas))){
                            monde = 0;
                            printf("monde :%d", monde);
                        }
                    }
                
            }
        }   
    }*/
    SDL_DestroyRenderer(renderer);  
    SDL_DestroyWindow(window); 
    TTF_Quit();
    SDL_Quit();   
    return 0;
}
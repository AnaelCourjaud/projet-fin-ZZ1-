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


int main()
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

    int x; int y; int monde = 2;
    while (program_on){                             // Voilà la boucle des évènements 

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
    }
    SDL_DestroyRenderer(renderer);  
    SDL_DestroyWindow(window); 
    TTF_Quit();
    SDL_Quit();   
    return 0;

}
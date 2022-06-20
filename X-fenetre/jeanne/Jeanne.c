#include <SDL2/SDL.h>
#include <stdio.h>

/************************************/
/*  exemple de création de fenêtres */
/************************************/

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
    SDL_Window 
       *window_1 = NULL,
       *window_2 = NULL;
    SDL_Renderer 
        *renderer1 = NULL,
        *renderer2 = NULL;
  
  /*Création de la première chaine de fenetre */
  /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", 
             SDL_GetError());                // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }
    window_1 = SDL_CreateWindow(
      "Fenetre de gauche",                    // codage en utf8, donc accents possibles
      50, 50,                                  // coin haut gauche en haut gauche de l'écran
      400, 300,                              // largeur = 400, hauteur = 300
      SDL_WINDOW_RESIZABLE);                 // redimensionnable
    
    window_2 = SDL_CreateWindow(
      "Fenetre de gauche",                    // codage en utf8, donc accents possibles
      450, 50,                                  // coin haut gauche en haut gauche de l'écran
      400, 300,                              // largeur = 400, hauteur = 300
      SDL_WINDOW_RESIZABLE);                 // redimensionnable

    renderer1 = SDL_CreateRenderer(window_1, -1, SDL_RENDERER_ACCELERATED ); /*  SDL_RENDERER_SOFTWARE */
        if (renderer1 == 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
        /* faire ce qu'il faut pour quitter proprement */
        }  
    renderer2 = SDL_CreateRenderer(window_2, -1, SDL_RENDERER_ACCELERATED ); /*  SDL_RENDERER_SOFTWARE */
        if (renderer2 == 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
        /* faire ce qu'il faut pour quitter proprement */
        }  


    /* couleur de fond */
    SDL_SetRenderDrawColor(renderer1, 0, 0, 255, 255);
    SDL_RenderClear(renderer1);
    SDL_SetRenderDrawColor(renderer2, 255, 127, 40, 255);
    SDL_RenderClear(renderer2);

    /* afficher à l'ecran */
    SDL_RenderPresent(renderer1);
    if (window_1 == NULL) {
        SDL_Log("Error : SDL window X creation - %s\n", 
                SDL_GetError());                 // échec de la création de la fenêtre
        SDL_Quit();                              // On referme la SDL       
        exit(EXIT_FAILURE);
    }
    SDL_RenderPresent(renderer2);
    if (window_2 == NULL) {
        SDL_Log("Error : SDL window X creation - %s\n", 
                SDL_GetError());                 // échec de la création de la fenêtre
        SDL_Quit();                              // On referme la SDL       
        exit(EXIT_FAILURE);
    }

    int i;
    int x;
    int y;
    int w,h;
    for(i=0;i<10;i++){
    SDL_GetWindowPosition(window_1,&x,&y);
    SDL_SetWindowPosition(window_1, x+50*i, y+50*i);
    SDL_GetWindowPosition(window_2,&x,&y);
    SDL_SetWindowPosition(window_2, x, y+50*i);
    }
    for(i=0;i<10;i++){
    SDL_GetWindowPosition(window_1,&x,&y);
    SDL_SetWindowPosition(window_1, x-50*i, y);
    SDL_GetWindowSize(window_1, &w, &h);
    SDL_SetWindowSize(window_1, w+50, h+50);
    }

  SDL_Delay(50000);                           // Pause exprimée  en ms

  /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
    SDL_DestroyRenderer(renderer2);
    SDL_DestroyRenderer(renderer1);
    SDL_DestroyWindow(window_2);
    SDL_DestroyWindow(window_1);
 
  SDL_Quit();                                // la SDL

  return 0;
}

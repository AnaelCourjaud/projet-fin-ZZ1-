#include <SDL2/SDL.h>
#include <stdio.h>

SDL_Window *creerWindow(int largeur, int longueur, int x, int y)
{
    
    /* Création de la fenêtre premiere fenetre*/
    SDL_Window *window  = SDL_CreateWindow(
        "Fenetre 1",
        x, y,
        largeur, longueur,
        SDL_WINDOW_RESIZABLE);
    
    
    if (window == NULL){
        SDL_Log("Error : SDL window 1 creation -%s\n",
            SDL_GetError());
        SDL_Quit();                              // On referme la SDL       
        exit(EXIT_FAILURE);
    }

    return window;
}

SDL_Renderer *creerRender(SDL_Window *window)
{
    
    SDL_Renderer 
        *renderer = NULL;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == 0) {
     fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
      /*faire ce qu'il faut pour quitter proprement */
    }
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    return renderer;
}

int main()
{
    SDL_DisplayMode taille;
    SDL_GetCurrentDisplayMode(0, &taille);


    SDL_Window
        *window_1 = NULL;
    SDL_Window
        *window_2 = NULL;

    SDL_Renderer 
        *renderer1 = NULL;
    SDL_Renderer
        *renderer2 = NULL;

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if(SDL_Init(SDL_INIT_VIDEO) !=0 ){
        SDL_Log("Error : SDL initialisation - %s\n",
            SDL_GetError());    // l'initialisation de la SDL a échoué 
        exit(EXIT_FAILURE);
    }

    /* Création de la fenêtre premiere fenetre*/
    window_1  = SDL_CreateWindow(
        "Fenetre 1",
        0, 0,
        1920, 100,
        SDL_WINDOW_RESIZABLE);
    
    
    if (window_1 == NULL){
        SDL_Log("Error : SDL window 1 creation -%s\n",
            SDL_GetError());
        SDL_Quit();                              // On referme la SDL       
        exit(EXIT_FAILURE);
    }

    /* Création de la fenêtre deuxieme fenetre*/
    window_2  = SDL_CreateWindow(
        "Fenetre 2",
        0, 1000,
        1920, 100,
        SDL_WINDOW_RESIZABLE);
    
    
    if (window_2 == NULL){
        SDL_Log("Error : SDL window 1 creation -%s\n",
            SDL_GetError());
        SDL_Quit();                              // On referme la SDL       
        exit(EXIT_FAILURE);
    }


    renderer1 = SDL_CreateRenderer(window_1, -1, SDL_RENDERER_ACCELERATED);
    if (renderer1 == 0) {
     fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
      /*faire ce qu'il faut pour quitter proprement */
    }
    
    SDL_SetRenderDrawColor(renderer1, 255, 0, 0, 128);
    SDL_RenderClear(renderer1);

    SDL_RenderPresent(renderer1);

    /*creation 2eme renderer */
    renderer2 = SDL_CreateRenderer(window_2, -1, SDL_RENDERER_ACCELERATED);
    if (renderer2 == 0) {
     fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
      /*faire ce qu'il faut pour quitter proprement */
    }
    
    SDL_SetRenderDrawColor(renderer2, 255, 0, 0, 128);
    SDL_RenderClear(renderer2);

    SDL_RenderPresent(renderer2);

    SDL_Delay(5000); 
    SDL_DestroyRenderer(renderer1);  
    SDL_DestroyRenderer(renderer2);  
    SDL_DestroyWindow(window_1);
    SDL_DestroyWindow(window_2);
    
    SDL_Quit();   
    return 0; 
}


#include <SDL2/SDL.h>
#include <stdio.h>

int main()
{
    SDL_DisplayMode taille;
    SDL_GetCurrentDisplayMode(0, &taille);


    SDL_Window
        *window_1 = NULL;
        *window_2 = NULL;

    SDL_Renderer 
        *renderer = NULL;

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

    //SDL_FillRect(window_1, NULL, SDL_MapRGB(window_1, 255, 255, 255));

    renderer = SDL_CreateRenderer(window_1, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == 0) {
     fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
      /*faire ce qu'il faut pour quitter proprement */
    }
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);


    SDL_Delay(5000); 
    SDL_DestroyRenderer(renderer);  
    SDL_DestroyWindow(window_1);
    
    SDL_Quit();   
    return 0; 
}

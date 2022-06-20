#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/*void draw(SDL_Renderer *renderer)
{ // Je pense que vous allez faire moins laid :)
    SDL_Rect rectangle;

    SDL_SetRenderDrawColor(renderer,
                           50, 0, 0, // mode Red, Green, Blue (tous dans 0..255)
                           255);     // 0 = transparent ; 255 = opaque
    rectangle.x = 0;                 // x haut gauche du rectangle
    rectangle.y = 0;                 // y haut gauche du rectangle
    rectangle.w = 400;               // sa largeur (w = width)
    rectangle.h = 400;               // sa hauteur (h = height)

    SDL_RenderFillRect(renderer, &rectangle);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer,
                       0, 0,      // x,y du point de la première extrémité
                       400, 400); // x,y seconde extrémité
*/
    /* tracer un cercle n'est en fait pas trivial, voilà le résultat sans algo intelligent ... 
    for (float angle = 0; angle < 2 * M_PI; angle += M_PI / 4000)
    {
        SDL_SetRenderDrawColor(renderer,
                               (cos(angle * 2) + 1) * 255 / 2, // quantité de Rouge
                               (cos(angle * 5) + 1) * 255 / 2, //          de vert
                               (cos(angle) + 1) * 255 / 2,     //          de bleu
                               255);                           // opacité = opaque
        SDL_RenderDrawPoint(renderer,
                            200 + 100 * cos(angle),  // coordonnée en x
                            200 + 150 * sin(angle)); //            en y
    }
}*/

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    SDL_Window
        *window_1 = NULL;
    SDL_Renderer
        *renderer1 = NULL,
        *renderer2 = NULL;

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n",
                SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }
    window_1 = SDL_CreateWindow(
        "Fenetre",             // codage en utf8, donc accents possibles
        0, 0,                  // coin haut gauche en haut gauche de l'écran
        1920, 1080,            // largeur = 400, hauteur = 300
        SDL_WINDOW_RESIZABLE); // redimensionnable

    renderer1 = SDL_CreateRenderer(window_1, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
    if (renderer1 == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        /* faire ce qu'il faut pour quitter proprement */
    }

    /* couleur de fond */
    SDL_SetRenderDrawColor(renderer1, 0, 0, 0, 0);
    SDL_RenderClear(renderer1);

    /* afficher à l'ecran */
    SDL_RenderPresent(renderer1);

    SDL_SetRenderDrawColor(renderer2, 255, 0, 0, 255);
    SDL_RenderDrawPoint(renderer2, 50, 50);
    SDL_RenderPresent(renderer2);

    if (window_1 == NULL)
    {
        SDL_Log("Error : SDL window X creation - %s\n",
                SDL_GetError()); // échec de la création de la fenêtre
        SDL_Quit();              // On referme la SDL
        exit(EXIT_FAILURE);
    }

    SDL_Delay(50000); // Pause exprimée  en ms

    /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
    SDL_DestroyRenderer(renderer2);
    SDL_DestroyRenderer(renderer1);
    SDL_DestroyWindow(window_1);

    SDL_Quit(); // la SDL

    return 0;
}

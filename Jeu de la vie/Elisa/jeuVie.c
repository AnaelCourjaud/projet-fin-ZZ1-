#include "jeuVie.h"

void affichage(int grille[HAUTEUR][LARGEUR], SDL_Renderer *renderer)
{
    int i; int j;

    for(i=0;i<HAUTEUR;i++){
        for(j=0;j<LARGEUR;j++){
            SDL_Rect rect = {40*j, 40*i+65, 40, 40};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            if(grille[i][j] == 0){  
                SDL_RenderDrawRect(renderer, &rect);    
            }
            else{
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}
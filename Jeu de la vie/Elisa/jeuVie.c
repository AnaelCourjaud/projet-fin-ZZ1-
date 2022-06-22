#include "jeuVie.h"

void affichage(int grille[HAUTEUR][LARGEUR], SDL_Renderer *renderer)
{
    int i; int j;

    for(i=0;i<HAUTEUR;i++){
        for(j=0;j<LARGEUR;j++){
            SDL_Rect rect = {40*j, 40*i, 40, 40};
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

void creationTexte(char texte[], SDL_Renderer *renderer, int taille, int x, int y, int opacite){

    TTF_Font* font = NULL;                                               // la variable 'police de caractère'
    font = TTF_OpenFont("font.ttf", taille);                     // La police à charger, la taille désirée
    if (font == NULL) fprintf(stderr, "Can't load font  %s\n", SDL_GetError()); 

    TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);           // en italique, gras

    SDL_Color color = {0, 0, 0, opacite}; 
    SDL_Surface* text_surface = NULL;                                    // la surface  (uniquement transitoire)
    text_surface = TTF_RenderText_Blended(font, texte, color); // création du texte dans la surface 
    if (text_surface == NULL) fprintf(stderr, "Can't create text surface %s\n", SDL_GetError());

    SDL_Texture* text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL) fprintf(stderr, "Can't create texture from surface %s\n", SDL_GetError());
    SDL_FreeSurface(text_surface);                                       // la texture ne sert plus à rien

    SDL_Rect pos = {x, y, 1000, 1000};                                         // rectangle où le texte va être prositionné
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);          // récupération de la taille (w, h) du texte 
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);
    SDL_DestroyTexture(text_texture);   
}
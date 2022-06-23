#include "affichage.h"

void creationTexte(char texte[], char style[], char police[], SDL_Renderer *renderer, int taille, int x, int y, int opacite)
{

    TTF_Font *font = NULL;                   // la variable 'police de caractère'
    font = TTF_OpenFont(police, taille); // La police à charger, la taille désirée
    if (font == NULL)
        fprintf(stderr, "Can't load font  %s\n", SDL_GetError());
    
    if(strcmp(style,"normal") == 0){ //si on veut le texte en style normal
    TTF_SetFontStyle(font, TTF_STYLE_NORMAL); }// en italique, gras TTF_STYLE_ITALIC | TTF_STYLE_BOLD

    if(strcmp(style,"surligne") == 0){ //si on veut le texte surligné
    TTF_SetFontStyle(font, TTF_STYLE_UNDERLINE); }

    SDL_Color color = {0, 0, 0, opacite};
    SDL_Surface *text_surface = NULL;                          // la surface  (uniquement transitoire)
    text_surface = TTF_RenderText_Blended(font, texte, color); // création du texte dans la surface
    if (text_surface == NULL)
        fprintf(stderr, "Can't create text surface %s\n", SDL_GetError());

    SDL_Texture *text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    if (text_texture == NULL)
        fprintf(stderr, "Can't create texture from surface %s\n", SDL_GetError());
    SDL_FreeSurface(text_surface); // la texture ne sert plus à rien

    SDL_Rect pos = {x, y, 1000, 1000};                          // rectangle où le texte va être prositionné
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);
    SDL_DestroyTexture(text_texture);
}

void creationImage(char nom[], SDL_Renderer *renderer, int longueur, int largeur, int x, int y){

    SDL_Texture  *texture;
    SDL_Surface *image = NULL;
    SDL_Rect rect;

    image=IMG_Load(nom);

    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    rect.x = x;
    rect.y = y;
    rect.w = longueur;
    rect.h = largeur;

    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
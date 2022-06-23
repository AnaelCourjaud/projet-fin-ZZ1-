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

void Animation(char nom[], char fond[], SDL_Renderer *renderer, SDL_Window *window, int longueur, int largeur, int x, int y,int nbimage, int ite)
{
    SDL_Texture  *texture;
    SDL_Surface *image = NULL;

    SDL_Rect
        source = {0},                             // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
        destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer


    image=IMG_Load(nom);

    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    SDL_Rect state[nbimage];                         // Tableau qui stocke les vignettes dans le bon ordre pour l'animation

    SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h); 
    int offset_x = source.w / nbimage,                // La largeur d'une vignette de l'image
        offset_y = source.h;

    /* construction des différents rectangles autour de chacune des vignettes de la planche */
    int i = 0;                                   
    for (int y = 0; y < source.h ; y += offset_y) {
    for (int x = 0; x < source.w; x += offset_x) {
      state[i].x = x;
      state[i].y = y;
      state[i].w = offset_x;
      state[i].h = offset_y;
      ++i;
    } 
    }

    for(; i< nbimage ; ++i){                  // reprise du début de l'animation en sens inverse  
        state[i] = state[nbimage-1-i];
    }
    destination.w = largeur;           // Largeur du sprite à l'écran
    destination.h = longueur;            // Hauteur du sprite à l'écran
    destination.x = x; // Position en x pour l'affichage du sprite
    destination.y = y;  // Position en y pour l'affichage du sprite

    ite = ite % nbimage;   
    creationImage(fond, renderer, 1920, 1080, 0, 0);
    SDL_RenderCopy(renderer, texture, &state[ite], &destination);

}

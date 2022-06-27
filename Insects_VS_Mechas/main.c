#include "initialisation.h"
#include "affichage.h"
//#include "affichageAttaque.h"
#include "general.h"

int main(int argc, char *argv[])
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;
    SDL_Rect tailleFenetre;

    SDL_Texture *texture[nbrTextures];
    TTF_Font *tabPolices[nbrPolices];

    // ************** Initialisation de la SDL  + gestion de l'échec possible *********
    // ********************************************************************************

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    // ***************************** Texte ********************************************

    if (TTF_Init() < 0)
        fprintf(stderr, "Unable to initialize TTF:  %s\n", SDL_GetError());

    // *************************  Gestion des fenetres   *****************************

    SDL_GetCurrentDisplayMode(0, &screen);
    tailleFenetre.w = screen.w * coefReducEcran; // réduction fenetre
    tailleFenetre.h = screen.h * coefReducEcran;

    //  ************************* Création de la fenêtre *************************

    window = SDL_CreateWindow("Insects_VS_Mechas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, tailleFenetre.w, tailleFenetre.h, SDL_WINDOW_RESIZABLE);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    //  ************************* Création du renderer *************************

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    // ********************************************************************************
    // ********************************************************************************

    init(window, renderer, texture, tabPolices);

    sprite_t fond;
    int nbrInsectesss = 3;

    // fond.source = {0};
    // fond.destination ={0};

insecte_t *tabInsectes[nbrInsectesss];

for(int i=0; i<nbrInsectesss;i++){
    insecte_t *insecte = malloc(sizeof(insecte_t));
    tabInsectes[i] = insecte;
}
    tabInsectes[0]->spriteInsecte.textureSprite = texture[indiceBugfirewalk];
    
    tabInsectes[0]->spriteInsecte.source.x = 0;
    tabInsectes[0]->spriteInsecte.source.y = 0;
SDL_QueryTexture(tabInsectes[0]->spriteInsecte.textureSprite, NULL, NULL,
                     &tabInsectes[0]->spriteInsecte.source.w, &tabInsectes[0]->spriteInsecte.source.h); 
        
  tabInsectes[0]->spriteInsecte.destination.x = 0;
    tabInsectes[0]->spriteInsecte.destination.y = 0;
    tabInsectes[0]->spriteInsecte.destination.w = 200;
    tabInsectes[0]->spriteInsecte.destination.h = 200;
    tabInsectes[0]->typeInsecte = BUGFIRE;

      tabInsectes[1]->spriteInsecte.textureSprite = texture[indiceFlyvollant];
    tabInsectes[1]->spriteInsecte.source.x = 0;
    tabInsectes[1]->spriteInsecte.source.y = 0;
SDL_QueryTexture(tabInsectes[1]->spriteInsecte.textureSprite, NULL, NULL,
                     &tabInsectes[1]->spriteInsecte.source.w, &tabInsectes[1]->spriteInsecte.source.h); 
  tabInsectes[1]->spriteInsecte.destination.x = 600;
    tabInsectes[1]->spriteInsecte.destination.y = 600;
    tabInsectes[1]->spriteInsecte.destination.w = 200;
    tabInsectes[1]->spriteInsecte.destination.h = 200;
    tabInsectes[1]->typeInsecte = FLY;


  tabInsectes[2]->spriteInsecte.textureSprite = texture[indiceMantiswalk];
    tabInsectes[2]->spriteInsecte.source.x = 0;
    tabInsectes[2]->spriteInsecte.source.y = 0;
SDL_QueryTexture(tabInsectes[2]->spriteInsecte.textureSprite, NULL, NULL,
                     &tabInsectes[2]->spriteInsecte.source.w, &tabInsectes[2]->spriteInsecte.source.h); 
  tabInsectes[2]->spriteInsecte.destination.x = 600;
    tabInsectes[2]->spriteInsecte.destination.y = 0;
    tabInsectes[2]->spriteInsecte.destination.w = 200;
    tabInsectes[2]->spriteInsecte.destination.h = 200;
    tabInsectes[2]->typeInsecte = MANTIS;

    //insecte_t tabInsectes[] = {insecte1, insecte2, insecte3};

    fond.textureSprite = texture[indiceFlyvollant];
    SDL_QueryTexture(fond.textureSprite, NULL, NULL,
                     &fond.source.w, &fond.source.h);

    fond.destination.x = 600;
    fond.destination.y = 600;
    fond.destination.w = 200;
    fond.destination.h = 200;
    fond.source.x = 0;
    fond.source.y = 0;

    // insecte_t scarabe1;
    //scarabe1.spriteInsecte = fond;
    //scarabe1.typeInsecte = BUGFIRE;

    /*
    SDL_Texture * textureSprite = IMG_LoadTexture(renderer, "./Sprites/fondaccueil.png");
        SDL_Rect source ={0} ,destination = {0};

         SDL_QueryTexture(textureSprite, NULL, NULL,
                         &source.w, &source.h);

                         source.x = 20;
        source.y = 20;
        //source.w = 1000;
        //source.h = 1000;
        destination.x = 20;
        destination.y = 20;
        destination.w = 200;
        destination.h = 200;
    */
    SDL_SetRenderDrawColor(renderer, 50, 0, 0, 255); // mode Red, Green, Blue (tous dans 0..255)
    // SDL_RenderClear(renderer);

    printf("avant copy\n");
     SDL_RenderCopy(renderer, fond.textureSprite, &fond.source, &fond.destination);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawLine(renderer,
                       0, 0, // x,y du point de la première extrémité
                       400, 400);
    for(int i=0;i<1;i++){
SDL_RenderCopy(renderer, tabInsectes[i]->spriteInsecte.textureSprite, &tabInsectes[i]->spriteInsecte.source, &tabInsectes[i]->spriteInsecte.destination);
    
    }
    // printf("0==0 : %d  et %d", 0==0, scarabe1.typeInsecte!=SCARAB);
    //SDL_RenderCopy(renderer, tabInsectes[i].spriteInsecte.textureSprite, &tabInsectes[i].spriteInsecte.source, &tabInsectes[i].spriteInsecte.destination);
    SDL_RenderPresent(renderer);
    printf("avant délai\n");
    SDL_Delay(3000);
    printf("après délai\n");
    // SDL_DestroyTexture(textureSprite);

    // SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
    //   SDL_Event event;                // c'est le type IMPORTANT !!

    /*
        SDL_Texture *sprite1;
        SDL_Texture *sprite2;
        SDL_Texture *textureFond;

        SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
        SDL_Event event;                // c'est le type IMPORTANT !!

        int ETATJEU = ACCUEIL;
        int i = 0;
        int j=0;

        sprite_t fondAccueil;
        sprite_t lore1;
        sprite_t lore2;
        sprite_t lore3;



        while (program_on)
        {
            // Voilà la boucle des évènements
            int interessant = 0;
            int choixFait = 0;

            // *************************  Gestion des evenements *****************************
            //
            // *******************************************************************************

            while ((interessant == 0) && (SDL_PollEvent(&event)))
            {   // tant que la file d'évènements n'est pas vide : défiler l'élément en tête et l'on a pas d'évènements interessants à traiter
                // de file dans 'event'
                switch (event.type)
                {
                case SDL_QUIT:
                    interessant = 1;        // Un évènement simple, on a cliqué sur la x de la fenêtre
                    program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                    break;
                case SDL_KEYUP: // Le type de event est : une touche lachée

                    switch (event.key.keysym.sym)
                    { // la touche appuyée est ...
                    case SDLK_SPACE:
                        if (ETATJEU == ACCUEIL)
                        {
                            ETATJEU = LORE1;
                        }
                        else if (ETATJEU == LORE1)
                        {
                            ETATJEU = LORE2;
                        }
                        else if (ETATJEU == LORE2)
                        {
                            ETATJEU = LORE3;
                        }
                        else if (ETATJEU == LORE3)
                        {
                            ETATJEU = JEU;
                        }
                        interessant = 1;
                    default:
                        break;
                    }

                default: // L'évènement défilé ne nous intéresse pas
                    break;
                }
            }
            interessant = 0;

            switch (ETATJEU)
            {
            case ERREUR:
                break;
            case ACCUEIL:

                fondAccueil.textureSprite = texture[indiceFondAccueil];
                creationFond(fondAccueil.textureSprite, window, renderer, 0, 0);
                break;
            case LORE1:
                lore1.textureSprite = texture[indiceLore1];
                creationFond(lore1.textureSprite, window, renderer, 0, 0);

                break;
            case LORE2:
                lore2.textureSprite = texture[indiceLore2];
                creationFond(lore2.textureSprite, window, renderer, 0, 0);

                break;
            case LORE3:
                lore3.textureSprite = texture[indiceLore3];
                creationFond(lore3.textureSprite, window, renderer, 0, 0);


                break;
            case JEU:
                printf("Jeu en route");

                break;
            default:
                ETATJEU = ERREUR;
                break;
            }

            SDL_RenderPresent(renderer);
            SDL_Delay(150);
        }*/

    end_sdl(1, "FIN NORMALE", window, renderer);
    return 0;
}
#include "initialisation.h"
#include "affichage.h"
//#include "affichageAttaque.h"
#include "general.h"
#include "vague.h"

int main(int argc, char *argv[])
{ 

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;
    SDL_Rect tailleFenetre;

    TTF_Font *tabPolices[nbrPolices];

    spriteBase_t *spritesDeBase[NBRTEXTURES];
    spriteCourant_t *listeCourants[tailleMaxSpritesCourants]; // le maximum de sprites courants à afficher
    combattant_t *listeCombattants[NBRMAXCOMBATTANTS];

    int listeCompo[20][3] = {{BUGFIRE,NULL,NULL}, {FLY, NULL, NULL}, {MANTIS, NULL, NULL},
    {BUGFIRE,BUGFIRE,NULL}, {FLY, FLY, NULL}, {MANTIS, MANTIS, NULL}, {BUGFIRE,FLY,NULL}, {BUGFIRE,MANTIS,NULL}, {FLY, MANTIS, NULL},
    {BUGFIRE,BUGFIRE,BUGFIRE}, {FLY, FLY, FLY}, {MANTIS, MANTIS, MANTIS},
    {BUGFIRE,BUGFIRE,FLY}, {BUGFIRE,BUGFIRE,MANTIS}, {FLY, FLY, BUGFIRE}, {FLY, FLY, MANTIS}, {MANTIS, MANTIS, BUGFIRE}, {MANTIS, MANTIS, FLY}, {BUGFIRE,FLY,MANTIS}};


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
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer, listeCourants);

    //  ************************* Création du renderer *************************

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer, listeCourants);

    // ********************************************************************************
    // ********************************************************************************

    init(window, renderer, tabPolices, spritesDeBase, listeCourants, listeCombattants);
/*
    for (int i = 0; i < tailleMaxSpritesCourants; i++)
    {
        spriteCourant_t *courant = malloc(sizeof(spriteCourant_t));
        listeCourants[i] = courant;
    }
    */

    // on va initialiser que les deux premiers car trop long sinon

listeCourants[0] = malloc(sizeof(spriteCourant_t));
listeCourants[1] = malloc(sizeof(spriteCourant_t));

    listeCourants[0]->spriteDeBase = spritesDeBase[indiceFond];
    listeCourants[0]->numImageEnCours = 0;
    listeCourants[0]->retardateurRalenti = listeCourants[0]->spriteDeBase->ralenti;

    listeCourants[1]->spriteDeBase = spritesDeBase[indicePasserelleFinie];

    SDL_Rect window_dimensions = {0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h); // Récupération des dimensions de la fenêtre

    listeCourants[0]->source.x = 0;
    listeCourants[0]->source.y = 0;
    listeCourants[0]->source.w = 0;
    listeCourants[0]->source.h = 0; // Rectangle définissant la zone de la texture à récupérer
    // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
    listeCourants[0]->destination.x = 0;
    listeCourants[0]->destination.y = 0;
    listeCourants[0]->destination.w = window_dimensions.w;
    listeCourants[0]->destination.h = window_dimensions.h; // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_QueryTexture(listeCourants[0]->spriteDeBase->textureSprite, NULL, NULL, &listeCourants[0]->source.w, &listeCourants[0]->source.h);

    listeCourants[0]->source.w = listeCourants[0]->source.w / listeCourants[0]->spriteDeBase->nbrImagesHorizontales;
    listeCourants[0]->source.h = listeCourants[0]->source.h / listeCourants[0]->spriteDeBase->nbrImagesVerticales;

    listeCourants[1]->source.x = 0;
    listeCourants[1]->source.y = 0;
    listeCourants[1]->source.w = 0;
    listeCourants[1]->source.h = 0; // Rectangle définissant la zone de la texture à récupérer
    // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
    listeCourants[1]->destination.x = 0;
    listeCourants[1]->destination.y = 0;
    listeCourants[1]->destination.w = window_dimensions.w;
    listeCourants[1]->destination.h = window_dimensions.h; // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_QueryTexture(listeCourants[1]->spriteDeBase->textureSprite, NULL, NULL, &listeCourants[1]->source.w, &listeCourants[1]->source.h);

    // listeCourants[1]->source.w = listeCourants[1]->source.w / listeCourants[1]->spriteDeBase->nbrImagesHorizontales;
    // listeCourants[1]->source.h = listeCourants[1]->source.h / listeCourants[1]->spriteDeBase->nbrImagesVerticales;

//creationVague(spritesDeBase, listeCombattants, listeCourants);
printf("fin creation vague\n");

printf("0 == 0 : %d\n", 0 == 0);

for(int i=0;i<tailleMaxSpritesCourants;i++){
    printf("listeCourrants[%d] == NULL : %d\n",i,listeCourants[i]==NULL);
}

int azer=0;
while(listeCourants[azer] != NULL){
    printf("%d\n",azer);
    azer++;
}

    int repet = 0;
    while (repet < 200)
    {
        repet++;

        animation(window, renderer, listeCourants);

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        printf("avant délai\n");
        SDL_Delay(30);
        // printf("après délai %d\n",fond->numImageEnCours);
        printf(" repet : %d",repet);
    }

    /*
        SDL_Texture *sprite1;
        SDL_Texture *sprite2;
        SDL_Texture *textureFond;

        SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
        SDL_Event event;                // c'est le type IMPORTANT !!

        int ETATJEU = ACCUEIL;
        /*
        int i = 0;
        int j=0;

        sprite_t fondAccueil;
        sprite_t lore1;
        sprite_t lore2;
        sprite_t lore3;

*/
/*
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
                        ETATJEU = VAGUE;
                    }

                default: // L'évènement défilé ne nous intéresse pas
                    break;
                }
            interessant = 0;
                }
            


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
        case VAGUE:
            printf("Jeu en route");

            break;
        case ATTENTERIPOSTE:

            break;
        case RIPOSTE:

            break;
        case FINDEVAGUE:

            break;
        case FINJEU:

            break;
        default:
            ETATJEU = ERREUR;
            break;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(150);
    }
    }
*/

    end_sdl(1, "FIN NORMALE", window, renderer, listeCourants);
    return 0;
}
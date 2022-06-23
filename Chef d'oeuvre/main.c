#include "resolution.h"
#include "affichage.h"
#include "affichageAttaque.h"


#define ligneTexture 2
#define colonneTexture 9
#define nombreFichier 18
#define tailleMaxFichiers 50

#define nbrImageSpriteFini 10

int main(int argc, char *argv[])
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;
    SDL_Rect tailleFenetre;

    /************** Initialisation de la SDL  + gestion de l'échec possible *********/
    /*                                                                              */
    /********************************************************************************/

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n",
                SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    /***************************** Texte ********************************************/
    /*                                                                              */
    /********************************************************************************/

    /*****Initialisation*****/

    if (TTF_Init() < 0)
     fprintf(stderr, "Unable to initialize TTF:  %s\n", SDL_GetError());

    /*************************  Gestion des fenetres   *****************************/
    /*                                                                             */
    /*******************************************************************************/

    // SDL_DisplayMode screen;
    SDL_GetCurrentDisplayMode(0, &screen);
    tailleFenetre.w = screen.w * 1.0; //réduction fenetre
    tailleFenetre.h = screen.h * 1.0;
    printf("Résolution écran\n\tw : %d\n\th : %d\n",
           screen.w, screen.h);
    printf("Résolution fenetre\n\tw : %d\n\th : %d\n",
           tailleFenetre.w, tailleFenetre.h);

    // SDL_Window *window = NULL;
    // SDL_Renderer *renderer = NULL;

    /*tailleFenetre.x = screen.w;
    tailleFenetre.y = screen.h;
    printf("Résolution écran\n\tw : %d\n\th : %d\n",
           screen.w, screen.h);
    printf("Pour fermer : cliquer sur la croix, ou alors 'q' ou alors 'ESCAPE'. Bon trip !\n");*/

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Jeu de l'ambiance",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              tailleFenetre.w, tailleFenetre.h,
                              SDL_WINDOW_OPENGL);
    if (window == NULL)
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /*************************  Gestion des evenements *****************************/
    /*                                                                             */
    /*******************************************************************************/

/////////////// récupération des textures et stockage dans tableau
   SDL_Texture *texture[ligneTexture][colonneTexture];
    char nomFichiers[ligneTexture][colonneTexture][tailleMaxFichiers] = {{"./Sprites/attaqueeau.png", "./Sprites/attaquefeu.png", "./Sprites/attaquepierre.png", "./Sprites/defense.png","./Sprites/attente.png","./Sprites/persobase.png","./Sprites/victoire.png","./Sprites/defaite.png","./Sprites/fond1.jpg"},
 {"./Sprites/attaqueeauennemi.png", "./Sprites/attaquefeuennemi.png", "./Sprites/attaquepierreennemi.png", "./Sprites/defenseennemi.png","./Sprites/attenteennemi.png","./Sprites/ennemibase.png","./Sprites/victoireennemi.png","./Sprites/defaiteennemi.png","./Sprites/fond2.jpg"}};
    for (int i = 0; i < ligneTexture; i++)
    {
        for (int j = 0; j < colonneTexture; j++)
        {
            texture[i][j] = IMG_LoadTexture(renderer, nomFichiers[i][j]);
            if (texture[i][j] == NULL)
                end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
        }
    }

////////:::////

   // int nbCycleMax=10;
    //int cycleActuel=0;

    SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
    SDL_Event event;                // c'est le type IMPORTANT !!
/*
    SDL_Point 
                indicesSprite1 = {0},
                indicesSprite2 = {0},
                indicesFond = {0};
*/
    SDL_Texture *sprite1;
    SDL_Texture *sprite2;
    SDL_Texture *textureFond;

    int nbrImageSprite1;
    int nbrImageSprite2;
    int animationFinieTerminee = 1;

    int ETATJEU = ACCUEIL;
    int i = 0;
    int j=0;

    int PV[2] = {1, 1};
    int etat[2] = {EAU, EAU};

    while (program_on)
    {
        // Voilà la boucle des évènements
        int interessant = 0;
        //int changerEtat = 0;
        int choixFait = 0;
        int etatPrec;

        while ((interessant == 0) && (SDL_PollEvent(&event)))
        {   // tant que la file d'évènements n'est pas vide : défiler l'élément en tête et l'on a pas d'évènements interessants à traiter
            // de file dans 'event'
            switch (event.type)
            { // En fonction de la valeur du type de cet évènement
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
                        ETATJEU = JEU;
                        i=0;
                        j=0;
                    }
                    interessant = 1;
                    break;
                case SDLK_q:
                    if(animationFinieTerminee ==1){
                        if (ETATJEU == JEU)
                        {
                            ETATJEU = ACCUEIL;
                        }
                        interessant = 1;
                    }
                case SDLK_r:
                    if(animationFinieTerminee ==1){
                        if (ETATJEU == FINJEU)
                        {
                            ETATJEU = ACCUEIL;
                        }
                        interessant = 1;
                    }
                    break;
                case SDLK_e:
                    if(animationFinieTerminee ==1){
                    etat[0] = 0;
                    choixFait = 1;
                    interessant = 1;
                    }
                    break;
                case SDLK_f:
                    if(animationFinieTerminee ==1){
                    etat[0] = 1;
                    choixFait = 1;
                    interessant = 1;
                    }
                    break;
                case SDLK_t:
                    if(animationFinieTerminee ==1){
                    etat[0] = 2;
                    choixFait = 1;
                    interessant = 1;
                    }
                    break;
                case SDLK_d:
                    if(animationFinieTerminee ==1){
                    etatPrec = etat[0];
                    etat[0] = 3;
                    choixFait = 1;
                    interessant = 1;
                    }
                    break;
                default:
                    break;
                }

            default: // L'évènement défilé ne nous intéresse pas
                break;
            }
        }
        interessant = 0;
           // cycleActuel++;
            //if(cycleActuel>nbCycleMax){
        switch (ETATJEU)
        {
        case ERREUR:
            break;
        case ACCUEIL:
            /*SDL_SetRenderDrawColor(renderer, 0, 145, 255, 255);
            SDL_RenderClear(renderer);*/
            SDL_RenderClear(renderer);
            creationImage(texture[0][8],window, renderer, tailleFenetre.w, tailleFenetre.h, 0, 0);

            creationTexte("Bienvenue :", "normal", "./fonts/font.ttf", renderer, 100, 600, 100, 255);
            creationTexte("Commandes :", "surligne", "./fonts/font2.ttf", renderer, 90, 400, 300, 255);
            creationTexte("E pour attaque eau", "normal", "./fonts/font2.ttf", renderer, 90, 500, 450, 255);
            creationTexte("F pour attaque feu", "normal", "./fonts/font2.ttf", renderer, 90, 500, 550, 255);
            creationTexte("T pour attaque terre", "normal", "./fonts/font2.ttf", renderer, 90, 500, 650, 255);
            creationTexte("D pour defense", "normal", "./fonts/font2.ttf", renderer, 90, 500, 750, 255);
            creationTexte("Q pour revenir ici", "normal", "./fonts/font2.ttf", renderer, 90, 500, 850, 255);

            break;
        case JEU:
            // SDL_RenderClear(renderer);
            // creationImage("./Sprites/fond2.jpg", renderer, 1920, 1080, 0, 0);


            //SDL_Texture *sprite1 = texture[0][1];
            //SDL_Texture *sprite2 = texture[0][2];
            //SDL_Texture *fond = texture[0][3];
            if(choixFait ==1){
                changementEtatEnnemi(etat);
                reussitedefense(etat, etatPrec);
                int resultat = gagnant(etat);
                resolutionPV(PV, resultat, etat);
                sprite1 = textureAttaque(texture,0, etat, resultat);
                sprite2 = textureAttaque(texture,1, etat, resultat);

                choixFait = 0;
                animationFinieTerminee = 0;
                i=0;
            }

            if(i >= nbrImageSpriteFini && animationFinieTerminee == 0){
                animationFinieTerminee = 1;
                i=0;
            }

            if(animationFinieTerminee == 1){
                sprite1 = texture[0][5];
                sprite2 = texture[1][5];

            }

            for(int i=0;i<ligneTexture;i++){
                for(int j=0;j<colonneTexture;j++){
                    if(sprite1 == texture[i][j]){
                        if(j==0 || j==1 || j==2 || j==3 || j==4){
                            nbrImageSprite1=10;
                        }else if(j==5 || j==6){
                            nbrImageSprite1=2;
                        }else{
                            nbrImageSprite1=3;
                        }
                    }
                    if(sprite2 == texture[i][j]){
                        if(j==0 || j==1 || j==2 || j==3 || j==4){
                            nbrImageSprite2=10;
                        }else if(j==5 || j==6){
                            nbrImageSprite2=2;
                        }else{
                            nbrImageSprite2=3;
                        }
                    }
               }
            }


            textureFond= texture[1][8];
            int nbrImageFond = 1;

            printf("justeAvant animation\n");
            printf(" textures égales : %d\n", texture[0][5] == texture[0][4]);
            //Animation(sprite1, sprite2, textureFond, renderer, window, 400, 400, 200, 1300, 500, nbrImageSprite1,nbrImageSprite2, i);
            Animation(sprite1, sprite2, textureFond, renderer, window, 400, 400, 200, 1300, 500, nbrImageSprite1,nbrImageSprite2, nbrImageFond, i, j);
            printf("justeAprès animation\n");
            i++;
            j++;
            //Animation(sprite1, sprite2, textureFond, renderer, window, 400, 400, 200, 1300, 500, nbrImageSprite1,nbrImageSprite2, i);


            if(((PV[0] <= 0)||(PV[1] <= 0))&&(animationFinieTerminee == 1 )){
                ETATJEU = FINJEU;
            }
            
            /*animationFinieTerminee = 0;
         

            int nbrImageSprite1 = 2;
            int nbrImageSprite2 = 2;


            Animation(texture[indicesSprite1.x][indicesSprite1.y], texture[indicesSprite2.x][indicesSprite2.y], texture[indicesFond.x][indicesFond.y], renderer, window, 400, 400, 200, 1300, 500, nbrImageSprite1,nbrImageSprite2, i);
            i++;
            */
           
            /*SDL_RenderClear(renderer);
            creationImage("fond.jpg", renderer, 1920, 1080, 0, 0);*/

            break;
        case FINJEU:
            if(PV[1] <=0 ){
                sprite1 = texture[0][6];
                sprite2 = texture[1][7];
                nbrImageSprite1=2;
                nbrImageSprite2=3;
            }
            if(PV[0] <=0 ){
                sprite1 = texture[1][7];
                sprite2 = texture[0][6];
                nbrImageSprite1=3;
                nbrImageSprite2=2;
            }
            Animation(sprite1, sprite2, textureFond, renderer, window, 400, 400, 200, 1300, 500, nbrImageSprite1,nbrImageSprite2,1, i,j);
            i++;
            break;
        default:
            ETATJEU = ERREUR;
            break;
        }
        //cycleActuel=0;
          //  }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(150);
    }

   end_sdl(1, "FIN NORMALE", window, renderer);
    return 0;
}
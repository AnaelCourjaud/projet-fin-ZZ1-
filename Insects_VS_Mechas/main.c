#include "initialisation.h"
#include "affichage.h"
// #include "general.h"
#include "gestionObjets.h"
#include "riposte.h"
#include "resolutionNulle.h"
#include "apprentissage.h"
#include "analyseVague.h"

int main()
{
    srand(time(NULL));

    int listeCompo[20][3] = {{BUGFIRE, -1, -1}, {FLY, -1, -1}, {MANTIS, -1, -1}, {BUGFIRE, BUGFIRE, -1}, {FLY, FLY, -1}, {MANTIS, MANTIS, -1}, {BUGFIRE, FLY, -1}, {BUGFIRE, MANTIS, -1}, {FLY, MANTIS, -1}, {BUGFIRE, BUGFIRE, BUGFIRE}, {FLY, FLY, FLY}, {MANTIS, MANTIS, MANTIS}, {BUGFIRE, BUGFIRE, FLY}, {BUGFIRE, BUGFIRE, MANTIS}, {BUGFIRE, FLY, FLY}, {FLY, FLY, MANTIS}, {BUGFIRE, MANTIS, MANTIS}, {FLY, MANTIS, MANTIS}, {BUGFIRE, FLY, MANTIS}};

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;
    SDL_Rect tailleFenetre;

    TTF_Font *tabPolices[nbrPolices];

    spriteBase_t *spritesDeBase[NBRTEXTURES];
    spriteCourant_t *listeCourants[tailleMaxSpritesCourants]; // le maximum de sprites courants à afficher
    combattant_t *listeCombattants[NBRMAXCOMBATTANTS];

    // int listeCompo[20][3] = {{BUGFIRE, NULL, NULL}, {FLY, NULL, NULL}, {MANTIS, NULL, NULL}, {BUGFIRE, BUGFIRE, NULL}, {FLY, FLY, NULL}, {MANTIS, MANTIS, NULL}, {BUGFIRE, FLY, NULL}, {BUGFIRE, MANTIS, NULL}, {FLY, MANTIS, NULL}, {BUGFIRE, BUGFIRE, BUGFIRE}, {FLY, FLY, FLY}, {MANTIS, MANTIS, MANTIS}, {BUGFIRE, BUGFIRE, FLY}, {BUGFIRE, BUGFIRE, MANTIS}, {FLY, FLY, BUGFIRE}, {FLY, FLY, MANTIS}, {MANTIS, MANTIS, BUGFIRE}, {MANTIS, MANTIS, FLY}, {BUGFIRE, FLY, MANTIS}};

    // ************** Initialisation de la SDL  + gestion de l'échec possible *********
    // ********************************************************************************

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); // l'initialisation de la SDL a échoué
        exit(EXIT_FAILURE);
    }

    //************************ Chargement musique *************************************

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    /* Chargement musique */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    Mix_Music *accueil = Mix_LoadMUS("./Musiques/accueil.mp3");
    Mix_Music *lore1 = Mix_LoadMUS("./Musiques/lore1.mp3");
    Mix_Music *lore2 = Mix_LoadMUS("./Musiques/lore2.mp3");
    Mix_Music *lore3 = Mix_LoadMUS("./Musiques/lore3.mp3");
    Mix_Music *jeu = Mix_LoadMUS("./Musiques/jeu.mp3");

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
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer, spritesDeBase, listeCourants);

    //  ************************* Création du renderer *************************

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer, spritesDeBase, listeCourants);

    // ********************************************************************************
    // ********************************************************************************

    init(window, renderer, tabPolices, spritesDeBase, listeCourants, listeCombattants);

    SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
    SDL_Event event;                // c'est le type IMPORTANT !!

    // ETATJEU = ACCUEIL;
    int ETATJEU = ACCUEIL;
    int changermusique = 1;
    int compteurAnimationMort = 0;
    int nombreInsectesMorts = 0;
    int numeroDeVague = 0;
    int compteurDeCoups = 0;
    int train = 1;

    // Initialisation ia
    float tableQ[NBPERCEPTION][NBDEFENSES];
    initTableQ(tableQ);

    int tablesauv[2][NBPERCEPTION] ;

    float epsilon = 1.0;
    float gamma = 0.5;

    
    creerSpriteCourant(spritesDeBase, listeCourants, indiceFondAccueil, 0.0, 0.0);

    while (program_on)
    {
        // Voilà la boucle des évènements
        int interessant = 0;
        // int choixFait = 0;

        // *************************  Gestion des evenements *****************************
        //
        // *******************************************************************************

        while ((interessant == 0) && (SDL_PollEvent(&event)))
        { // tant que la file d'évènements n'est pas vide : défiler l'élément en tête et l'on a pas d'évènements interessants à traiter
            // de file dans 'event'
            switch (event.type)
            {
            case SDL_QUIT:
                interessant = 1;        // Un évènement simple, on a cliqué sur la x de la fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;
            case SDL_KEYUP: // Le type de event est : une touche relâchée

                switch (event.key.keysym.sym)
                { // la touche appuyée est ...
                case SDLK_ESCAPE:
                    interessant = 1;
                    program_on = SDL_FALSE;
                    break;
                case SDLK_SPACE:
                    if (ETATJEU == ACCUEIL)
                    {
                        cleanListeCourants(listeCourants);
                        creerSpriteCourant(spritesDeBase, listeCourants, indiceLore1, 0.0, 0.0);
                        numeroDeVague = 0;
                        ETATJEU = LORE1;
                    }
                    else if (ETATJEU == LORE1)
                    {
                        cleanListeCourants(listeCourants);
                        creerSpriteCourant(spritesDeBase, listeCourants, indiceLore2, 0.0, 0.0);
                        ETATJEU = LORE2;
                    }
                    else if (ETATJEU == LORE2)
                    {
                        cleanListeCourants(listeCourants);
                        creerSpriteCourant(spritesDeBase, listeCourants, indiceLore3, 0.0, 0.0);
                        ETATJEU = LORE3;
                    }
                    else if (ETATJEU == LORE3)
                    {
                        cleanListeCourants(listeCourants);
                        cleanListeCombattants(listeCombattants);
                        creerSpriteCourant(spritesDeBase, listeCourants, indiceFond, 0.0, 0.0);
                        creerSpriteCourant(spritesDeBase, listeCourants, indicePasserelleAnimee, 0.0, 0.0);
                        creerSpriteCourant(spritesDeBase, listeCourants, indiceBatiment2, -0.12, 0.27);
                        creationVague(spritesDeBase, listeCombattants, listeCourants);
                        numeroDeVague++;
                        ETATJEU = ARRIVEEVAGUE;
                    }
                    interessant = 1;
                    changermusique = 1;
                    break;
                case SDLK_q:

                    if (ETATJEU != ACCUEIL)
                    {
                        cleanListeCombattants(listeCombattants);
                        cleanListeCourants(listeCourants);
                        creerSpriteCourant(spritesDeBase, listeCourants, indiceFondAccueil, 0.0, 0.0);
                        ETATJEU = ACCUEIL;
                    }
                    interessant = 1;
                    changermusique = 1;
                    break;
                case SDLK_g:
                    if (train == 0)
                    {
                        if (ETATJEU == ATTENTECHOIXRIPOSTE)
                        {
                            // cleanListeCombattants(listeCombattants);
                            // cleanListeCourants(listeCourants);
                            // creerSpriteCourant(spritesDeBase, listeCourants, indiceFondAccueil, 0.0, 0.0);
                            creerAttaquant(spritesDeBase, listeCourants, listeCombattants, ROBOTGROS, WALK, NBENNEMIVAGUE, xSponeDefenseur, ySponeDefenseur);
                            compteurDeCoups++;
                            ETATJEU = ARRIVEERIPOSTE;
                        }
                        interessant = 1;
                    }
                    break;
                case SDLK_p:
                    if (train == 0)
                    {
                        if (ETATJEU == ATTENTECHOIXRIPOSTE)
                        {
                            creerAttaquant(spritesDeBase, listeCourants, listeCombattants, ROBOTPETIT, WALK, NBENNEMIVAGUE, xSponeDefenseur, ySponeDefenseur);
                            compteurDeCoups++;
                            ETATJEU = ARRIVEERIPOSTE;
                        }
                        interessant = 1;
                    }
                    break;
                case SDLK_m:
                    if (train == 0)
                    {
                        if (ETATJEU == ATTENTECHOIXRIPOSTE)
                        {
                            creerAttaquant(spritesDeBase, listeCourants, listeCombattants, ROBOTMETAL, WALK, NBENNEMIVAGUE, xSponeDefenseur, ySponeDefenseur);
                            compteurDeCoups++;
                            ETATJEU = ARRIVEERIPOSTE;
                        }
                        interessant = 1;
                    }
                    break;
                // case SDLK_t:
                //     if (ETATJEU == ACCUEIL)
                //     {
                //         cleanListeCombattants(listeCombattants);
                //         // ETATJEU = TRAIN;
                //         interessant = 1;
                        
                //         for (int i = 1; i <= NBRVAGUESTRAIN; i++)
                //         {
                //             creationVague(spritesDeBase, listeCombattants, listeCourants);
                //             int estVide = 1;

                //             while (estVide == 1)
                //             {
                //                 int perception = reconnaitreCompo(listeCompo, listeCombattants);
                //                 // int ordreIA = preferenceLearning(perception, tableQ, epsilon);
                //                 int compteurdeCoupsIA = 0;
                //                 // switch (ordreIA)
                //                 {
                //                 case ROBOTGROS:
                //                     creerAttaquant(spritesDeBase, listeCourants, listeCombattants, ROBOTGROS, WALK, NBENNEMIVAGUE, xSponeDefenseur, ySponeDefenseur);
                //                     compteurdeCoupsIA++;
                //                     break;
                //                 case ROBOTMETAL:
                //                     creerAttaquant(spritesDeBase, listeCourants, listeCombattants, ROBOTMETAL, WALK, NBENNEMIVAGUE, xSponeDefenseur, ySponeDefenseur);
                //                     compteurdeCoupsIA++;
                //                     break;
                //                 case ROBOTPETIT:
                //                     creerAttaquant(spritesDeBase, listeCourants, listeCombattants, ROBOTPETIT, WALK, NBENNEMIVAGUE, xSponeDefenseur, ySponeDefenseur);
                //                     compteurdeCoupsIA++;
                //                     break;
                //                 }
                //                 applicationDegats(listeCombattants);
                //                 for (int j = 0; j < NBRMAXCOMBATTANTS; j++)
                //                 {
                //                     if (listeCombattants[j] != NULL)
                //                     {
                //                         if (listeCombattants[j]->typeCombattant >= ROBOTGROS && listeCombattants[j]->typeCombattant <= ROBOTGROS + 2)
                //                         {
                //                             free(listeCombattants[j]);
                //                             listeCombattants[j] = NULL;
                //                         }
                //                         else
                //                         {
                //                             if (listeCombattants[j]->magieRestante <= 0 && listeCombattants[j]->physiqueRestant <= 0)
                //                             {
                //                                 free(listeCombattants[j]);
                //                                 listeCombattants[j] = NULL;
                //                             }
                //                         }
                //                     }
                //                 }
                //                 for (int j = 0; j < NBRMAXCOMBATTANTS; j++) // est-ce qu'il reste des combattants vivants ? si oui : nouvelle défense, si non : nouvelle vague
                //                 {
                //                     if (listeCombattants[j] != NULL)
                //                     {
                //                         estVide = 0;
                //                     }
                //                 }
                //             }
                //         }
                //     }
                //     break;
                default: // L'évènement défilé ne nous intéresse pas
                    break;
                }
            default:
                break;
            }
        }

        switch (ETATJEU)
        {
        case ERREUR:
            // printf("ETATJEU == ERREUR\n");
            break;
        case ACCUEIL:
            // printf("Accueil\n");
            if (changermusique == 1)
            {
                Mix_PlayMusic(accueil, -1);
            }
            animation(window, renderer, listeCourants);
            break;
        case LORE1:
            // printf("lore1\n");
            if (changermusique == 1)
            {
                Mix_PlayMusic(lore1, 0);
            }
            animation(window, renderer, listeCourants);
            break;
        case LORE2:
            // printf("lore2\n");
            if (changermusique == 1)
            {
                Mix_PlayMusic(lore2, 0);
            }
            animation(window, renderer, listeCourants);

            break;
        case LORE3:
            // printf("lore3\n");
            if (changermusique == 1)
            {
                Mix_PlayMusic(lore3, 0);
            }
            animation(window, renderer, listeCourants);

            break;
        case ARRIVEEVAGUE:
            // printf("ARRIVEEVAGUE\n");
            // printf("vague\n");
            if (changermusique == 1)
            {
                Mix_PlayMusic(jeu, -1);
            }
            animation(window, renderer, listeCourants);
            int attaquantsArrives = 0;
            attaquantsArrives = faireAvancerCombattants(listeCombattants, BUGFIRE);
            if (attaquantsArrives == 1)
            {
                switchEtatCombattants(spritesDeBase, listeCourants, listeCombattants, BUGFIRE, ATTAQUE);
                ETATJEU = ATTENTECHOIXRIPOSTE;
            }
            // listeCombattants[0]->spriteCourant->destination.x++;
            break;
        case ATTENTECHOIXRIPOSTE:
            if (train == 1)
            {
                int perception = reconnaitreCompo(listeCompo, listeCombattants);
                int ordreIA = preferencelearning(perception, tableQ, epsilon);
                printf("ordreIA:%d\n", ordreIA);

                //Sauvegardes des perceptions et des defenses
                tablesauv[0][compteurDeCoups] = perception;
                tablesauv[1][compteurDeCoups] = ordreIA;

                switch (ordreIA+3)
                {
                case ROBOTGROS:
                    creerAttaquant(spritesDeBase, listeCourants, listeCombattants, ROBOTGROS, WALK, NBENNEMIVAGUE, xSponeDefenseur, ySponeDefenseur);
                    compteurDeCoups++;
                    ETATJEU = ARRIVEERIPOSTE;
                    break;
                case ROBOTMETAL:
                    creerAttaquant(spritesDeBase, listeCourants, listeCombattants, ROBOTMETAL, WALK, NBENNEMIVAGUE, xSponeDefenseur, ySponeDefenseur);
                    compteurDeCoups++;
                    ETATJEU = ARRIVEERIPOSTE;
                    break;
                case ROBOTPETIT:
                    creerAttaquant(spritesDeBase, listeCourants, listeCombattants, ROBOTPETIT, WALK, NBENNEMIVAGUE, xSponeDefenseur, ySponeDefenseur);
                    compteurDeCoups++;
                    ETATJEU = ARRIVEERIPOSTE;
                    break;
                }
            }
            printf("attente riposte\n");
            animation(window, renderer, listeCourants);
            break;
        case ARRIVEERIPOSTE:
            // printf("ARRIVEERIPOSTE\n");
            animation(window, renderer, listeCourants);
            int defenseursArrives = 0;
            defenseursArrives = faireAvancerCombattants(listeCombattants, ROBOTGROS);
            if (defenseursArrives == 1)
            {
                switchEtatCombattants(spritesDeBase, listeCourants, listeCombattants, ROBOTGROS, ATTAQUE);
                compteurAnimationMort = 0;
                ETATJEU = ATTAQUESDEFENSEUR;
            }
            break;
        case ATTAQUESDEFENSEUR:
            // printf("attaques défenseur\n");
            if (compteurAnimationMort == NBRATTAQUESDEFENSEURAVANTMORT * listeCombattants[NBENNEMIVAGUE]->spriteCourant->spriteDeBase->nbrImagesHorizontales * listeCombattants[NBENNEMIVAGUE]->spriteCourant->spriteDeBase->nbrImagesVerticales * (listeCombattants[NBENNEMIVAGUE]->spriteCourant->spriteDeBase->ralenti + 1))
            {
                // résolution
                applicationDegats(listeCombattants);
                // degatInflige(listeCombattants);
                // switch etat mort
                nombreInsectesMorts = switchEtatCombattants(spritesDeBase, listeCourants, listeCombattants, BUGFIRE, MORT);
                switchEtatCombattants(spritesDeBase, listeCourants, listeCombattants, ROBOTGROS, MORT);
                ETATJEU = ANIMATIONMORT;
            }
            animation(window, renderer, listeCourants);
            compteurAnimationMort++;
            break;
        case ANIMATIONMORT:
            // printf("animation mort\n");
            // if (compteurAnimationMort == NBRATTAQUESDEFENSEURAVANTMORT * listeCombattants[NBENNEMIVAGUE]->spriteCourant->spriteDeBase->nbrImagesHorizontales * listeCombattants[NBENNEMIVAGUE]->spriteCourant->spriteDeBase->nbrImagesVerticales * (listeCombattants[NBENNEMIVAGUE]->spriteCourant->spriteDeBase->ralenti + 1))
            // {
            //     // résolution
            //     degatInflige(listeCombattants);
            //     // switch etat mort
            //     switchEtatCombattants(spritesDeBase, listeCourants, listeCombattants, BUGFIRE, MORT);
            //     switchEtatCombattants(spritesDeBase, listeCourants, listeCombattants, ROBOTGROS, MORT);
            // }
            animation(window, renderer, listeCourants);
            for (int i = 0; i < NBRMAXCOMBATTANTS; i++)
            {
                if (listeCombattants[i] != NULL)
                {
                    if (listeCombattants[i]->spriteCourant->animationTerminee == 1) // supprimer le combattant i
                    {
                        for (int j = 0; j < tailleMaxSpritesCourants; j++)
                        {
                            if (listeCourants[j] == listeCombattants[i]->spriteCourant)
                            {
                                free(listeCombattants[i]->spriteCourant);
                                listeCombattants[i]->spriteCourant = NULL;
                                listeCourants[j] = NULL;
                                // printf("sprite de combattant supprimé main\n");
                            }
                        }
                        free(listeCombattants[i]);
                        listeCombattants[i] = NULL;
                        nombreInsectesMorts--;
                    }
                }
            }
            if (nombreInsectesMorts < 0)
            {
                int nombreCombattantsExistants = 0;
                for (int i = 0; i < NBRMAXCOMBATTANTS; i++)
                {
                    if (listeCombattants[i] != NULL)
                    {
                        nombreCombattantsExistants++;
                    }
                }

                if (nombreCombattantsExistants == 0)
                {
                    gestionTable( tableQ, tablesauv, gamma, epsilon);

                    if (numeroDeVague < NBRDEVAGUES)
                    {
                        creationVague(spritesDeBase, listeCombattants, listeCourants);
                        numeroDeVague++;
                        ETATJEU = ARRIVEEVAGUE;
                    }
                    else
                    {
                        ETATJEU = FINDEVAGUE;
                    }
                }
                else
                {
                    ETATJEU = ATTENTECHOIXRIPOSTE;
                }
            }

            break;
        case FINDEVAGUE:
            // printf("fin de vague\n");
            animation(window, renderer, listeCourants);
            ETATJEU = FINJEU;
            break;
        case FINJEU:
            // printf("fin du jeu\n");
            cleanListeCourants(listeCourants);
            animation(window, renderer, listeCourants);
            break;
        default:
            ETATJEU = ERREUR;
            break;
        }

        changermusique = 0;

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(20);
        // printf(("hello\n"));
        // for (int i = 0; i < NBRMAXCOMBATTANTS; i++)
        // {
        //     printf("listeCombattants[%d] == %d\n", i, listeCombattants[i] == NULL);
        // }
    }

    // printf(" juste avant end_sdl\n");
    end_sdl(1, "FIN NORMALE", window, renderer, spritesDeBase, listeCourants);
    Mix_CloseAudio();
    return 0;
}
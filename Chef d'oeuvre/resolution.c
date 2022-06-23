#include "resolution.h"

int gagnant(int etat[2]){
    //0: perso gagne; 1:ennemi gagne; 2: meme attaque; 3 : au moins une defense
    int duel[4][4] = {{2,0,1,3},{1,2,0,3},{0,1,2,3},{3,3,3,2}};
    return duel[etat[0]][etat[1]];
}


void resolutionPV(int PV[], int resultat, int etat[]){
    int degat[3] = {2,3,1}; //degat des attaques eau, feu et terre
    if (resultat == 0){// si le perso a gagné
        PV[1] = PV[1] - degat[etat[0]];
    }
    if (resultat == 1){// si l'ennemi a gagné
        PV[0] = PV[0] - degat[etat[1]];
    }
    // si meme attaque ou si defense, pas de changemement de PV
}

void end_sdl(char ok,            // fin anormale : ok = 0 ; normale ok = 1
             char const *msg,    // message à afficher
             SDL_Window *window, // fenêtre à fermer
             SDL_Renderer *renderer)
{ // renderer à fermer
    char msg_formated[255];
    int l;

    if (!ok)
    { // Affichage de ce qui ne va pas
        strncpy(msg_formated, msg, 250);
        l = strlen(msg_formated);
        strcpy(msg_formated + l, " : %s\n");

        SDL_Log(msg_formated, SDL_GetError());
    }

    if (renderer != NULL)
    {                                  // Destruction si nécessaire du renderer
        SDL_DestroyRenderer(renderer); // Attention : on suppose que les NULL sont maintenus !!
        renderer = NULL;
    }
    if (window != NULL)
    {                              // Destruction si nécessaire de la fenêtre
        SDL_DestroyWindow(window); // Attention : on suppose que les NULL sont maintenus !!
        window = NULL;
    }

    SDL_Quit();

    if (!ok)
    { // On quitte si cela ne va pas
        exit(EXIT_FAILURE);
    }
}
/*
int main(){
    int PV[2] = {10, 6};
    int etat[2] = {FEU, EAU};
    int resultat = gagnant(etat);
    resolutionPV(PV, resultat, etat);
    printf("%d", PV[0]);
    printf("%d", PV[1]);
    return 0;
}*/
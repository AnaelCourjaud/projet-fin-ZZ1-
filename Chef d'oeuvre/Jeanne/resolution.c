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

int main(){
    int PV[2] = {10, 6};
    int etat[2] = {EAU, EAU};
    int resultat = gagnant(etat);
    resolutionPV(PV, resultat, etat);
    printf("%d", PV[0]);
    printf("%d", PV[1]);
    return 0;
}
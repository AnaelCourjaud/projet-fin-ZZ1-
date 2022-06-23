#include "affichageAttaque.h"

SDL_Texture * textureAttaque(SDL_Texture *texture[2][7], int joueur, int etat[2], int resultat)
{
    SDL_Texture * textureperso;
    switch (resultat)
    {
    case 0: // victoire perso
        if (joueur == 0)
            textureperso = texture[0][etat[0]];
        else
            textureperso = texture[1][4];
        break;
    case 1: // victoire ennemi
        if (joueur == 0)
            textureperso = texture[0][4];
        else
            textureperso = texture[1][etat[1]];
        break;
    default: // ex aequo et défense
        if (joueur == 0)
            textureperso = texture[0][etat[0]];
        else
            textureperso = texture[1][etat[1]];
    }
    return textureperso;
}

/*int main()
{
    int PV[2] = {10, 6};
    int etat[2] = {FEU, FEU};
    int resultat = gagnant(etat);
    int animation[2][7] = {{0, 1, 2, 3, 4, 5, 6}, {10, 11, 12, 13, 14, 15, 16}};
    printf("Resultat:"
           "%d\n",
           resultat);
    int textureperso = textureAttaque(animation, 0, etat, resultat);
    int textureennemi = textureAttaque(animation, 1, etat, resultat);
    printf("Perso:"
           "%d\n",
           textureperso);
    printf("Ennemi:"
           "%d\n",
           textureennemi);
    return 0;
}*/
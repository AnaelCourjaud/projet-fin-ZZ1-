#include "affichageAttaque.h"

SLD_Texture * textureAttaque(int animation[2][7], int joueur, int etat[2], int resultat)
{
    SLD_Texture * texture;
    switch (resultat)
    {
    case 0: // victoire perso
        if (joueur == 0)
            texture = animation[0][etat[0]];
        else
            texture = animation[1][4];
        break;
    case 1: // victoire ennemi
        if (joueur == 0)
            texture = animation[0][4];
        else
            texture = animation[1][etat[1]];
        break;
    default: // ex aequo et défense
        if (joueur == 0)
            texture = animation[0][etat[0]];
        else
            texture = animation[1][etat[1]];
    }
    return texture;
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
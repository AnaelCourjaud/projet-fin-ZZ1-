#include <nouvgen.h>

// monde = 0 -> monde normal; monde = 1 -> monde torique

int survie[9] = {0, 1, 1, 1, 1, 1, 0, 0, 0};

int naissance[9] = {0, 0, 0, 1, 0, 0, 0, 0, 0};

int nouvgengrille(int grille[HAUTEUR][LARGEUR], int nouvgrille[HAUTEUR][LARGEUR])
{
    int i, j;
    nb_modif = 0;
    for (i = 0; i < HAUTEUR; i++)
    {
        for (j = 0; j < LARGEUR; j++)
            nb_modif = nb_modif + nouvgen(i, j, grille, nouvgrille);
    }
    return nb_modif;
}

int nouvgen(int i, int j, int grille[HAUTEUR][LARGEUR], int nouvgrille[HAUTEUR][LARGEUR])
{
    int voisins = nb_voisins(i, j, grille, monde);
    int modif = 0;
    if (grille[i][j] == 1)
    {
        if (survie[voisins] == 0)
            nouvgrille[i][j] = 0;
        modif++;
        else nouvgrille[i][j] = 1;
    }
    else
    {
        if (naissance[voisins] == 1)
            nouvgrille[i][j] = 1;
        modif++;
        else nouvgrille[i][j] = 0;
    }
    return modif;
}

int nb_voisins(int i, int j, int grille[HAUTEUR][LARGEUR], int monde)
{
    int voisins = 0;
    int horz[3] = {-1, 0, 1};
    int vert[3] = {-1, 0, 1};
    int maxvert = 3;
    int minvert = 0;
    int minhorz = 0;
    int maxhorz = 3;
    if (monde == 0)
    {
        if (j == 0)
            minhorz = 1;
        if (j == LARGEUR)
            maxhorz = 2;
        if (i == 0)
            minvert = 1;
        if (i == LARGEUR - 1)
            maxvert = 2;
    }
    else
    {
        if (j == 0)
            horz[0] = LARGEUR - 1;
        if (j == LARGEUR)
            horz[2] = 0;
        if (i == 0)
            vert[0] = HAUTEUR - 1;
        if (i == LARGEUR)
            vert[2] = 0;
    }

    for (a = minhorz; a < maxhorz; a++)
    {
        for (b = minvert; b < maxvert; b++)
        {
            if (grille[horz[a] + i][vert[b] + j] == 1)
                voisins++;
        }
    }
    return (voisins);
}
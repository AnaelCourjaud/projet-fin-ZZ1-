#include <nouvgen.h>

int survie[9] = {0,1,1,1,1,1,0,0,0}

int naissance[9] = {0,0,0,1,0,0,0,0,0}

void nouvgen(int i, int j, int grille[HAUTEUR][LARGEUR], int nouvgrille[HAUTEUR][LARGEUR])
{
    int voisins = nb_voisins(i, j, grille[][]);
    if (grille[i][j] == 1)
    {
        if (survie[voisins] == 0)
            nouvgrille[i][j] = 0;
        else
            nouvgrille[i][j] = 1;
    }
    else
    {
        if (naissance[voisins] == 1)
            nouvgrille[i][j] = 1;
        else
            nouvgrille[i][j] = 0;
    }
}

int nb_voisins(int i, int j, int grille[HAUTEUR][LARGEUR])
{
    int voisins = 0;
    int a, b;
    for (a = -1, a < 2, a++)
    {
        for (b = -1, b < 2, b++)
        {
            if (grille[a + i][b + j] == 1)
                voisins++;
        }
    }
    return (voisins);
}
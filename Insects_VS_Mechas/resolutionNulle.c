#include "resolutionNulle.h"

void applicationDegats(combattant_t *tableauCombattants[NBRMAXCOMBATTANTS])
{
    printf("debut applicationdegats\n");
    int nombreDegatsPhysique = 0;
    int nombreDegatsMagique = 0;

    for (int i = 0; i < NBRMAXCOMBATTANTS; i++)
    {
        if (tableauCombattants[i] != NULL)
        {
            if (tableauCombattants[i]->typeCombattant == ROBOTGROS || tableauCombattants[i]->typeCombattant == ROBOTMETAL || tableauCombattants[i]->typeCombattant == ROBOTPETIT)
            {
                nombreDegatsPhysique += tableauCombattants[i]->physiqueRestant;
                nombreDegatsMagique += tableauCombattants[i]->magieRestante;
            }
        }
    }
    printf("degats pghysiques %d  degats magiques %d\n",nombreDegatsPhysique, nombreDegatsMagique);

    for (int j = 0; j < nombreDegatsPhysique; j++)
    {
        int i = 0;
        int hit = 0;
        while (hit == 0 && i < NBRMAXCOMBATTANTS)
        // for (int i = 0; i < NBRMAXCOMBATTANTS; i++)
        {
            if (tableauCombattants[i] != NULL)
            {
                if (tableauCombattants[i]->typeCombattant == BUGFIRE || tableauCombattants[i]->typeCombattant == FLY || tableauCombattants[i]->typeCombattant == MANTIS)
                {
                    if (tableauCombattants[i]->physiqueRestant > 0)
                    {
                        tableauCombattants[i]->physiqueRestant--;
                        hit = 1;
                    }
                }
            }
            i++;
        }
    }

    for (int j = 0; j < nombreDegatsMagique; j++)
    {
        int i = 0;
        int hit = 0;
        while (hit == 0 && i < NBRMAXCOMBATTANTS)
        // for (int i = 0; i < NBRMAXCOMBATTANTS; i++)
        {
            if (tableauCombattants[i] != NULL)
            {
                if (tableauCombattants[i]->typeCombattant == BUGFIRE || tableauCombattants[i]->typeCombattant == FLY || tableauCombattants[i]->typeCombattant == MANTIS)
                {
                    if (tableauCombattants[i]->magieRestante > 0)
                    {
                        tableauCombattants[i]->magieRestante--;
                        hit = 1;
                    }
                }
            }
            i++;
        }
    }
}
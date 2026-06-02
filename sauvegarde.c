#include <stdio.h>
#include <stdlib.h>
#include "sauvegarde.h"
#include  "jeu.h"
void SAUV_initialisation(){
    FILE *f = fopen("..\\sauvegarde.csv", "w"); //Ouverture du fichier sauvegarde.csv en mode sur écriture
    if (f == NULL) //Vérification de la réussite de l'ouverture du fichier
    {
        printf("Erreur : impossible d'ouvrir le fichier sauvegarde.csv\n");
        exit(1);
    }
    fclose(f);
}
void SAUV_sauvegarde(Partie p)
{
    FILE *f = fopen("..\\sauvegarde.csv", "a");
    if (f == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier sauvegarde.csv\n");
        exit(1);
    }
    fprintf(f,"%d,%d,%d,",p.mode,p.difficulte,p.taille);
    //Sauvegarde du mode de jeu, de la difficulté de la partie et de la taille de la grille

    fprintf(f,"\n");

    for (int i = 0; i < p.taille; i++) {        //Sauvegarde des positions des mines de la forme x-y
        for (int j = 0; j < p.taille; j++) {

            if (p.grille[i][j].mine == 1) {
                fprintf(f, "%d-%d,", i, j);
            }
        }
    }

    fprintf(f,"\n");

    for (int i = 0; i < p.taille; i++)          //Sauvegarde des positions des cases relevées de la forme x-y
    {
        for (int j = 0; j < p.taille; j++)
        {
            if (p.grille[i][j].visible == 1)
            {
                fprintf(f, "%d-%d,", p.grille[i][j].visible);
            }
        }
    }


    fclose(f);
}
void SAUV_charger_partie(Partie p)
{
    FILE *f = fopen("..\\sauvegarde.csv", "r");
    if (f == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier sauvegarde.csv\n");
        exit(1);
    }
    fscanf(f,"%d",&p.mode);
    fclose(f);
}
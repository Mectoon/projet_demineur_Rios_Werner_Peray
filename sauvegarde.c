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
    fprintf(f,"%d,",p.mode);

    fclose(f);
}
void SAUV_charger_partie()
{
    FILE *f = fopen("..\\sauvegarde.csv", "r");
    if (f == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier sauvegarde.csv\n");
        exit(1);
    }


    fclose(f);
}
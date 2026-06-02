#include <stdio.h>
#include <stdlib.h>
#include "sauvegarde.h"
void SAUV_initialisation(){
    FILE *f = fopen("sauvegarde.csv", "w"); //Ouverture du fichier sauvegarde.csv en mode sur écriture
    if (f == NULL) //Vérification de la réussite de l'ouverture du fichier
    {
        printf("Erreur : impossible d'ouvrir le fichier sauvegarde.csv\n");
        exit(1);
    }
    fclose(f);
}
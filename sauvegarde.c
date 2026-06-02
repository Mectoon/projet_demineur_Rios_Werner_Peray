#include <stdio.h>
#include <stdlib.h>
#include "sauvegarde.h"
void SAUV_init(){
    FILE *f = fopen("sauvegarde.csv", "a");

    if (f == NULL) {
        printf("Erreur : impossible de créer le fichier.\n");
        exit(1);
    }

    // Exemple d’écriture d’en-tête CSV
    fprintf(f, "nom,score,essais,malus,bonus\n");

    // Exemple d’écriture d’une ligne
    fprintf(f, "partie1,50,4,1,89\n");

    fclose(f);
}
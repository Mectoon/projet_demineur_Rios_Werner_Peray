#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    //Ouverture du fichier sauvegarde.csv en mode sur écriture additionnelle

    if (f == NULL)      //Vérification de la réussite de l'ouverture du fichier
    {
        printf("Erreur : impossible d'ouvrir le fichier sauvegarde.csv\n");
        exit(1);
    }



    fprintf(f,"%d,%d,%d,",p.mode,p.difficulte,p.taille);
    //Sauvegarde du mode de jeu, de la difficulté de la partie et de la taille de la grille

    fprintf(f,"\n");        //Retour à la ligne pour sauvegarde des prochaines informations

    ecrire_coordonnees(p,f,"mine");       //Sauvegarde des positions des mines de la forme x-y

    fprintf(f,"\n");        //Retour à la ligne pour sauvegarde des prochaines informations

    ecrire_coordonnees(p,f,"taille");          //Sauvegarde des positions des cases relevées de la forme x-y



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

void ecrire_coordonnees(Partie p, FILE *f, const char *champ)
{
    for (int i = 0; i < p.taille; i++)
    {
        for (int j = 0; j < p.taille; j++)
        {
            int valeur = 0; //Définition d'une variable qui vaut 1 si la case de coordonnées (i,j)
                            // du paramètre "champ" concerné vaut 1 et 0 sinon
            if (strcmp(champ, "visible") == 0)  //Recherche du paramètre à modifier en fonction de la chaîne "champ"
                {
                valeur = p.grille[i][j].visible;
                }
            else if (strcmp(champ, "mine") == 0)
                {
                valeur = p.grille[i][j].mine;
                }
            else if (strcmp(champ, "bonus") == 0)
                {
                valeur = p.grille[i][j].bonus;
                }
            else if (strcmp(champ, "malus") == 0)
                {
                valeur = p.grille[i][j].malus;
                }
            if (valeur == 1)
                fprintf(f, "%d-%d,", i, j);
        }
    }
}
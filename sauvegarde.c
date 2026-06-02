#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sauvegarde.h"
#include  "jeu.h"
void SAUV_initialisation(){
    FILE *f = fopen("..\\sauvegarde.csv", "w"); // Ouverture du fichier sauvegarde.csv en mode sur écriture
    if (f == NULL) // Vérification de la réussite de l'ouverture du fichier
    {
        printf("Erreur : impossible d'ouvrir le fichier sauvegarde.csv\n");
        exit(1);
    }
    fclose(f);
}

void SAUV_charger_partie(Partie *p)
{
    char ligne[5][1024];        // Création d'un tableau de 5 lignes avec 1024 caractères par ligne,
    // collectant le contenu du fichier de sauvegarde
    char temporaire[1024];      // Création d'un tableau de stockage temporaire pour copier le contenu
    // du fichier avant d'introduire dans le tableau ligne
    int num_ligne = 0;          // Déclaration d'une variable entière indiquant le numéro de ligne sur laquelle on extrait les données
    FILE *f = fopen("..\\sauvegarde.csv", "r"); // Ouverture du fichier sauvegarde.csv en mode lecture
    if (f == NULL)   // Vérification de la réussite de l'ouverture du fichier
    {
        printf("Erreur : impossible d'ouvrir le fichier sauvegarde.csv\n");
        exit(1);
    }

    while (fgets(temporaire, 1024, f) != NULL) // Stocke chaque ligne dans un tableau
    {                                                             // pour ne garder que les 5 dernières.
        strcpy(ligne[num_ligne % 5], temporaire);
        num_ligne++;
    }
    fclose(f);
    // Chargement des données sauvegardées dans la structure Partie
    // Ligne 1 : paramètres généraux
    sscanf(ligne[0], "%d,%d,%d,%d,%d,%d,%d",
           &p->mode,
           &p->difficulte,
           &p->taille,
           &p->vies,
           &p->tour,
           &p->tour_malus,
           &p->temps);

    // Ligne 2 : mines
    SAUV_charger_coordonnees(p, ligne[1], "mine");

    // Ligne 3 : cases visibles
    SAUV_charger_coordonnees(p, ligne[2], "visible");

    // Ligne 4 : malus
    SAUV_charger_coordonnees(p, ligne[3], "malus");

    // Ligne 5 : bonus
    SAUV_charger_coordonnees(p, ligne[4], "bonus");
}

void SAUV_charger_coordonnees(Partie *p, const char *ligne, const char *champ)
{
    char temporaire[1024];  // Copie locale de la ligne pour éviter de modifier l'originale
    strcpy(temporaire, ligne);

    char *couple = strtok(temporaire, ","); // Extraction d'un couple "x-y" séparé par des virgules

    while (couple != NULL)  // Parcours de tous les couples présents dans la ligne
    {
        char *x_str = strtok(couple, "-");  // Récupération de la partie avant le tiret, coordonnée x
        char *y_str = strtok(NULL, "-");    // Récupération de la partie après le tiret, coordonnée y

        if (x_str && y_str!=NULL)   // Vérification que les deux valeurs x et y existent
        {
            int x = atoi(x_str);    //x_str chaîne transformée en entier x
            int y = atoi(y_str);    //y_str chaîne transformée en entier y

            // Activation du champ correspondant dans la grille selon le type demandé
            if (strcmp(champ, "mine") == 0)
                p->grille[x][y].mine = 1;

            else if (strcmp(champ, "visible") == 0)
                p->grille[x][y].visible = 1;

            else if (strcmp(champ, "bonus") == 0)
                p->grille[x][y].bonus = 1;

            else if (strcmp(champ, "malus") == 0)
                p->grille[x][y].malus = 1;
        }

        couple = strtok(NULL, ","); // Passage au couple suivant dans la ligne
    }
}
void SAUV_sauvegarde(Partie *p)
{
    FILE *f = fopen("..\\sauvegarde.csv", "a");
    //Ouverture du fichier sauvegarde.csv en mode sur écriture additionnelle

    if (f == NULL)      //Vérification de la réussite de l'ouverture du fichier
    {
        printf("Erreur : impossible d'ouvrir le fichier sauvegarde.csv\n");
        exit(1);
    }


    fprintf(f,"%d,%d,%d,%d,%d,%d,%d",p->mode,p->difficulte,p->taille,p->vies,p->tour,p->tour_malus,p->temps);
    //Sauvegarde du mode de jeu, de la difficulté de la partie, de la taille de la grille,
    //du nombre de vies, du numéro du tour actuel, celui d'activation du dernier malus et du temps mis précédemment

    fprintf(f,"\n");        //Retour à la ligne pour sauvegarde des prochaines informations

    ecrire_coordonnees(p,f,"mine");           //Sauvegarde des positions des mines de la forme x-y
    ecrire_coordonnees(p,f,"taille");         //Sauvegarde des positions des cases relevées de la forme x-y
    ecrire_coordonnees(p,f,"malus");          //Sauvegarde des positions des cases malus de la forme x-y
    ecrire_coordonnees(p,f,"bonus");          //Sauvegarde des positions des cases bonus de la forme x-y


    fclose(f);
}
void ecrire_coordonnees(Partie *p, FILE *f, const char *champ)
{
    for (int i = 0; i < p->taille; i++)
    {
        for (int j = 0; j < p->taille; j++)
        {
            int valeur = 0; //Définition d'une variable qui vaut 1 si la case de coordonnées (i,j)
                            // du paramètre "champ" concerné vaut 1 et 0 sinon
            if (strcmp(champ, "visible") == 0)  //Recherche du paramètre à modifier en fonction de la chaîne "champ"
                {
                valeur = p->grille[i][j].visible;
                }
            else if (strcmp(champ, "mine") == 0)
                {
                valeur = p->grille[i][j].mine;
                }
            else if (strcmp(champ, "bonus") == 0)
                {
                valeur = p->grille[i][j].bonus;
                }
            else if (strcmp(champ, "malus") == 0)
                {
                valeur = p->grille[i][j].malus;
                }
            if (valeur == 1)
                fprintf(f, "%d-%d,", i, j);
        }
    }
    fprintf(f,"\n"); //Retour à la ligne pour sauvegarde des prochaines informations
}
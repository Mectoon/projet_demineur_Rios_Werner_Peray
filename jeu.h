//
// Created by arios on 27/05/2026.
//

#ifndef PROJET_DEMINEUR_RIOS_WERNER_PERAY_JEU_H
#define PROJET_DEMINEUR_RIOS_WERNER_PERAY_JEU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max 12
#define FICHIER_SAUVEGARDE "sauvegarde.txt"

/**
 * @struct Case
 * @brief Representation d'une case de la grille.
 */
typedef struct {
    int mine;          // 1 = bombe, 0 = pas de bombe
    int visible;       // 1 = case revelee, 0 = case cachee
    int nb_mines;      // nombre de mines autour de la case

    int bonus;         // 1 = bonus present, 0 = pas de bonus
    int bonus_reveal;  // 1 = bonus revelation present, 0 = pas de bonus revelation
    int malus;         // 1 = malus present, 0 = pas de malus
} Case;

/**
 * @struct Partie
 * @brief Representation de l'ensemble d'une partie.
 */
typedef struct {
    Case grille[max][max];

    int taille;        // taille de la grille : entre 6 et 12
    int difficulte;    // 1 = facile, 2 = moyen, 3 = difficile
    int mode;          // 1 = classique, 2 = bonus/malus

    int nb_mines;      // nombre total de mines
    int nb_bonus;      // nombre total de bonus
    int nb_malus;      // nombre total de malus

    int vies;          // entre 0 et + infini
    int brouillage;    // 0 tours ou 2 tours
    int etat;          // 0 = en cours, 1 = gagne, 2 = perdu
} Partie;

/**
 * @brief Calcule le nombre de mines en fonction de la taille de la grille et de la difficulte.
 *
 * La fonction utilise la difficulte stockee dans la structure Partie :
 * 1 - facile : 20% des cases sont des mines.
 * 2 - moyen : 25% des cases sont des mines.
 * 3 - difficile : 30% des cases sont des mines.
 * Elle stocke ensuite le nombre de mines dans la structure partie.
 *
 * @param p Pointeur vers la structure Partie.
 * @return Rien.
 */
void calculer_nombre_mines(Partie *p);


/**
 * @brief Initialise une grille vide selon la taille donnee.
 *
 * Toutes les cases sont initialisees sans mine, non visibles,
 * avec 0 mine autour, sans bonus et sans malus.
 *
 * @param p Pointeur vers la structure Partie.
 * @param taille Taille de la grille a creer.
 * @return Rien.
 */
void creer_tableau_vide(Partie *p, int taille);


/**
 * @brief Place aleatoirement les bombes dans la grille.
 *
 * La fonction place le nombre de bombes contenu dans p->nb_mines.
 * Si une bombe est deja presente sur une case tiree au hasard,
 * un nouveau tirage est effectue.
 *
 * @param p Pointeur vers la structure Partie.
 * @return Rien.
 */
void placer_bombes(Partie *p);


/**
 * @brief Place aleatoirement les bonus et les malus dans la grille.
 *
 * La fonction place les bonus et les malus uniquement sur des cases libres.
 *
 * @param p Pointeur vers la structure Partie.
 * @return Rien.
 */
void placer_bonus_malus(Partie *p);


/**
 * @brief Calcule le nombre de mines autour de chaque case.
 *
 * Pour chaque case de la grille, la fonction compte les mines presentes
 * dans les 8 cases voisines. Une case contenant une mine recoit la valeur -1.
 *
 * @param p Pointeur vers la structure Partie.
 * @return Rien.
 */
void calculer_mines_autour(Partie *p);


/**
 * @brief Affiche la grille de jeu.
 *
 * Les cases cachees sont affichees avec '-'.
 * Les cases visibles affichent soit une mine, soit le nombre de mines autour,
 * soit un bonus ou un malus selon leur contenu.
 *
 * @param p Pointeur vers la structure Partie.
 * @return Rien.
 */
void afficher_grille(Partie *p);


/**
 * @brief Revele une case choisie par le joueur.
 *
 * La fonction verifie d'abord si les coordonnees sont valides.
 * Si la case contient une mine, on perd une vie.
 * Si la case ne contient pas de mine, elle devient visible.
 * Si la case revelee contient 0 mine autour, les cases voisines sont revelees automatiquement.
 *
 * @param p Pointeur vers la structure Partie.
 * @param ligne Ligne de la case a reveler.
 * @param colonne Colonne de la case a reveler.
 * @return Rien.
 */
void reveler_case(Partie *p, int ligne, int colonne);

#endif //PROJET_DEMINEUR_RIOS_WERNER_PERAY_JEU_H
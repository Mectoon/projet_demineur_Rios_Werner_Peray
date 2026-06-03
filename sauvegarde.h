//
// Created by arios on 27/05/2026.
//

#ifndef PROJET_DEMINEUR_RIOS_WERNER_PERAY_SAUVEGARDE_H

#define PROJET_DEMINEUR_RIOS_WERNER_PERAY_SAUVEGARDE_H
#include "jeu.h"
/**
 * @brief Efface tout le contenu du fichier sauvegarde.csv
 * @return Rien.
 */
void SAUV_initialisation();
/**
 * @brief Charge la dernière partie sauvegardée en lisant directement les 5 dernières lignes du fichier.
 *
 * La fonction ouvre le fichier sauvegarde.csv et lit toutes ses lignes.
 * Seules les 5 dernières sont conservées, car elles correspondent à la dernière partie sauvegardée.
 * La première ligne contient les paramètres généraux de la partie.
 * Les quatre suivantes contiennent les coordonnées des mines,des cases visibles, malus et bonus.
 *
 * @param p Pointeur vers la structure Partie à remplir.
 * @return Rien.
 */
void SAUV_charger_partie(Partie *p);
/**
 * @brief Charge des coordonnées de la forme x-y dans la grille.
 *
 * La fonction reçoit une ligne contenant des couples x-y séparés par des virgules.
 * Chaque couple correspond à une case de la grille dont la valeur doit être activée.
 *
 * @param p Pointeur vers la structure Partie.
 * @param ligne Chaîne contenant les coordonnées à charger.
 * @param champ Chaîne indiquant le champ à modifier (mine, visible, bonus ou malus).
 * @return Rien.
 */
void SAUV_charger_coordonnees(Partie *p, const char *ligne, const char *champ);


void SAUV_sauvegarde(Partie *p);
void SAUV_ecrire_coordonnees(Partie *p, FILE *f, const char *champ);
#endif //PROJET_DEMINEUR_RIOS_WERNER_PERAY_SAUVEGARDE_H


/**
* \file pile.h
*
* 1 type et 3 fonctions :
*
* -type \a pile : structure qui contient un tableau de tuiles et le nombre de tuiles qu'elle contient
*
* -init() : crée une pile vide
* -empile(p,new) : ajoute la tuile new en haut de la pile p
* -depile(p) : retire la tuile au sommet de p
*/


#ifndef PILE_H
#define PILE_H

#include <stdio.h>
#include <stdlib.h>
#include "structuile.h"
#define MAX 100


typedef struct
{
  tuile t[MAX];
  int som;
}pile;

/**
 *\brief crée une pile vide p
 */
pile init();


/**
 *\brief ajoute la tuile new en haut de la pile p
 *\param pile p et tuile new
 */
void empile(pile *p, tuile new);


/**
 *\brief retire la tuile au sommet de p
 *\param une pile p
 *\return la tuile retirée du sommet de p
 */
tuile depile(pile *p);



/**
 *\brief alloue dynamiquement et ALEATOIREMENT nb_tuiles TUILES
 *\param nb_tuile : nombre de tuile
 *\return un tableau de tuiles de taille nb_tuile
 */
pile initi_tuiles(int nb_tuile);


/**
 *\brief alloue dynamiquement des TUILES A PARTIR D UN FICHIER
 *\param le fichier
 *\return tableau de TUILES REMPLIES
 */
pile initi_tuile_fichier(FILE* fp);

#endif

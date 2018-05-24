/**
 * \file village.h
 *
 * 1 fonctions
 *
 * int trouver_village(grille g); : renvois un entier qui représente le cardinal de le village le plus grand dans grille g
 */

#ifndef VILLAGE_H
#define VILLAGE_H
#include "../lotA/structgrille.h"
#include "../lotA/structuile.h"
#include "../lotA/structure.h"

struct ville_s
{
	int x;
	int y;
};
typedef struct ville_s* ville;
/**
 *\brief calcule le cardinal de le village le plus grand
 *\param une grille g
 *\return un entier entier qui représente le cardinal de le village le plus grand dans grille g
 */
int trouver_village(grille g);


#endif
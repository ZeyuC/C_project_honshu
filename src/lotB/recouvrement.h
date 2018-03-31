/**
* \file recouvrement.h
*
* 3 fonctions :
* - un type terrain
* -ter_recouvert (grille l): Liste des terrains recouverts sur le plateau
*
* -ter_recouvert_tuile(grille l, pile p) : Liste des terrains recouverts par une tuile si on essaie de la poser
   sur le plateau
* -test_recouvert : Test de la règle Une tuile ne peut être totalement recouverte à
aucun moment de la partie
*/

#ifndef RECOUVRET_H
#define RECOUVRET_H
#include "../lotA/structgrille.h"
#include "../lotA/structuile.h"
#include "../lotA/structure.h"

struct terrain_s
{
	int x;
	int y;
	char type;
};
typedef struct terrain_s* terrain;

/**
 *\brief Liste des terrains recouverts sur le plateau
 *\param une grille
 *\return un tableux de tpye terrain qui contient les coordonnée de terrain recouverts
 */
terrain ter_recouvert(grille l,int n);

/**
 *\brief Liste des terrains recouverts par une tuile si on essaie de la poser
   sur le plateau
 *\param une grille et une tuile
 *\return un tableux de tpye terrain qui contient les coordonnée de terrain recouverts par une tuile
 */
terrain ter_recouvert_tuile(grille l, tuile tuile_s);

/**
 *\brief test si l'endroit qu'on poser pour une nouvelle tuile est totalement recouvert 
 *\param une grille et une nouvelle tuile qu'on veut poser 
 *\return 0 si il est pas totalement recouvert 1 sinon
 */
int test_recouvert(grille l,tuile new_t);


#endif
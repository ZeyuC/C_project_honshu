/**
 * \file structure.h
 *
 * 3 fonctions
 *
 * - lecture_grille(x,y) : lis le terrain de la grille en position (x,y)
 * - rot_tuile(t,ort) : donne l'orientation \a ort à la tuile
 * - inser_tuile(g,t,x,y) : insert la tuile t dans la grille g en position (x,y)
 */

#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "structuile.h"
#include "structgrille.h"



/**
 *\brief lis la COORDONNEE (x,y) DE LA GRILLE
 *\param 0 <=x <= g->size , 0<= y <= g->size , tableau char ** g NOT NULL
 *\return le char en coordonnées (x,y) de la grille g
 */
char lecture_grille(int x,int y,grille g);


/**
 *\brief ORIENTE UNE TUILE t
 *\param tuile t, char "<", ">", "v" ou "^" donnant l'orientation de la tuile
 *\return void
*/
void rot_tuile(tuile t, char ort);

/**
 *\brief INSERE LA TUILE t DANS LA GRILLE  g
 * si la tuile n'entre pas entierement dans la grille, aucune action
 *\param grille g non null, t , x>=0 , y>= 0
 *\return void
 */
void inser_tuile(grille g ,tuile t,int x,int y);

#endif

/**
 * \file village.h
 *
 * 3 fonctions
 *
 * - trouver_village(grille g); : donne un vecteur avec les coordonnées de chaque village de la grille
 * - presence(int x, int y, vectur v) : vérifie si la case (x,y) est un village
 * - trouver_ville(int x, int y, grille g) : donne les coordonnées des villages de la ville du village (x,y), si ville il y a 
 */

#ifndef STRUCTURE_H
#define STRUCTURE_H


int coord_village[size][2] = {
	for (i=0; i<=size; i++){
		printf("{0,0},");
	}
	printf("{0,0}");
}

/**
 *\brief liste les coordonnées des villages de la grille
 *\param la grille g
 *\return le vecteur coord_village modifié
*/


void trouver_village(grille g);
	
	


int vec[size*size][2] = {
	for (i=0; i<=size; i++){
		printf("{-1,-1},");
	}
	printf("{-1,-1}");
}

/**
 *\brief vérifie la présence d'un village à la case (x,y)
 *\param les cordonnées x et y, la grille g
 *\return 1 si il y a présence
*/


int presence(int x, int y, vecteur v);

/**
 *\brief retourne la ville associée au village en (x,y), si ville il y a
 *\param les cordonnées x et y, la grille g
 *\return le vecteur vec avec les coordonées des villages de la ville du village (x,y)
*/


void trouver_ville(int x, int y, grille g);



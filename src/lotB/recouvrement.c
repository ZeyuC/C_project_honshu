#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "recouvrement.h"


int plus_de_tuile(pile p){
    int i;
    int count = 0;
    for (i = 0; i < p.som; i++){
        if (p.t[i]->pos[0] != -1){
            count ++;
        }
    }
    return count == p.som ;
}


int end_of_game(grille g, pile hand, tuile t){
    int count = 0;
    int i,j;
    if (plus_de_tuile(hand)){
        return 1;
    }
    else {
        for (i = 0; i < g->size; i++){
            for (j = 0; j < g->size; j++){
                t->ort = '^';
                if (add_to_grille(g,t,i,j,0)){
                    count++;
                }
                t->ort = '>';
                if (add_to_grille(g,t,i,j,0)){
                    count++;
                }
                t->ort = '<';
                if (add_to_grille(g,t,i,j,0)){
                    count++;
                }
                t->ort = 'v';
                if (add_to_grille(g,t,i,j,0)){
                    count++;
                }
            }
        }
        return count==0;
    }
}

/**
 *\brief le nombre de terrain recouvert
 *\param une grille
 *\return un entier qui est le nombre de terrain recouvert
 */
int nombre_recouvert(grille g)
{
    int count=0,i,j;
    int size = g->size;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size ; j++)
        {
            if(g->matrix[i][j]!='.')
            {
                count++;
            }
        }
    }
    return count;
}

/**
 *\brief Liste des terrains recouverts sur le plateau
 *\param une grille et nombre de terrains recouverts
 *\return un tableau de type terrain qui contient les coordonnées des terrains recouverts
 */
terrain* ter_recouvert(grille l,int n)
{

    int i,j;
    int count=0;
    int size = l->size;
    terrain* t = (terrain*)malloc(sizeof(terrain)*n);
    for (i=0; i<n; i++){
       t[i] = (terrain)malloc(sizeof(int)*2 + sizeof(char));
     }
    for (i = 0; i < size; i++)
    {
    	for (j = 0; j < size ; j++)
    	{
    		if(l->matrix[i][j]!='.')
              {

              	t[count]->y=j;
              	t[count]->type=l->matrix[i][j];
              	count++;

              }
    	}
    }

    return t;
}


/**
 *\brief Liste des terrains recouverts par une tuile si on essaie de la poser
   sur le plateau
 *\param une grille et une tuile
 *\return un tableau de type terrain qui contient les coordonnées des terrains recouverts par une tuile
 */
terrain* ter_recouvert_tuile(grille l, tuile tuile_s, int x, int y)
{
     int i,j;
     terrain* t = (terrain*)malloc(sizeof(terrain)*6);
     for (i=0; i<6; i++){
       t[i] = (terrain)malloc(sizeof(int)*2 + sizeof(char));
     }
     char ort = tuile_s->ort;
     int count=0;
     if(ort == '^'){
     	 for ( i = 0; i < 3; ++i)
       {
     		 for (j = 0; j < 2; ++j)
     		 {
     		   t[count]->x=x+i;
        	 t[count]->y=y+j;
        	 t[count]->type=l->matrix[x+i][y+j];
        	 count++;
     		 }
     	 }
     }
     else if(ort == '<'){
     	for ( i = 0; i < 2; ++i)
     	{
     		for (j = 0; j < 3; ++j)
     		{

     			t[count]->x=x-i;
          t[count]->y=y+j;
          t[count]->type=l->matrix[x-i][y+j];
          count++;
     		}
     	}

     }
     else if(ort == '>'){
     	for ( i = 0; i < 2; ++i)
     	{
     		for (j = 0; j < 3; ++j)
     		{
     			t[count]->x=x+i;
          t[count]->y=y-j;
          t[count]->type=l->matrix[x+i][y-j];
          count++;
     		}
     	}
     }
     else {
     	for ( i = 0; i < 3; ++i)
     	{
     		for (j = 0; j < 2; ++j)
     		{
     			t[count]->x=x-i;
          t[count]->y=y-j;
          t[count]->type=l->matrix[x-i][y-j];
          count++;
     		}
     	}
     }
    return t;
}


/**
 *\brief donne la liste des positions occupées par la tuile à la place k dans la pile de la grille
 *\param une grille et un entier k tel que k<=pile_tuile.som
 *\return retourne la liste des positions de la tuile voulu
 */


int** list_pos(grille g,int k){
  int x,y,i,a;
  int** poss_tuile = (int**)malloc(6*sizeof(int*));
  for (i=0; i<6; i++){
    poss_tuile[i] = (int*)malloc(2*sizeof(int));
  }
  a=0;
  if (g->pile_tuile.t[k]->ort == '^'){
    for (x = g->pile_tuile.t[k]->pos[0]; x < g->pile_tuile.t[k]->pos[0]+3; x++){
      for (y = g->pile_tuile.t[k]->pos[1]; y < g->pile_tuile.t[k]->pos[1]+2; y++){
        poss_tuile[a][0] = x;
        poss_tuile[a][1] = y;
        a++;
      }
    }
    return poss_tuile;
  }
  else if (g->pile_tuile.t[k]->ort == 'v'){
    for (x = g->pile_tuile.t[k]->pos[0]; x > g->pile_tuile.t[k]->pos[0]-3; x--){
      for (y = g->pile_tuile.t[k]->pos[1]; y > g->pile_tuile.t[k]->pos[1]-2; y--){
        poss_tuile[a][0] = x;
        poss_tuile[a][1] = y;
        a++;
      }
    }
    return poss_tuile;
  }
  else if (g->pile_tuile.t[k]->ort == '<'){
    for (x = g->pile_tuile.t[k]->pos[0]; x > g->pile_tuile.t[k]->pos[0]-2; x--){
      for (y = g->pile_tuile.t[k]->pos[1]; y < g->pile_tuile.t[k]->pos[1]+3; y++){
        poss_tuile[a][0] = x;
        poss_tuile[a][1] = y;
        a++;
      }
    }
    return poss_tuile;
  }
  else{
    for (x = g->pile_tuile.t[k]->pos[0]; x < g->pile_tuile.t[k]->pos[0]+2; x++){
      for (y = g->pile_tuile.t[k]->pos[1]; y > g->pile_tuile.t[k]->pos[1]-3; y--){
        poss_tuile[a][0] = x;
        poss_tuile[a][1] = y;
        a++;
      }
    }
    return poss_tuile;
  }
}


/**
 *\brief donne l'indice dans la pile de la grille de la tuile dont une case est en (x,y)
 *\param une grille et une position donnée par 2 entier x et y tel que (x,y) soit dans la grille
 *\return le numéro de la tuile s'il y en a une qui occupe cette position et -1 sinon
 */
int tuile_of(grille g, int x, int y){
  int i,k,j;
  for (i = g->pile_tuile.som; i>-1; i--){
    int** list = list_pos(g,i);
    for (k=0; k<6; k++){
      if (list[k][0] == x && list[k][1] == y){
        for (j=0; j<6; j++){
          free(list[j]);
        }
        free(list);
        return i;
      }
    }
    for (j=0; j<6; j++){
      free(list[j]);
    }
    free(list);
  }
  return -1;
}



/**
 *\brief test si la tuile d'indice k dans la pile de la grille n'est pas totalement recouverte
 *\param une grille et un entier k <= taille de la pile de la grille
 *\return 1 si elle n'est pas totalement recouverte 0 sinon
 */
int test_fully_covered(grille g,int k)
{
  int i;
  int count = 0;
  int** list = list_pos(g,k);
  for (i=0; i<6; i++){
    if (k != tuile_of(g,list[i][0],list[i][1])){
      count ++;;
    }
  }
  for (i=0; i<6; i++){
    free(list[i]);
  }
  free(list);
  return count < 6;
}

/**
 *\brief vérifie que l'on respecte la limite de la zone
 *\param une grille, une tuile et sa position x et y
 *\return 0 si le test échoue
 */


int test_limite(grille g, tuile t, int x, int y){
  if ( x<0 || x>g->size || y<0 || y>g->size){
    return 0;
  }
  else if (t->ort == '^'){
    return (x+2 < g->size) && (y+1 < g->size);
  }
  else if (t->ort == 'v'){
    return (x-2 >= 0) && (y-1 >= 0);
  }
  else if (t->ort == '<'){
    return (x-1 >= 0) && (y+2 < g->size);
  }
  else {
    return (x+1 < g->size) && (y-2 >= 0);
  }
}

/**
*\brief on vérifie pour une nouvelle tuile qu'au moins une de ses cases recouvre autre chose que '.'
*\param grille g, tuile t , position de la tuile x et y
*\return 1 si la règle est respectée et 0 sinon
*/
int recouvre_ancien(grille g, tuile t, int x, int y){
  if (t->ort == '^'){
    return (g->matrix[x][y] != '.'||g->matrix[x+1][y] != '.'||g->matrix[x+2][y] != '.'||g->matrix[x][y+1] != '.'||g->matrix[x+1][y+1] != '.'||g->matrix[x+2][y+1] != '.');
  }
  else if (t->ort == 'v'){
    return (g->matrix[x][y] != '.'||g->matrix[x-1][y] != '.'||g->matrix[x-2][y] != '.'||g->matrix[x][y-1] != '.'||g->matrix[x-1][y-1] != '.'||g->matrix[x-2][y-1] != '.');
  }
  else if (t->ort == '<'){
    return (g->matrix[x][y] != '.'||g->matrix[x][y+1] != '.'||g->matrix[x][y+2] != '.'||g->matrix[x-1][y] != '.'||g->matrix[x-1][y+1] != '.'||g->matrix[x-1][y+2] != '.');
  }
  else{
    return (g->matrix[x][y] != '.'||g->matrix[x][y-1] != '.'||g->matrix[x][y-2] != '.'||g->matrix[x+1][y] != '.'||g->matrix[x+1][y-1] != '.'||g->matrix[x+1][y-2] != '.');
  }
}

/**
*\brief on vérifie pour une nouvelle tuile qu'elle ne recouvre pas une case Lac
*\param  grille g, tuile t et les position de cette tuile x et y
*\return 1 si la règle est respectée et 0 sinon
*/

int testlac(grille g, tuile t, int x, int y)
{
  if (t->ort == '^'){
    return (g->matrix[x][y] != 'L'&&g->matrix[x+1][y] != 'L'&&g->matrix[x+2][y] != 'L'&&g->matrix[x][y+1] != 'L'&&g->matrix[x+1][y+1] != 'L'&&g->matrix[x+2][y+1] != 'L');
  }
  else if (t->ort == 'v'){
    return (g->matrix[x][y] != 'L'&&g->matrix[x-1][y] != 'L'&&g->matrix[x-2][y] != 'L'&&g->matrix[x][y-1] != 'L'&&g->matrix[x-1][y-1] != 'L'&&g->matrix[x-2][y-1] != 'L');
  }
  else if (t->ort == '<'){
    return (g->matrix[x][y] != 'L'&&g->matrix[x][y+1] != 'L'&&g->matrix[x][y+2] != 'L'&&g->matrix[x-1][y] != 'L'&&g->matrix[x-1][y+1] != 'L'&&g->matrix[x-1][y+2] != 'L');
  }
  else{
    return (g->matrix[x][y] != 'L'&&g->matrix[x][y-1] != 'L'&&g->matrix[x][y-2] != 'L'&&g->matrix[x+1][y] != 'L'&&g->matrix[x+1][y-1] != 'L'&&g->matrix[x+1][y-2] != 'L');
  }
}

/**
 *\brief on vérifie pour une nouvelle tuile qu'il peut bien inserer dans la grille
 *\param  grille g, tuile t et les position de cette tuile x et y ,a==1 affiche les messages
 *\return 1 si la règle est respectée et 0 sinon
 */
int add_to_grille(grille g, tuile t, int x, int y, int a){
    int k,i;

    if (!(test_limite(g, t, x, y))){    /*on vérifie que la tuile rentre dans la grille*/
        if (a==1) printf("la nouvelle tuile est en dehors des limites du plateau!\n");
        return 0;
    }
    if (!(recouvre_ancien(g,t,x,y))) {
        if (a==1) printf("la nouvelle tuile ne recouvre aucune autre tuile!\n");
        return 0;
    }
    if (!(testlac(g,t,x,y))){
        if (a==1) printf("une case lac est recouverte pas la nouvelle tuile!\n");
        return 0;
    }

    terrain* liste_ter = ter_recouvert_tuile(g,t,x,y);   /*on liste les terrains qu'occupera la nouvelle tuile si elle est posée*/

    empile(&(g->pile_tuile),t);

    g->pile_tuile.t[g->pile_tuile.som]->pos[0]=x;

    g->pile_tuile.t[g->pile_tuile.som]->pos[1]=y;

    for (i=0; i<6; i++){
        g->pile_tuile.som --;
        k = tuile_of(g,liste_ter[i]->x, liste_ter[i]->y);
        g->pile_tuile.som ++;
        if (k!=-1){
            if (!(test_fully_covered(g,k))) {
                g->pile_tuile.t[g->pile_tuile.som]->pos[0]=-1;
                g->pile_tuile.t[g->pile_tuile.som]->pos[1]=-1;
                g->pile_tuile.som --;
                for (i=0; i<6; i++){
                    free(liste_ter[i]);
                }
                free(liste_ter);
                if (a==1) printf("la nouvelle tuile recouvre complètement une tuile déjà posée du plateau\n");
                return 0;
            }
        }
    }

    g->pile_tuile.t[g->pile_tuile.som]->pos[0]=-1;
    g->pile_tuile.t[g->pile_tuile.som]->pos[1]=-1;
    g->pile_tuile.som --;
    for (i=0; i<6; i++){
        free(liste_ter[i]);
    }
    free(liste_ter);

    return 1;
}

/**
*\brief on vérifie pour une nouvelle tuile qu'elle ne recouvre pas une case Ressouce
*\param  grille g, tuile t et les position de cette tuile x et y
*\return 1 si la règle est respectée et 0 sinon
*/
int test_recouvert_R(grille g, tuile t, int x, int y)
{
  if (t->ort == '^'){
    return (g->matrix[x][y] != 'R'&&g->matrix[x+1][y] != 'R'&&g->matrix[x+2][y] != 'R'&&g->matrix[x][y+1] != 'R'&&g->matrix[x+1][y+1] != 'R'&&g->matrix[x+2][y+1] != 'R');
  }
  else if (t->ort == 'v'){
    return (g->matrix[x][y] != 'R'&&g->matrix[x-1][y] != 'R'&&g->matrix[x-2][y] != 'R'&&g->matrix[x][y-1] != 'R'&&g->matrix[x-1][y-1] != 'R'&&g->matrix[x-2][y-1] != 'R');
  }
  else if (t->ort == '<'){
    return (g->matrix[x][y] != 'R'&&g->matrix[x][y+1] != 'R'&&g->matrix[x][y+2] != 'R'&&g->matrix[x-1][y] != 'R'&&g->matrix[x-1][y+1] != 'R'&&g->matrix[x-1][y+2] != 'R');
  }
  else{
    return (g->matrix[x][y] != 'R'&&g->matrix[x][y-1] != 'R'&&g->matrix[x][y-2] != 'R'&&g->matrix[x+1][y] != 'R'&&g->matrix[x+1][y-1] != 'R'&&g->matrix[x+1][y-2] != 'R');
  }
}
/**
*\brief on vérifie pour une nouvelle tuile qu'elle ne recouvre pas une case Usine
*\param  grille g, tuile t et les position de cette tuile x et y
*\return 1 si la règle est respectée et 0 sinon
*/
int test_recouvert_U(grille g, tuile t, int x, int y)
{
  if (t->ort == '^'){
    return (g->matrix[x][y] != 'U'&&g->matrix[x+1][y] != 'U'&&g->matrix[x+2][y] != 'U'&&g->matrix[x][y+1] != 'U'&&g->matrix[x+1][y+1] != 'U'&&g->matrix[x+2][y+1] != 'U');
  }
  else if (t->ort == 'v'){
    return (g->matrix[x][y] != 'U'&&g->matrix[x-1][y] != 'U'&&g->matrix[x-2][y] != 'U'&&g->matrix[x][y-1] != 'U'&&g->matrix[x-1][y-1] != 'U'&&g->matrix[x-2][y-1] != 'U');
  }
  else if (t->ort == '<'){
    return (g->matrix[x][y] != 'U'&&g->matrix[x][y+1] != 'U'&&g->matrix[x][y+2] != 'U'&&g->matrix[x-1][y] != 'U'&&g->matrix[x-1][y+1] != 'U'&&g->matrix[x-1][y+2] != 'U');
  }
  else{
    return (g->matrix[x][y] != 'U'&&g->matrix[x][y-1] != 'U'&&g->matrix[x][y-2] != 'U'&&g->matrix[x+1][y] != 'U'&&g->matrix[x+1][y-1] != 'U'&&g->matrix[x+1][y-2] != 'U');
  }
}
/**
*\brief on vérifie pour une nouvelle tuile qu'elle ne recouvre pas une case Forest
*\param  grille g, tuile t et les position de cette tuile x et y
*\return 1 si la règle est respectée et 0 sinon
*/
int test_recouvert_F(grille g, tuile t, int x, int y)
{
  if (t->ort == '^'){
    return (g->matrix[x][y] != 'F'&&g->matrix[x+1][y] != 'F'&&g->matrix[x+2][y] != 'F'&&g->matrix[x][y+1] != 'F'&&g->matrix[x+1][y+1] != 'F'&&g->matrix[x+2][y+1] != 'F');
  }
  else if (t->ort == 'v'){
    return (g->matrix[x][y] != 'F'&&g->matrix[x-1][y] != 'F'&&g->matrix[x-2][y] != 'F'&&g->matrix[x][y-1] != 'F'&&g->matrix[x-1][y-1] != 'F'&&g->matrix[x-2][y-1] != 'F');
  }
  else if (t->ort == '<'){
    return (g->matrix[x][y] != 'F'&&g->matrix[x][y+1] != 'F'&&g->matrix[x][y+2] != 'F'&&g->matrix[x-1][y] != 'F'&&g->matrix[x-1][y+1] != 'F'&&g->matrix[x-1][y+2] != 'F');
  }
  else{
    return (g->matrix[x][y] != 'F'&&g->matrix[x][y-1] != 'F'&&g->matrix[x][y-2] != 'F'&&g->matrix[x+1][y] != 'F'&&g->matrix[x+1][y-1] != 'F'&&g->matrix[x+1][y-2] != 'F');
  }
}
/**
*\brief on vérifie pour une nouvelle tuile qu'elle ne recouvre pas une case Ville
*\param  grille g, tuile t et les position de cette tuile x et y
*\return 1 si la règle est respectée et 0 sinon
*/
int test_recouvert_V(grille g, tuile t, int x, int y)
{
  if (t->ort == '^'){
    return (g->matrix[x][y] != 'V'&&g->matrix[x+1][y] != 'V'&&g->matrix[x+2][y] != 'V'&&g->matrix[x][y+1] != 'V'&&g->matrix[x+1][y+1] != 'V'&&g->matrix[x+2][y+1] != 'V');
  }
  else if (t->ort == 'v'){
    return (g->matrix[x][y] != 'V'&&g->matrix[x-1][y] != 'V'&&g->matrix[x-2][y] != 'V'&&g->matrix[x][y-1] != 'V'&&g->matrix[x-1][y-1] != 'V'&&g->matrix[x-2][y-1] != 'V');
  }
  else if (t->ort == '<'){
    return (g->matrix[x][y] != 'V'&&g->matrix[x][y+1] != 'V'&&g->matrix[x][y+2] != 'V'&&g->matrix[x-1][y] != 'V'&&g->matrix[x-1][y+1] != 'V'&&g->matrix[x-1][y+2] != 'V');
  }
  else{
    return (g->matrix[x][y] != 'V'&&g->matrix[x][y-1] != 'V'&&g->matrix[x][y-2] != 'V'&&g->matrix[x+1][y] != 'V'&&g->matrix[x+1][y-1] != 'V'&&g->matrix[x+1][y-2] != 'V');
  }
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structgrille.h"


/**
 *\brief Alloue DYNAMIQUEMENT et INITIALISE UNE GRILLE
 *\param taille >= 5
 *\return une grille g de taille n
 */
 grille create(int n){
   int i,j;
   grille g = (grille)malloc(sizeof(struct grille_s));
   g->size = n;
   g->pile_tuile = init();
   g->matrix = (char**) malloc(n*sizeof(char*));
   for(i = 0; i < n; i++) {
     char* line = (char*) malloc(n * sizeof(char));
     g->matrix[i] = line;
     for(j = 0; j < n; j++) {
       g->matrix[i][j]='.';
     }
   }
   tuile t = ini_tuile();
   t->ort = '<';
   t->num = -1;
   inser_tuile(g,t,(int)(n+1)/2, (int)(n-1)/2);
 	 return g ;
 }




/**
 *\brief LIBERE L ESPACE MEMOIRE DE LA GRILLE
 *\param la grille à libérer
 *\return void
 */
void destroy(grille g){
  int i;
  for(i = 0; i < g->size; i++) {
     free(g->matrix[i]);
  }
  free(g->matrix);
  free(g->pile_tuile.t[0]);
  free(g);
}



/*int main(){
  int i,j;
  srand(time(NULL));
  grille g = create(7);
  for (i=0; i<7; i++){
    for (j=0; j<7; j++){
      printf("%2c ",g->matrix[i][j]);
    }
    printf("\n");
  }
  tuile t = ini_tuile();
  inser_tuile(g,t,1,1);
  printf("\n\n\n");
  for (i=0; i<7; i++){
    for (j=0; j<7; j++){
      printf("%2c ",g->matrix[i][j]);
    }
    printf("\n");
  }
  printf("(%d,%d)\n",g->pile_tuile.t[0]->pos[0],g->pile_tuile.t[0]->pos[1] );
  return 0;
}*/

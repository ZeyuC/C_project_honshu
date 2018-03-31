#include<stdio.h>
#include<stdlib.h>

#include "../lotA/structure.h"
#include "../lotA/structgrille.h"
#include "../lotA/structure.h"
#include "recouvrement.h"

int main(){
  /*int i,j ;

  int size = 8 ;
  grille g = create(8) ;

  printf("\n\n\tab Bienvenue sur le plateau Honshu\n");
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      printf(" %c",g->matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");*/
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
    
  destroy(g) ;
  return 0 ;
}


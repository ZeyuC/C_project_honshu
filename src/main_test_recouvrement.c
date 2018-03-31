#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include "lotA/structure.h"
#include "lotA/structgrille.h"
#include "lotA/structure.h"
#include "lotB/recouvrement.h"

int main()
{
  int i,j ;

  int size = 7 ;
  grille g = create(size) ;

  /*printf("\n\n\tab Bienvenue sur le plateau Honshu\n");
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      printf(" %c",g->matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");*/
  
  /* test le ficher recouvrement.h*/
   srand(time(NULL));
   for (i=0; i<size; i++){
        for (j=0; j<size; j++){
            printf("%2c ",g->matrix[i][j]);
        }
        printf("\n");
    }
    tuile t = ini_tuile();
   inser_tuile(g,t,1,1);
    printf("\n\n\n");
    for (i=0; i<size; i++){
        for (j=0; j<size; j++){
            printf("%2c ",g->matrix[i][j]);
        }
        printf("\n");
    }
   
    int n ;

    n= nombre_recouvert(g);
    printf("le nombre recouvert %d\n",n);
   
    terrain ter1 =(terrain)malloc(sizeof(terrain)*n);
    ter1= ter_recouvert(g,n);
    printf("les terrain recouvert sont : \n");
    for (i = 0; i < n; ++i)
    {
      printf("x : %d y : %d type : %c\n",ter1[i].x,ter1[i].y,ter1[i].type);
    }
    tuile t1 = ini_tuile(1,1);
    rot_tuile(t1,'<');
    terrain ter2 =(terrain)malloc(sizeof(terrain)*6);

    ter2 = ter_recouvert_tuile(g,t1);

    inser_tuile(g,t1,1,1);

    
    for (i=0; i<7; i++){
        for (j=0; j<7; j++){
            printf("%2c ",g->matrix[i][j]);
        }
        printf("\n");
   }

    printf("les terrain où on veux poser sont recouvert par : \n");
    for (i = 0; i < 6; ++i)
    {
      printf("x : %d y : %d type : %c\n",ter2[i].x,ter2[i].y,ter2[i].type);
    }

    tuile t2 = ini_tuile(1,1);
    printf("%d\n",test_recouvert(g,t2));
    inser_tuile(g,t2,1,1);
    printf("ressusir\n");
    destroy(g) ;
    return 0 ;
}


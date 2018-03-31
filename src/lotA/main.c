#include<stdio.h>
#include<stdlib.h>


#include "structgrille.c"
#include "structuile.c"
#include "structure.c"
#include "pile.c"


/**
 *\brief affiche la grille
 *\param g : grille ,\param size : taille de la grille
 */
void affichegrille(grille g,int size){
  int i,j ;
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      printf(" %c",g->matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

/**
 *\brief affiche les tuiles restantes
 *\param t : tableau de tuile ,\param nbtuile : nombre de tuile
 */
void affichepiletuile(tuile* t,int nbtuile){
  int i,j,k ;
  for(i=0;i<nbtuile;i++){
    printf("%d    ",i);
  }
  printf("\n");

  for( i=0;i<3;i++){
    for(k=0;k<nbtuile;k++){
      for(j=0;j<2;j++){
        printf("%c ",t[k]->point[i][j]);
      }printf(" ");
    }printf("\n");
  }
  printf("\n");
}

/**
 *\brief donne la tuile de numéro num
 *\param pt pile de tuile, \param num : le numero de la tuile désiré
 *\return la tuile de numéro \param num
 */
tuile recupere(pile pt,int num){
  int i;
  for(i=0;i<pt.som;i++){
    if(pt.t[i]->num == num ){
      return pt.t[i] ;
    }
  }
  return NULL;
}

/**
 *\brief affiche la tuile t
 *\param t : une tuile
 */
void affichetuile(tuile t){
  int i,j ;
  for(i=0;i<3;i++){
    for(j=0;j<2;j++){
      printf("%c ",t->point[i][j]);
    }
    printf("\n");
  }
}

int main(){

  printf("\n\n\nBienvenue sur le plateau Honshu\n\n");
  /*
    tuile t = (tuile)malloc(sizeof(tuile));*/

  int nbt = 5 ;
  pile pt = initi_tuiles(nbt);

  int size = 8 ;
  grille g = create(size) ;

  int numerotuile ;
  char ort ;

  int findujeu = 0 ; /* vaut 0 au départ et devient 1 quand le jeu finit */

  while(findujeu==0){

    affichegrille(g,size);
    affichepiletuile(pt.t,nbt);



    while( numerotuile<0 || numerotuile>nbt){
      printf("Choix de la tuile numéro :  ");
      scanf(" %d",&numerotuile);
    }
    /*
    t = recupere(pt,numerotuile);
    affichetuile(t);*/


    while( ort != '^' || ort != 'v'  || ort != '<'  || ort != '>'){
      printf("Entrez un des 4 caractères suivant : v , < , > , ^ : ");
      scanf(" %c",&ort);
    }



    printf("\n");
  }
  destroy(g) ;
  return 0 ;
}

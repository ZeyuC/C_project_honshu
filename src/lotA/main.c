#include<stdio.h>
#include<stdlib.h>
#include<time.h>


#include "structgrille.h"
#include "../lotB/recouvrement.h"
#include "../lotC/Honshu_Opt.h"
#include "../lotD/mainSDL.h"
/*int plus_de_tuile(pile p){
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
}*/

/**
 *\brief affiche la grille
 *\param g : grille ,\param size : taille de la grille
 */
void affichegrille(grille g){
  int i,j ;

  printf("  ");
  for(i=0;i<g->size;i++){
    printf(" %d",i);
  }
  /*printf("     ");
  for(i=0;i<g->size;i++){
    printf("%3d",i);
  }*/
  printf("\n");

  for(i=0;i<g->size;i++){
    printf("%d ",i);
    for(j=0;j<g->size;j++){
      printf(" %c",g->matrix[i][j]);
    }
    printf(" %d",i);
    /*for(j=0; j<g->size; j++){
      if(g->matrix[i][j] == '.'){
        printf("%3c",g->matrix[i][j]);
      }
      else {
        printf("%3d",tuile_of(g,i,j));
      }
    }*/
    printf("\n");
  }
  printf("\n");
}

/**
 *\brief affiche les tuiles restantes
 *\param p : une pile de tuiles
 */
void affichepiletuile(pile p){
  int i,k ;
  for(i=0;i<p.som;i++){
    if( p.t[i]->pos[0] == -1){
 	printf("%5d",p.t[i]->num);
    }
  }
  printf("\n");

  for( i=0;i<3;i++){
    for(k=0;k<p.som;k++){
      if( p.t[k]->pos[0] == -1){
 	      printf("%3c",p.t[k]->point[i][0]);
 	      printf("%2c",p.t[k]->point[i][1]);
      }
    }
    printf("  ");
    printf("\n");
  }
  printf("\n");
}


/**
 *\brief donne la tuile de numéro num
 *\param pt pile de tuile, \param num : le numero de la tuile désiré
 *\return la tuile de numéro \param num si elle est dans la pile
 *\return NULL sinon
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
  srand(time(NULL));
  int i;
  for(i = 0; i < 70; i++){
    printf("\n");
  }
  printf("\n\n\nBienvenue sur le plateau Honshu\n\n");
  tuile tuile_test = ini_tuile();  /*tuile de test pour fin de partie*/
  int nbt=0 ;
  pile pt ;
  int bonne_coord,x,y;

  int size = 10 ;
  grille g = create(size) ;

  int numerotuile;
  char ort ;

  int findujeu = 0 ; /* vaut 0 au départ et devient 1 quand le jeu finit */

  int interface=-1;
 
   while(interface !=0 && interface !=1)
   {
        printf("\n\n\n Tapez 0,interface Commande\n\n");
        printf("\n\n\n Tapez 1,interface Graphique\n\n");
        scanf("%d",&interface);
   }
    if(interface==0)
    {
  /* MODE DE CHARGEMENT DES TUILES  */
  ort = 'q';
  while( ort != 'f' && ort != 'a' ){
    printf("\nTuiles random : tapez a\nTuiles chargées à partir d'un fichier : tapez f : ");
    scanf(" %c",&ort);
  }

  if(ort=='a'){
    nbt=12;
    pt = initi_tuiles(nbt) ;
  }
  else{
    char fichier[256];
    printf("\nTaper le nom du fichier : ");
    scanf("%s", fichier);
    printf("%s \n", fichier);
    FILE* fp;
    while(( fp = fopen(fichier, "r"))==NULL)
    {
      printf("le nom du fichier est faux, veuillez ressaisir: \n");
      scanf("%s", fichier);
      printf("%s \n", fichier);
    }
    pt = initi_tuile_fichier(fp,&nbt);
    i = fclose(fp);
  }
  /**********************************/


  /********** DEBUT BOUCLE DE JEU **********/
  while(findujeu==0){
    printf("\n");
    affichegrille(g);
    affichepiletuile(pt);
    printf("******************votre score mtn est %d******************\n",score(g));
    printf("\n");

    char solu;

    printf("si vous voulez regarder la solution , touchez 's',sinon touchez n'import quelles autres touches  : \n");
    getchar();
    scanf("%c",&solu);
    if(solu=='s')
    {
      pile p=pt;
     /* int best=Honshu_Opt(g,p);
      printf("the best solution est %d: \n",best);*/
      pile res = initi_tuiles(p.som);
      int best_s = solveur(g,p,res);
      printf("the new best solution est %d: \n",best_s);
     /* g->pile_tuile.som = 0;
     for (i=0; i<p.som; i++){
        inser_tuile(g,res.t[i],res.t[i]->pos[0],res.t[i]->pos[1]);
      }
      for (i=0; i<p.som; i++){
        free(res.t[i]);
      }*/
      break;
    }


    char rapple;
    printf("si vous voulez rappler les moyens pour gagner les point,touchez 'r', sinon touchez n'import quelles autres touches :  ");
    getchar(); /*pour la touche "entrer"*/
    scanf("%c",&rapple);
    if(rapple=='r')
      rappel_moyens();

    printf("\n");
    numerotuile=-1;
    while( numerotuile<0 || numerotuile>pt.som){
      printf("Choix de la tuile numéro :  ");
      scanf(" %d",&numerotuile);
    }
    if (pt.t[numerotuile]->pos[0]==-1){
      ort = 'o';
      while( ort != '^' && ort != 'v'  && ort != '<'  && ort != '>'){
        printf("Entrez un des 4 caractères suivant : v , < , > , ^ : ");
        scanf(" %c",&ort);
      }
      rot_tuile(pt.t[numerotuile],ort);
      bonne_coord = 0;
      while (!bonne_coord){
        printf("Entrez les coordonnées pour placer la tuile dans la grille.\n x : ");
        scanf(" %d", &x);
        printf(" y : ");
        scanf(" %d", &y);
        bonne_coord = add_to_grille(g,pt.t[numerotuile],x,y,1);
      }
      inser_tuile(g, pt.t[numerotuile], x, y);
      findujeu = end_of_game(g, pt, tuile_test);
    }
    else{printf("tuile déjà utilisée\n" );}
    printf("\n");
  }
  affichegrille(g);
  printf("---------------Fin de la partie---------------\n");
  free(tuile_test);
  destroy(g);
  for(i=0; i<pt.som;i++){
    free(pt.t[i]);
  }
  }
  else
  {
      nbt=12;
      pt = initi_tuiles(nbt) ;
      mainSDL(g,pt);
  }
  return 0 ;
}

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"


#include "structure.h"
/* inclus
structuile.h
structgrille.h : pile.h : structuile.h
*/

/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite(void)
{
   if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}


/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}
/* ====================== TESTS CI DESSOUS =======================*/

void test_create_grille(){
  grille g = create(8) ;
  CU_ASSERT(g->size == 8 ) ;
  CU_ASSERT(g->matrix[0][0] == '.' ) ;
  destroy(g) ;
}

void test_lecture_grille()
{
  grille g = create(8) ;
  g->matrix[0][0]='L' ;
  g->matrix[0][1]='F' ;
  g->matrix[0][2]='P' ;
  g->matrix[0][3]='V' ;
  g->matrix[0][4]='U' ;
  g->matrix[4][4]='P' ;
  g->matrix[7][7]='U' ;
  g->matrix[2][2]='R' ;

  CU_ASSERT( lecture_grille(0,0,g)=='L' ) ;
  CU_ASSERT( lecture_grille(0,1,g)=='F' ) ;
  CU_ASSERT( lecture_grille(0,2,g)=='P' ) ;
  CU_ASSERT( lecture_grille(0,3,g)=='V' ) ;
  CU_ASSERT( lecture_grille(0,4,g)=='U' ) ;
  CU_ASSERT( lecture_grille(4,4,g)=='P' ) ;
  CU_ASSERT( lecture_grille(7,7,g)=='U' ) ;
  CU_ASSERT( lecture_grille(2,2,g)=='R' ) ;

}


void test_ini_tuile_sachant(){

  tuile t = ini_tuile_sachant('F','L','P','R','U','V');

  CU_ASSERT( t->point[0][0] == 'F' ) ;
  CU_ASSERT( t->point[0][1] == 'L' ) ;
  CU_ASSERT( t->point[1][0] == 'P' ) ;
  CU_ASSERT( t->point[1][1] == 'R' ) ;
  CU_ASSERT( t->point[2][0] == 'U' ) ;
  CU_ASSERT( t->point[2][1] == 'V' ) ;

  CU_ASSERT( t->ort == '^' );

  CU_ASSERT( t->pos[0] == -1 );
  CU_ASSERT( t->pos[1] == -1 );

  CU_ASSERT( t->num == -1 ) ;
}

void test_initi_tuile_fichier(){

  FILE* fp = fopen("tuile","r");
  tuile* pilet = initi_tuile_fichier(fp) ;
  CU_ASSERT( pilet[0]->point[0][0] == 'U' ) ;
  CU_ASSERT( pilet[0]->point[0][1] == 'F' ) ;
  CU_ASSERT( pilet[0]->point[1][0] == 'R' ) ;
  CU_ASSERT( pilet[0]->point[1][1] == 'P' ) ;
  CU_ASSERT( pilet[0]->point[2][0] == 'V' ) ;
  CU_ASSERT( pilet[0]->point[2][1] == 'V' ) ;

  CU_ASSERT( pilet[1]->point[0][0] == 'P' ) ;
  CU_ASSERT( pilet[1]->point[0][1] == 'F' ) ;
  CU_ASSERT( pilet[1]->point[1][0] == 'V' ) ;
  CU_ASSERT( pilet[1]->point[1][1] == 'V' ) ;
  CU_ASSERT( pilet[1]->point[2][0] == 'V' ) ;
  CU_ASSERT( pilet[1]->point[2][1] == 'U' ) ;

  CU_ASSERT( pilet[2]->point[0][0] == 'V' ) ;
  CU_ASSERT( pilet[2]->point[0][1] == 'V' ) ;
  CU_ASSERT( pilet[2]->point[1][0] == 'F' ) ;
  CU_ASSERT( pilet[2]->point[1][1] == 'P' ) ;
  CU_ASSERT( pilet[2]->point[2][0] == 'F' ) ;
  CU_ASSERT( pilet[2]->point[2][1] == 'P' ) ;
}

void test_rot_tuile(){

  tuile t=ini_tuile();
  t->ort='^';

  CU_ASSERT(t->ort == '^' ) ;

  rot_tuile(t,'>');
  CU_ASSERT(t->ort == '>' ) ;

  rot_tuile(t,'v');
  CU_ASSERT(t->ort == 'v' ) ;

  rot_tuile(t,'<');
  CU_ASSERT(t->ort == '<' ) ;

  rot_tuile(t,'^');
  CU_ASSERT(t->ort == '^' ) ;
}


void test_inser_tuile(){
  grille g = create(8) ;
  tuile t = ini_tuile_sachant('F','L','P','R','U','V');

  inser_tuile(g,t,0,0) ; /* test tuile peut entrer entierement dans la grille */
  CU_ASSERT( g->matrix[0][0] == 'F' ) ;
  CU_ASSERT( g->matrix[0][1] == 'L' ) ;
  CU_ASSERT( g->matrix[1][0] == 'P' ) ;
  CU_ASSERT( g->matrix[1][1] == 'R' ) ;
  CU_ASSERT( g->matrix[2][0] == 'U' ) ;
  CU_ASSERT( g->matrix[2][1] == 'V' ) ;

  inser_tuile(g,t,7,0) ; /* test tuile non entierement dans la grille */
  CU_ASSERT( g->matrix[7][0] == '.' ) ;
  CU_ASSERT( g->matrix[7][1] == '.' ) ;
}


int main(){
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite, clean_suite);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }


   /*=============================*/
   /* METTRE LES TESTS DANS CE IF */
   if (
       (NULL == CU_add_test(pSuite, "Test lecture de la grille", test_lecture_grille)) ||
       (NULL == CU_add_test(pSuite, "Test rotation d'une tuile", test_rot_tuile) ) ||
       (NULL == CU_add_test(pSuite, "Test creation d'une grille", test_create_grille) ) ||
       (NULL == CU_add_test(pSuite, "Test creation d'une tuile sachant les terrains", test_ini_tuile_sachant) ) ||
       (NULL == CU_add_test(pSuite, "Test creation tuiles à partir d'un fichier", test_initi_tuile_fichier)) ||
       (NULL == CU_add_test(pSuite, "Test insertion d'une tuile", test_inser_tuile) )
 )



   {
      CU_cleanup_registry();
      return CU_get_error();
   }


   /*=============================*/

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

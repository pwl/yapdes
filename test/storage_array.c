#include "storage_array.h"

int main(int argc, char *argv[])
{
  int depth[] = {2,2};
  ODE_storage * s = ODE_storage_init_array(2, depth);
  ODE_R ** table = (ODE_R**)(s->ptrs);
  int i,j;
  
  ODE_storage_print( s );

  table[0][-1] = 1.1111111111111111111111111;

  ODE_storage_print( s );
    
  /* for( i = 0; i < 2; i++ ) */
  /*   for( j = 0; j < 3; j++ ) */
  /*     table[i][j]=(ODE_R)(i+3*j); */

  /* for( i = 0; i < s->size[1]; i++ ) */
  /*   printf("%i:" ODE_FMT "  ", i, s->data[i]); */

  ODE_storage_free(s);
  
  return 0;
}

#include "storage_array.h"

int main(int argc, char *argv[])
{
  int depth[] = {5,10};
  ODE_storage * s = ODE_storage_init_array(2, depth);
  ODE_R ** table = (ODE_R**)s->ptrs[0];
  int i,j;
  
  ODE_storage_print( s );

  for( i = 0; i < 5; i++ )
    for( j = 0; j < 10; j++ )
      table[i][j]=(ODE_R)(j+5*i);

  ODE_storage_print( s );

  ODE_storage_free(s);
  
  return 0;
}

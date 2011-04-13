#include "storage.h"

int main(int argc, char *argv[])
{
  int depth1[] = {1,2,3};
  int depth2[] = {3,2,1};
    
  ODE_storage * s1 = ODE_storage_init(3, depth1);
  ODE_storage * s2 = ODE_storage_init(3, depth2);
  /* ODE_storage * s3 = ODE_storage_init(3, depth1); */

  ODE_storage_print( s1);
  ODE_storage_print( s2);

  ODE_storage_add( s1, s2 );

  ODE_storage_print( s1);

  ODE_storage_add( s1, s2 );

  ODE_storage_print( s1);

  /* ODE_storage_add( s1, s3 ); */

  /* ODE_storage_print( s1, 1 ); */

  ODE_storage_free(s1);
  ODE_storage_free(s2);
  
  return 0;
}

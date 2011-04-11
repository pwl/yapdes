#include "storage.h"

int main(int argc, char *argv[])
{
  int depth[] = {2,2,3};
  
  ODE_storage * s1 = ODE_storage_init(3, depth);
  ODE_storage * s2 = ODE_storage_init(3, depth);

  ODE_storage_print( s1, 1 );
  ODE_storage_print( s2, 1 );

  ODE_storage_add( s1, s2 );

  ODE_storage_print( s1, 1 );

  ODE_storage_free(s1);
  ODE_storage_free(s2);
  
  return 0;
}

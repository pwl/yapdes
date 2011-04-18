#include "storage.h"

int main(int argc, char *argv[])
{
  int depth1[] = {1,1,1};
  int depth2[] = {1,1,1};
  int depth3[] = {2,3,4};

  ODE_storage * s1 = ODE_storage_init(3, depth1);
  ODE_storage * s2 = ODE_storage_init(3, depth2);
  ODE_storage * s3 = ODE_storage_init_array(3, depth3);
  ODE_storage * s4 = ODE_storage_copy( s3 );

  printf("\nStorage n. 1\n");
  ODE_storage_print( s1);
  printf("\nStorage n. 2\n");
  ODE_storage_print( s2);

  ODE_storage_add( s1, s2 );

  printf("\nStorage n. 1 + Storage n. 2\n");
  ODE_storage_print( s1);


  ODE_storage_add( s1, s2 );

  printf("\nStorage n. 1 + Storage n. 2 + Storage n. 2\n");
  ODE_storage_print( s1);

  ODE_storage_add( s1, s2 );

  printf("\nStorage n. 1 + Storage n. 2 + Storage n. 2 + Storage n. 2\n");
  ODE_storage_print( s1);

  printf("\nStorage n. 3\n");
  ODE_storage_print( s3 );

  printf("\nStorage n. 4 (should be a copy of s3)\n");
  ODE_storage_print( s4 );

  ODE_storage_add( s3, s4 );
  
  printf("\nStorage n. 3 + Storage n. 4\n");
  ODE_storage_print( s3 );
    
  ODE_storage_free(s1);
  ODE_storage_free(s2);
  ODE_storage_free(s3);
  ODE_storage_free(s4);
  
  return 0;
  
}

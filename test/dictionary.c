#include "dictionary.h"


int main(int argc, char *argv[])
{
  ODE_dictionary * d = ODE_dictionary_init( );
  int abcd=0, bbbb=1, cdef=100;

  ODE_dictionary_set_index(d, abcd, 'abcd' );
  ODE_dictionary_set_index(d, bbbb, 'bbbb' );
  ODE_dictionary_set_index(d, cdef, 'cdef' );
  

  if( abcd == ODE_dictionary_get_index(d, 'abcd' ) &&
      bbbb == ODE_dictionary_get_index(d, 'bbbb' ) &&
      cdef == ODE_dictionary_get_index(d, 'cdef' ))
    {
      printf("everything is fine!\n");
      ODE_dictionary_free( d );
      return 0;
    }
  else
    {
      ODE_dictionary_free( d );
      return 1;
    }
  
}

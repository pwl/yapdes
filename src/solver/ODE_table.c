#include "ODE_table.h"

ODE_table * ODE_table_init( int length )
{
  ODE_table * t = ODE_MALLOC( 1, ODE_table );
  t->table = ODE_MALLOC( length, ODE_R );
  return t;
}


void ODE_table_free( ODE_table * t )
{
  free( t->table );
  free( t );
}

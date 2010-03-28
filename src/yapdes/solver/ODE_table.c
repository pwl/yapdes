#include "ODE_table.h"

ODE_table * ODE_table_init( int length )
{
  ODE_table * t = malloc( sizeof( ODE_table ) );
  t->table = malloc( length * sizeof( ODE_R ) );
  return t;
}


void ODE_table_free( ODE_table * t )
{
  free( t->table );
  free( t );
}

#include "ODE_splitted_table.h"

ODE_splitted_table * ODE_splitted_table_init( int N, int * length )
{
  int i;
  ODE_splitted_table * st =
    malloc( sizeof( ODE_splitted_table ) );

  for( i = 0; i < N; i++)
    {
      st->table[i]=malloc( length[i] * sizeof( ODE_R ) );
      st->length[i]=length[i];
    }

  return st;
}

void ODE_splitted_table_free( ODE_splitted_table * st )
{
  int i;
  for( i = 0; i < st->N; i++)
    {
      free( st->table[i] );
    }

  free( st->length );
  free( st );
}

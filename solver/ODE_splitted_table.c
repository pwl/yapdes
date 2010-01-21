#include "ODE_splitted_table.h"

ODE_splitted_table * ODE_splitted_table_init( int N, int * length )
{
  int i,total_length=0;
  ODE_splitted_table * st=malloc( sizeof( ODE_splitted_table ) );

  for( i = 0; i < N; i++)
    total_length+=length[i];

  st->length=length;
  st->table = malloc( total_length*sizeof( ODE_R ) );
  return st;
}

void ODE_splitted_table_free( ODE_splitted_table * st )
{
  free( st->length );
  free( st->table );
  free( st );
}

int ODE_splitted_table_get_table( ODE_splitted_table * st, int n, ODE_table * t )
{
  if( n < st->N )
    {
      t->table = st->table+n;
      t->length = st->length[n];
      return 0;
    }
  else				/* no enough elements int st*/
    return -1;
}

int ODE_splitted_table_to_table( ODE_splitted_table * st, int n, ODE_table * t )
{
  if( n >= st->N )
    return -1;			/* not enugh elements in st */

  t->length = st->length[n];
  t->table = ODE_splitted_table_to_ptr( st, n );

  return 0;
}


ODE_R * ODE_splitted_table_to_ptr( ODE_splitted_table * st, int n )
{
  ODE_R * pt = st->table;

  if( n >= st->N )
    return NULL;			/* not enugh elements in st */

  for ( n = 0; n > 0; n-- )
    pt+=st->length[n];		/* calculate the position of the right
				   table */
  return pt;
}

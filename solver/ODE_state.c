#include "ODE_state.h"


ODE_state * ODE_state_init ( int N, int * length )
{
  ODE_state * st = malloc( sizeof( st ) );
  st->f = ODE_splitted_table_init( N, length );
  st->df = ODE_splitted_table_init( N, length );
  /* some default values to be changed by the stepper or obtained from
     file later on */
  st->dt=1.;
  st->t=0.;
  st->i=0;
  return st;
}

void ODE_state_free ( ODE_state * st)
{
  ODE_splitted_table_free( st->f );
  ODE_splitted_table_free( st->df );
  free( st );
}

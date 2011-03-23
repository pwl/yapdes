#include "module_state_init.h"

int module_state_init_start ( ODE_module * m )
{
  printf("MM: module_state_init [start]\n");

  m->solver->state = ODE_state_init( *(ODE_uint *)(m->data) );

  return 0;
}

int module_state_init_step ( ODE_module * m )
{
  printf("MM: module_state_init [step]\n");

  return 0;
}

int module_state_init_stop ( ODE_module * m )
{
  printf("MM: module_state_init [stop]\n");

  /* state has to be freed in order to restart module appropriately */
  ODE_state_free( m->solver->state );

  return 0;
}

int module_state_init_free( ODE_module * m )
{
  /* printf("MM: module_state [free]\n"); */

  free( m->data );

  return 0;
}

ODE_module * ODE_module_state_init_init ( ODE_uint size )
{
  ODE_module * m = ODE_module_init ();

  sprintf( m->type, "State_Init" );

  m->data = (void *)malloc( sizeof( ODE_uint ) );
  *(ODE_uint *)(m->data) = size;


  m->start =
    module_state_init_start;
  m->step =
    module_state_init_step;
  m->stop =
    module_state_init_stop;
  m->free =
    module_state_init_free;

  return m;
}

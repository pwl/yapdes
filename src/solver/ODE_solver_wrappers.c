#include "ODE_solver_wrappers.h"

ODE_solver * ODE_solver_wrapper_state( ODE_uint size )
{
  ODE_solver * s = ODE_solver_init( );
  ODE_module * mstate = ODE_module_state_init_init( size );

  ODE_solver_add_module( s, mstate );

  return s;
}


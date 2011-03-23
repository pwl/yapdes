#include "ODE_solver.h"

ODE_solver * ODE_solver_init ( void )
{
  ODE_solver * s = malloc( sizeof( ODE_solver ) );

  s->module_bundle = ODE_module_bundle_init( s, MODULE_BUNDLE_MAX_MODULES );

  s->state = NULL;

  s->status = SOLVER_ST_INITIALIZED
    | SOLVER_ST_MODULES_READY;	/* what stage of solving the
				     equation are we? */
  return s;
}

int ODE_solver_run ( ODE_solver * s )
{
  ODE_module_bundle_start( s->module_bundle );

  while( s->status & SOLVER_ST_READY && 0 ) /* temporarly disabled due
					       to && 0 */
    {
      ODE_module_bundle_step( s->module_bundle );
      /* stepper is going to be called here */
    }
  /* One more step for modules for the call pattern to look like this:
     m,s,m,s,...,m,s,m where m is a module and s is a step. In other
     words, simulation ends with a module call.
   */
  ODE_module_bundle_step( s->module_bundle );

  ODE_module_bundle_stop( s->module_bundle );

  return 0;
}

void ODE_solver_free (ODE_solver * s)
{
  /* @todo free only properly initalized modules */
  ODE_module_bundle_free( s->module_bundle );

  if( s->state )
    ODE_state_free( s->state );

  free( s );
}

void ODE_solver_add_module ( ODE_solver * s, ODE_module * m )
{
  ODE_module_bundle_add_module( s->module_bundle, m );
}

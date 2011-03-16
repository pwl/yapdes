#include "ODE_solver.h"

ODE_solver * ODE_solver_init ( void )
{
  ODE_solver * s = malloc( sizeof( ODE_solver ) );

  s->module_bundle = ODE_module_bundle_init( s, MODULE_BUNDLE_MAX_MODULES );

  s->status = SOLVER_ST_INITIALIZED
    | SOLVER_ST_MODULES_READY;	/* what stage of solving the
				     equation are we? */
  return s;
}

int ODE_solver_run ( ODE_solver * s )
{
  s->run_time = MODULE_RUN_START;
  ODE_module_bundle_run( s->module_bundle, MODULE_RUN_START );

  while( s->status & SOLVER_ST_READY && 0 ) /* temporarly disabled due
					       to && 0 */
    {
      ODE_module_bundle_run( s->module_bundle, MODULE_RUN_STEP );
      /* stepper is going to be called here */
    }

  ODE_module_bundle_run( s->module_bundle, MODULE_RUN_STOP );

  return 0;
}

void ODE_solver_free (ODE_solver * s)
{
  /* @todo free only properly initalized modules */
  ODE_module_bundle_free( s->module_bundle );

  ODE_state_free( s->state );

  free( s );
}


#include "ODE_solver.h"

ODE_solver * ODE_solver_init ( void )
{
  ODE_solver * s = malloc( sizeof( ODE_solver ) );
  s->modules = malloc( MAX_MOD_NUMB * sizeof( ODE_module * ) );
  s->mod_num = 0;		/**< number of modules loaded */
  s->run_time = SOLVER_RUN_NOT_RUNNING; /**< what stage of running are we? */
  s->status = SOLVER_ST_INITIALIZED
    | SOLVER_ST_MODULES_READY;	/**< what stage of solving the
				     equation are we? */
  return s;
}

/* TODO: send some information about which module failed to
   initialize, e.g. module number, print module name etc. */
int ODE_solver_modules_init( ODE_solver * s )
{
  int i;
  int ret_val;
  ODE_module * m;

  /* checks weather modules initialized properly */
  for (i = 0; i < s->mod_num; ++i)
    {
      m = s->modules[i];
      if( (ret_val =  m->init( m )) < 0 )
	return ret_val;
    }

  return 0;
}

int ODE_solver_modules_free( ODE_solver * s )
{
  int i;
  ODE_module * m;
  int ret_val;

  for (i = 0; i < s->mod_num; ++i)
    {
      m = s->modules[i];
      if( (ret_val = m->free( m )) < 0 ||
	  (ret_val = ODE_module_free_common( m )) < 0 )
	return ret_val;
    }

  return 0;
}

int ODE_solver_modules_run( ODE_solver * s )
{
  int i;
  ODE_module * m;

  for (i = 0; i < s->mod_num; ++i)
    {
      m = s->modules[i];
      /* TODO: do something with the return value of this, print, log? */
      ODE_module_run_common( m );
    }

  return 0;
}

/* TODO: inform the user or log! */
int ODE_solver_add_module( ODE_solver * s, ODE_module * m )
{
  int ret_val;

  /* too many modules are loaded */
  if ( s->mod_num >= MAX_MOD_NUMB )
    return -1;			/* the return value may be confusing
				   and overlap the return code of
				   module in the line below */

  /* module failed to initalize */
  if( (ret_val = m->init( m ) ) < 0 )
    return ret_val;

  /* if everything went right module is added to solver */
  s->modules[s->mod_num] = m;
  s->mod_num++;
  m->solver = s;

  return 0;
}

int ODE_solver_run ( ODE_solver * s )
{
  s->run_time = SOLVER_RUN_START;
  ODE_solver_modules_run( s );

  s->run_time = SOLVER_RUN_STEP;
  while( s->status & SOLVER_ST_READY && 0 )
    {
      /* stepper is going to be called here */
      ODE_solver_modules_run( s );
    }

  s->run_time = SOLVER_RUN_STOP;
  ODE_solver_modules_run( s );

  return 0;
}

void ODE_solver_free (ODE_solver * s)
{
  /* free any of the properly initalized modules */
  ODE_solver_modules_free( s );

  /* free the module list */
  free( s->modules );

  /* if any module has initialized state then free it */
  if ( s->status & SOLVER_ST_STATE_READY )
    ODE_state_free( s->state );

  free( s );
}


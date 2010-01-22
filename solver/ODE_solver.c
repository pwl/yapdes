#include "ODE_solver.h"

ODE_solver * ODE_solver_init ( void )
{
  ODE_solver * s = malloc( sizeof( ODE_solver ) );
  s->modules = malloc( MAX_MOD_NUMB * sizeof( ODE_module * ) );
  s->mod_num = 0;		/**< number of modules loaded */
  s->run_time = SOLVER_RUN_NOT_RUNNING; /**< what stage of running are we? */
  s->status = SOLVER_ST_INITIALIZED; /**< what stage of solving the
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
  int ret_val;

  for (i = 0; i < s->mod_num; ++i)
    {
      m = s->modules[i];
      if( ODE_module_run_triggers( m ) ) /* this will run the
					    triggers and find out if
					    module shall be run */
	if( (ret_val = m->run( m )) < 0 )
	  /* printf("here\n"); */
	  return ret_val;
    }

  return 0;
}

/* TODO: inform the user, or log! */
int ODE_solver_add_module( ODE_solver * s, ODE_module * m )
{
  /* too many modules are loaded */
  if ( s->mod_num >= MAX_MOD_NUMB )
    return 1;

  else
    {
      s->modules[s->mod_num] = m;
      s->mod_num++;
      m->solver = s;
    }
  return 0;
}

int ODE_solver_run ( ODE_solver * s )
{
  /* initialize modules and set the apropriate solver status */
  if ( ODE_solver_modules_init( s ) < 0 )
    return -1;

  s->status |= SOLVER_ST_MODULES_READY;

  s->run_time = SOLVER_RUN_START;
  ODE_solver_modules_run( s );

  return 0;
}

void ODE_solver_free (ODE_solver * s)
{
  if ( s->status & SOLVER_ST_MODULES_READY )
    ODE_solver_modules_free( s );

  free( s->modules );

  if ( s->status & SOLVER_ST_STATE_READY )
    ODE_state_free( s->state );

  free( s );
}


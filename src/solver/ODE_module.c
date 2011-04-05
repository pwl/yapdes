#include "solver/ODE_module.h"

ODE_module * ODE_module_init ( void )
{
  ODE_module * m = malloc( sizeof( ODE_module ) );

  m->times_run = 0;

  m->trigger_bundle = ODE_trigger_bundle_init( m, MAX_TRIG_NUMB );

  m->data = NULL;
  m->solver = NULL;

  m->start = NULL;
  m->step = NULL;
  m->stop = NULL;
  m->free = NULL;

  m->state = MODULE_STOPPED;

  return m;
}

void ODE_module_start( ODE_module * m )
{
  switch( m->state )
    {
    case MODULE_STOPPED:
      /* check the health status of the module (in particular if the
	 trigger_bundle and solver are assigned), if module fails this
	 test it shall not be run at all. Sanity test returns
	 TRUE/FALSE */
      /** @todo report an error! */
      if( ! ODE_module_sanity_check( m ) )
	m->state = MODULE_ERROR;

      /* if a module does not have a start function do not run it,
	 only change the state */
      else if( ! m->start )
	m->state = MODULE_STARTED;

      /* module has a start function, check weather it performed
	 well and change the state accordingly */
      else if ( ! m->start( m ) )
	{
	  /* set module state, now its ready to run m->step(m) */
	  m->state = MODULE_STARTED;
	  /* starting triggers does not return any value! */
	  ODE_trigger_bundle_start( m->trigger_bundle );
	}

      /* this is the case when m->start exists, but it returned an
	 error in the previous 'else if' */
      else
	m->state = MODULE_ERROR;
      break;

      /* module has already started, do nothing */
    case MODULE_STARTED:
      break;

      /* ignore broken modules */
    case MODULE_ERROR:
      break;
    }

}

void ODE_module_step( ODE_module * m )
{
  switch( m->state )
    {
      /* only started modules can do a step() action */
    case MODULE_STARTED:
      /* if a module does not have a step function break */
      if( ! m->step )
	break;
      /* else check the triggers */
      else if( ODE_trigger_bundle_test ( m->trigger_bundle ) )
	{
  	  /* check if module was activated without an error */
	  if ( ! m->step( m ) )
	    m->times_run++;
	  /* if not, switch its status to ERROR, it will be run no
	     more */
	  /** @todo an error should be logged */
	  else
	    m->state = MODULE_ERROR;
	}
      break;
      /* if module is not started or is broken it cannot be run */
    case MODULE_STOPPED:
    case MODULE_ERROR:
      break;
    }
}

/** @todo make triggers more efficient by caching test results */
void ODE_module_stop( ODE_module * m )
{

  /* printf("\nstopping module\n"); */
  /* ODE_module_print(m); */
  /* module which is not corretcly initialized or suffered an errer
     should not be stopped, as it might result in further errors. In
     such case memory leaks or unclosed files are possible to
     show up */
  switch( m->state )
    {
      /* only a started module can be stopped */
    case MODULE_STARTED:
      /* if a module does not have a stop function do nothing apart
	 from changing its state */
      if( ! m->stop )
	m->state = MODULE_STOPPED;

      /* stop function exists and it is run to stop the module */
      else if( ! m->stop( m ) )
	m->state = MODULE_STOPPED;

      /** @todo report an error */
      else
	m->state = MODULE_ERROR;

      break;

      /** @todo this is not a right way to do it, there should be an
	  additional status for a module which has trigger_bundle
	  initialized */
    case MODULE_ERROR:
      /* If m->trigger_bundle is not NULL try to stop the triggers but
	 dont change state of the module */
      if ( m->trigger_bundle )
	ODE_trigger_bundle_stop( m->trigger_bundle );
      break;
    case MODULE_STOPPED:
      break;
    }
  /* ODE_module_print(m); */
}

void ODE_module_free ( ODE_module * m )
{
  /* @todo after adding a state corresponding to a non initialized
     trigger_bundle it should be used here */
  /* @todo someting @e essentially wrong is going on here, an attempt
     to free a started module should not be left like that. Altough
     this should normally not happen as all triggers/modules are
     stopped @e before memory being released (this should be
     guaranteed by solver). */

  switch( m->state )
    {
      /* Module is broken, but we can try to close files and free
	 memory if it is possible. A procedure for a stopped module is
	 exactely the same. */
    case MODULE_ERROR:
      /* module is still running, clean free is potentially harmful,
	 something went very wrong, @todo report */
      /* @todo possible fix: call ODE_module_stop(m) and continue, it
	 would be good to do that @e before entering switch, as it
	 wont have any impact on states ERROR and STOPPED, just in
	 case. It might however, be a possible double to another ODE_module_stop()
	 and should be cleaned up definitely. The same goes to ODE_trigger_free(). */
    case MODULE_STARTED:
      break;
    case MODULE_STOPPED:
      if ( m->trigger_bundle )
	ODE_trigger_bundle_free( m->trigger_bundle );
      if ( m->free )
	m->free( m );
      break;
    }
  free( m );
}


/* you can add a trigger to a module which is in ERROR state */
void ODE_module_add_trigger (ODE_module * m, ODE_trigger * t)
{
  switch( m->state )
    {
      /* just add the trigger without altering its state */
    case MODULE_STOPPED:
      ODE_trigger_bundle_add_trigger( m->trigger_bundle, t );
      /* add the trigger and try to start it */
    case MODULE_STARTED:
      ODE_trigger_bundle_add_trigger( m->trigger_bundle, t );
      ODE_trigger_start( t );
      /* do not add a trigger to a broken module */
      /** @todo report an error */
    case MODULE_ERROR:
      break;
    }
}

void ODE_module_print ( ODE_module * m )
{
  if( m->state != MODULE_ERROR)
    {
      printf("M: Type: %s\n", m->type);
      printf("M: Number of triggers assigned: %i\n", ODE_trigger_bundle_count( m->trigger_bundle ));
      printf("M: Times run: %i\n",m->times_run);
      printf("M: Data structure assigned: %s\n", m->data ? "Yes" : "No" );
      printf("M: Solver assigned: %s\n", m->solver ? "Yes" : "No" );
      printf("M: Module state: %c\n", m->state );
    }
}

int ODE_module_sanity_check( ODE_module * m )
{

  /* ODE_module_print( m ); */

  if( !( m->trigger_bundle &&	/* module should have abundle
				   assigned */
	 m->solver &&		/* and a solver as well */
	(m->start  ||		/* there is something wrong if a
				   module does not have any
				   of those functions */
	 m->stop   ||
	 m->step ) ) )
    return FALSE;

  else
    return TRUE;
}

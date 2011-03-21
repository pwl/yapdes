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

  m->state = MODULE_STOPPED;

  return m;
}

void ODE_module_start( ODE_module * m )
{
  switch( m->state )
    {
    case MODULE_STOPPED:
      {
	/* check the health status of the module (in particular if
     m->start, m->step and m->stop are non NULL or if the
     trigger_bundle is not assigned), if module fails this test it
     shall not be run at all. Sanity test returns TRUE/FALSE */
	/** @todo report an error! */
	/* change state for insane modules */
	if( ! ODE_module_sanity_test( m ) )
	  m->state = MODULE_ERROR;

	/* module started successfuly? */
	else if ( ! m->start( m ) )
	  {
	    /* set module state, now its ready to run m->step(m) */
	    m->state = MODULE_STARTED;
	    /* starting triggers does not return any value! */
	    ODE_trigger_bundle_start( m->trigger_bundle );
	  }
	break;
      }

      /* module has already been started, nothing wrong is
	 happening, do nothing */
    case MODULE_STARTED:
      break;

      /* for any other state set the module to error */
    default:
      m->state = MODULE_ERROR;
    }
}

void ODE_module_step( ODE_module * m )
{
  switch( m->state )
    {
      /* only started modules can do a step() action */
    case MODULE_STARTED:
      if( ODE_trigger_bundle_test ( m->trigger_bundle ) )
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
      /* if module is not started it cannot be run */
    case MODULE_STOPPED:
    case MODULE_ERROR:
      return;
    }
}

/** @todo make triggers more efficient by caching test results */
void ODE_module_stop( ODE_module * m )
{
  /* module which is not corretcly initialized or suffered an errer
     should not be stopped, as it might result in further errors. In
     such case memory leaks or unclosed files are possible to
     show up */
  switch( m->state )
    {
      /* only a started module can be stopped */
    case MODULE_STARTED:
      {
	if( ! m->stop( m ) )
	  m->state = MODULE_STOPPED;
	/** @todo report an error */
	else
	  m->state = MODULE_ERROR;
      }

      /** @todo this is not a right way to do it, there should be an
	  additional status for a module which has trigger_bundle
	  initialized */
    default:
      /* If m->trigger_bundle is not NULL try to stop the triggers */
      if ( m->trigger_bundle )
	ODE_trigger_bundle_stop( m->trigger_bundle );
    }
}

void ODE_module_free ( ODE_module * m )
{
  /* @todo after adding a state corresponding to non initialized
     trigger_bundle it should be used here */
  if ( m->trigger_bundle )
    ODE_trigger_bundle_free( m->trigger_bundle );

  free( m );
}


/* you can add a trigger to a module which is in ERROR state */
void ODE_module_add_trigger (ODE_module * m, ODE_trigger * t)
{
  ODE_trigger_bundle_add_trigger( m->trigger_bundle, t );
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

int ODE_module_sanity_test( ODE_module * m )
{

  ODE_module_print( m );

  if( !(m->trigger_bundle &&
	m->solver &&
	m->start &&
	m->stop &&
	m->step ) )
    return FALSE;


  else
    return TRUE;
}

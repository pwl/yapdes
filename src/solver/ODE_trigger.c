#include "ODE_trigger.h"

ODE_trigger * ODE_trigger_init ( void )
{
  ODE_trigger * mt = malloc( sizeof( ODE_trigger ) );

  /** \todo can be set to some useful value by default */
  mt->start = NULL;
  mt->stop = NULL;
  mt->test = NULL;
  mt->module = NULL;
  mt->data = NULL;

  return mt;
}

void ODE_trigger_free( ODE_trigger * tr )
{
  free( tr );
}

/* the multiple state comparisons in the following function are due to
   two facts:

   1) trigger can be already started by some other module

   2) trigger can be restarted, i.e. started after being stopped
   (e.g. during multiple runs of the same instance of a solver */
void ODE_trigger_start( ODE_trigger * tr )
{
  /* action to take depends on the state of a trigger */
  switch( tr->state )
    {
      /* trigger encountered a problem */
    case TRIGGER_ERROR: return;

      /* trigger has been already started */
    case TRIGGER_STARTED: return;

      /* if the trigger has been properly stopped or not started at all */
      /** @todo can we eliminate a status NOT_STARTED in favor of STOPPED?
	  the separation of those two states is a redundancy, because a
	  properly stopped trigger should be able to be properly started
	  in the same way a trigger with status NOT_STARTED is */
    case TRIGGER_STOPPED:
      {
	/* triggers sanity test failed */
	if( ! ODE_trigger_sanity_test( tr ) )
	  /** @todo error is now considered unrecoverable, is it
	      possible to make it partially recoverable? */
	  tr->state = TRIGGER_ERROR;
	/* trigger is sane, continue */
	else
	  {
	    /* trigger starts correctly */
	    if( ! tr->start( tr ) )
	      tr->state = TRIGGER_STARTED;
	    /* trigger could not be started */
	    else
	      tr->state = TRIGGER_ERROR;
	  }
      }
    }
}

int ODE_trigger_test( ODE_trigger * tr )
{
  switch( tr->state )
    {
    case TRIGGER_ERROR:
    case TRIGGER_STOPPED:
      return FALSE;

    case TRIGGER_STARTED:
      return tr->test( tr );

    default:
      return FALSE;
    }
}

void ODE_trigger_stop( ODE_trigger * tr )
{
  switch( tr->state )
    {
    case TRIGGER_ERROR:
    case TRIGGER_STOPPED:
      return;

    case TRIGGER_STARTED:
      {
	/* trigger successfuly stopped? */
	if( ! tr->stop( tr ) )
	  tr->state = TRIGGER_STOPPED;
	/** @todo report! */
	else
	  tr->state = TRIGGER_ERROR;
      }
    }
}


int ODE_trigger_sanity_test( ODE_trigger * tr )
{
  if( ! (tr->start &&
	 tr->stop &&
	 tr->test &&
	 tr->module &&
	 tr->solver ) )
    return FALSE;

  else
    return TRUE;
}

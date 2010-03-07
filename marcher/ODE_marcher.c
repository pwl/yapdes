#include "ODE_marcher.h"

/** 
 * This function returns a pointer to the allocated memory area to
 * the marcher for ODE system of dimension dim
 * 
 * @param dim dimension of the ODE system
 * 
 * @return pointer to the allocated ODE_marcher
 */
ODE_marcher * ODE_marcher_alloc ( ODE_uint dim )
{
  ODE_marcher *m = ( ODE_marcher* ) malloc( sizeof( ODE_marcher ) );
  
  /* checking memory allocation correctness */
  if( m==0 ) {
      ODE_ERROR( "memory allocation for ODE_marcher", 0 );
  }

  /* allocating memory for marcher components */
  /* y0 */
  m->y0 = (ODE_R *) malloc( dim*sizeof( ODE_R ) );
  if( m->y0==0 ) {
      free( m );
      ODE_ERROR( "memory allocation for y0", 0 );
  }

  /* yerr */
  m->yerr = (ODE_R *) malloc( dim*sizeof( ODE_R ) );
  if( m->yerr==0 ) {
      free( m->y0 );
      free( m );
      ODE_ERROR( "memory allocation for yerr", 0 );
  }

  /* dydt_in */
  m->dydt_in = (ODE_R *) malloc( dim*sizeof( ODE_R ) );
  if( m->dydt_in==0 ) {
      free( m->yerr );
      free( m->y0 );
      free( m );
      ODE_ERROR( "memory allocation for dydt_in", 0 );
  }

  /* dydt_out */
  m->dydt_out = (ODE_R *) malloc( dim*sizeof( ODE_R ) );
  if( m->dydt_out==0 ) {
      free( m->dydt_in );
      free( m->yerr );
      free( m->y0 );
      free( m );
      ODE_ERROR( "memory allocation for dydt_out", 0 );
  }
  
  m->dim = dim; /* Setting dimension of marcher. */
  m->count = 0;
  m->failed_steps = 0;
  m->last_step = 0.0;

  return m;
}


/* Main marcher function.
 * 
 * This function advances the ODE system y(t) to y(t+h) using the
 * stepper function. The new time i.e. step-size will be modified
 * using step control function, to ensure an error on the given level.
 *
 * The routine may make several calls to stepper function in order to
 * determine the optimum step-size.The new step size will be stored
 * in the h variable.
 *
 * The maximum time t1 is guaranteed not to be exceeded by the routine.
 * When there is a last step the value of t will be set to t1.
 * 
 * @param m pointer to the ODE_marcher
 * @param step pointer to the ODE_stepper
 * @param con pointer to the ODE_step_control
 * @param dydt pointer to the ODE_system
 * @param t pointer to the starting time 
 * @param t1 end time of integration of the ODE
 * @param h pointer to the initial step size
 * @param y array with y_i(t) values at time t, where values of y_i(t+h) will by stored
 * 
 * @return step_status
 */
int ODE_marcher_apply ( ODE_marcher * m,
                        ODE_stepper * step,
                        ODE_step_control * con,
                        const ODE_system * dydt,
                        ODE_R *t, ODE_R t1, ODE_R *h, ODE_R y[] )
{
  const ODE_R t0 = *t;
  ODE_R h0 = *h;
  int step_status;
  int final_step = 0;
  ODE_R dt = t1 - t0;  /* remaining time, possibly less than h */

  /* Preconditions checking */
  if( m->dim != step->dim ) {
      ODE_ERROR( "stepper dimension must match marcher size", 0 );
  }
  
  if( (dt < 0.0 && h0 > 0.0) || (dt > 0.0 && h0 < 0.0) ) {
      ODE_ERROR( "step direction must match interval direction", 0 );
  }
  
  /* No need to copy if we cannot control the step size. */
  if( con != NULL ) {
      _ODE_R_MEMCPY( m->y0, y, m->dim );
  }
  
  /* Calculate initial dydt once if the method can benefit. */
  if( step->type->can_use_dydt_in ) {
      int status = _ODE_FUNC_EVAL( dydt, t0, y, m->dydt_in );
      if( status ) {
          return status;
      }
  }
  
  try_step:

  /* Checking if this step is the last one */
  if ( (dt >= 0.0 && h0 > dt) || (dt < 0.0 && h0 < dt) ) {
      /* printf("I'am there \n"); */
      h0 = dt;
      final_step = 1;
  }
  else {
      final_step = 0;
  }
  
  if( step->type->can_use_dydt_in ) {
      /* Running stepper with dydt_in */
      step_status =
          ODE_stepper_apply( step, t0, h0, y, m->yerr, m->dydt_in,
                             m->dydt_out, dydt );
  }
  else {
      /* Running stepper without dydt_in */
      step_status =
          ODE_stepper_apply( step, t0, h0, y, m->yerr, NULL,
                             m->dydt_out, dydt );
  }
  
  /* Check for stepper internal failure */
  if( step_status != ODE_TRUE ) {
      *h = h0;  /* notify user of step-size which caused the failure */
      return step_status;
  }

  /* If stepper doesn't caused an error increase count and set last_step size */
  m->count++;
  m->last_step = h0;

  /* Increasing actual time */
  if( final_step ) {
      *t = t1;
      /* printf("final step t = %f\n", *t); */
  }
  else {
      *t = t0 + h0;
      /* printf("test t = %f\n", *t); */
  }
  
  /* Using adaptive step size method. */
  if( con != NULL ) {
      /* Check error and attempt to adjust the step. */
      const int hadjust_status
            = ODE_step_control_hadjust( con, step, y, m->yerr, m->dydt_out, &h0 );
      
        if( hadjust_status == ODE_STEP_HADJ_DEC ) {
            /* Step was decreased. Undo and go back to try again. */
            _ODE_R_MEMCPY( y, m->y0, dydt->dimension );
            m->failed_steps++;
            goto try_step;
        }
  }
  
  *h = h0;  /* Suggest step size for next time-step. */
  
  return step_status;
}


/** 
 * This function resets marcher.
 * 
 * @param m pointer to the ODE_marcher
 * 
 * @return This function always returns ODE_TRUE.
 */
int ODE_marcher_reset ( ODE_marcher * m )
{
  m->count = 0;
  m->failed_steps = 0;
  m->last_step = 0.0;
  return ODE_TRUE;
}


/** 
 * This function frees memory associated with the marcher.
 * 
 * @param m pointer to the ODE_marcher
 */
void ODE_marcher_free ( ODE_marcher * m )
{
  free( m->dydt_out );
  free( m->dydt_in );
  free( m->yerr );
  free( m->y0 );
  free( m );
}

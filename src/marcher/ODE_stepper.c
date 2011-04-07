#include "ODE_stepper.h"


/** 
 * This function returns a pointer to the allocated memory area for
 * the stepper with stepping method given by step type T for solving
 * ODE system of dimension dim.
 * 
 * @param T pointer to the ODE_step_type
 * @param dim dimension of the ODE system
 * 
 * @return pointer to the allocated ODE_stepper
 */
ODE_stepper * ODE_stepper_alloc ( const ODE_step_type * T, size_t dim )
{
  ODE_stepper *s = ODE_MALLOC( 1, ODE_stepper );
  
  /* checking memory allocation correctness */
  if( s==0 ) {
      _ODE_ERROR( "memory allocation for ODE_stepper", 0 );
  }
  
  s->type = T; /* pointing ODE_step_type */
  s->dim = dim; /* setting ODE_stepper dimension */
  
  /* allocating ODE_step and setting ODE_stepper state */
  s->state = s->type->alloc( dim );
  
  /* checking memory allocation correctness */
  if( s->state == 0 ) {
      free( s );
      _ODE_ERROR( "memory allocation for ODE_step_type", 0 );
  }
  
  return s;
}


/** 
 * This function apply stepper, ie. advances system from time t
 * and state y(t) to the time t+h and state y(t+h) (stored on
 * output in y). An estimated error of step algorith is stored
 * at yerr array.
 *
 * If the argument dydt_in is not null it should point an array
 * containing the derivatives for the system at time t on input.
 * This is optional as the derivatives will be computed internally
 * if they are not provided, but allows the reuse of existing
 * derivative information. On output the new derivatives of the
 * system at time t+h will be stored in dydt_out if it is not null. 
 * 
 * @param s pointer to the ODE_stepper
 * @param t actual time
 * @param h initial step size
 * @param y array with y_i(t) values at time t, where values of y_i(t+h) will by stored
 * @param yerr array with estimated error of the step algorithm
 * @param dydt_in array with derivatives for dydt system at time t 
 * @param dydt_out array with derivatives for dydt system at time t+h 
 * @param dydt pointer to the ODE_system
 * 
 * @return status of steppers type apply function int
 */
int ODE_stepper_apply ( ODE_stepper * s,
                        ODE_R t, ODE_R h,
                        ODE_R y[], ODE_R yerr[],
                        const ODE_R dydt_in[],
                        ODE_R dydt_out[],
                        const ODE_system * dydt )
{
  return s->type->apply( s->state, s->dim, t, h, y, yerr,
                         dydt_in, dydt_out, dydt );
}


/** 
 * Returns steppers type name.
 * 
 * @param s pointer to the ODE_stepper
 * 
 * @return pointer to the steppers type name
 */
const char * ODE_stepper_name ( const ODE_stepper * s )
{
  return s->type->name;
}


/** 
 * This function returns stepper type order.
 * 
 * @param s pointer to the ODE_stepper
 * 
 * @return steppers type order
 */
ODE_uint ODE_stepper_order ( const ODE_stepper * s )
{
  return s->type->order(s->state);
}


/** 
 * This function resets stepper.
 * 
 * @param s pointer to the ODE_stepper
 * 
 * @return status of steppers type reset function
 */
int ODE_stepper_reset ( ODE_stepper * s )
{
  return s->type->reset( s->state, s->dim );
}


/** 
 * This function frees memory associated with the stepper.
 * 
 * @param s pointer to the ODE_stepper
 * 
 * @return status of steppers type free function
 */
void ODE_stepper_free ( ODE_stepper * s )
{
  s->type->free( s->state );
}

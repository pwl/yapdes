#include "ODE_control.h"

/**
 * @file   ODE_control.c
 * @author Maciej Maliborski <maciej.maliborski@gmail.com>
 * @date   Fri Mar  5 21:19:06 2010
 * 
 * @brief
 *
 * Available control object constructors.
 *
 * The standard control object is a four parameter heuristic
 * defined as follows:
 *    D0 = eps_abs + eps_rel * (a_y |y| + a_dydt h |y'|)
 *    D1 = |yerr|
 *    q  = consistency order of method (q=4 for 4(5) embedded RK)
 *    S  = safety factor (0.9 say)
 *
 *                      /  (D0/D1)^(1/(q+1))  D0 >= D1
 *    h_NEW = S h_OLD * |
 *                      \  (D0/D1)^(1/q)      D0 < D1
 *
 * This encompasses all the standard error scaling methods.
 *
 * The y method is the standard method with a_y=1, a_dydt=0.
 * The yp method is the standard method with a_y=0, a_dydt=1.
 * 
 * This controller computes errors using different absolute errors for
 * each component
 *
 *    D0 = eps_abs * scale_abs[i] + eps_rel * (a_y |y| + a_dydt h |y'|)
 */


/** 
 * This function returns pointer to the allocated memory area for
 * the step control.
 * 
 * @param T pointer to the ODE_step_type
 * 
 * @return pointer to the allocated ODE_srep_control
 */
ODE_step_control * ODE_step_control_alloc ( const ODE_step_control_type * T )
{
  ODE_step_control *c = ( ODE_step_control* ) malloc( sizeof( ODE_step_control ) );
  
  /* checking memory allocation correctness */
  if( c==0 ) {
      _ODE_ERROR( "memory allocation for ODE_step_control", 0 );
  }
  
  c->type = T; /* pointing ODE_step_control_type */
    
  /* allocating ODE_step_control_type and setting ODE_step_control state*/
  c->state = c->type->alloc(); /* there was c->type->apply(), was this wrong? */
  
  /* checking memory allocation correctness */
  if( c->state == 0 ) {
      free( c );
      _ODE_ERROR( "memory allocation for ODE_step_control_type", 0 );
  }
  
  return c;
}


/** 
 * This function initializes the control function c with the above
 * parameters.
 * 
 * @param c pointer to the ODE_step_control
 * @param eps_abs absolute error
 * @param eps_rel relative error
 * @param a_y scaling factor for the system state y(t)
 * @param a_dydt scaling factor for the system derivatives y'(t)
 * 
 * @return status of step sontrol type's init function
 */
int ODE_step_control_init ( ODE_step_control * c,
                            ODE_R eps_abs, ODE_R eps_rel,
                            ODE_R a_y, ODE_R a_dydt )
{
  return c->type->init( c->state, eps_abs, eps_rel, a_y, a_dydt );
}


/** 
 * This function adjusts the step size h using the step control c
 * and the current values of y, yerr and dydt. Stepper is needed to
 * get the order of the stepping method.
 *
 * Returned values depend on whether the step was:
 *  - decreased, if the error in the y values is too large,
 *  the function returns ODE_STEP_HADJ_DEC
 *  - increased, if the error in the y values is sufficiently
 *  small, the function returns ODE_STEP_HADJ_INC
 *  - unchanged - the function returns ODE_STEP_HADJ_DEC
 *
 * The goal of the function is to estimate the largest step size which
 * satisfies the user-specified accuracy requirements for the current point. 
 * 
 * @param c pointer to the ODE_step_control
 * @param s pointer to the ODE_stepper
 * @param y array with y_i(t) values at a given time
 * @param yerr array with estimated error of the step algorithm
 * @param dydt array with derivatives at a given time
 * @param h pointer to the initial step size
 * 
 * @return status of step sontrol type's handjust function
 */
int ODE_step_control_hadjust ( ODE_step_control * c,
                               ODE_stepper * s,
                               const ODE_R y[], const ODE_R yerr[],
                               const ODE_R dydt[], ODE_R * h )
{
  return c->type->hadjust( c->state, s->dim, s->type->order( s->state ),
                           y, yerr, dydt, h );
}


/** 
 * Returns step control type name.
 * 
 * @param c pointer to the ODE_step_control
 * 
 * @return step control type name
 */
const char * ODE_step_control_name ( const ODE_step_control * c )
{
  return c->type->name;
}


/** 
 * This function frees all the memory associated with the step control
 * function c.
 * 
 * @param c pointer to the ODE_step_control
 */
void ODE_step_control_free ( ODE_step_control * c )
{
  c->type->free( c->state );
  free( c );
}

#ifndef _ODE_STEPPER_H_
#define _ODE_STEPPER_H_

#include "ODE_marcher_common.h"

typedef struct
{
  const char * name; /* step name */
  
  int can_use_dydt_in;
  int gives_exact_dydt_out;

  /* functions */
  void * (*alloc) ( size_t dim ); /* why size_t ?? can it be uint ? */
  int  (*apply) ( void * state, size_t dim,
                  ODE_R t, ODE_R h,
                  ODE_R y[], ODE_R yerr[],
                  const ODE_R dydt_in[],
                  ODE_R dydt_out[],
                  const ODE_system * dydt );
  int  (*reset) ( void * state, size_t dim );
  void (*free)  ( void * state );
  
  unsigned int  (*order) ( void * state ); /* order of stepper */

}
ODE_step_type;

typedef struct
{
  const ODE_step_type * type; /* pointer to the stepper type */
  size_t dim; /* dimension of stepper */
  void * state; /* pointer to the state of stepper of void type */ 
}
ODE_stepper;

/* Implemented step types:
 *   * Runge Kutte Fehlberg method
 */
const ODE_step_type *ODE_step_rkf45;


/* Constructor for stepper objects.
 */
ODE_stepper * ODE_stepper_alloc ( const ODE_step_type * T, size_t dim );
int ODE_stepper_apply ( ODE_stepper *, ODE_R t,
                        ODE_R h, ODE_R y[],
                        ODE_R yerr[],
                        const ODE_R dydt_in[],
                        ODE_R dydt_out[],
                        const ODE_system * dydt );
int ODE_stepper_reset ( ODE_stepper * s );
void ODE_stepper_free ( ODE_stepper * s );

const char * ODE_stepper_name ( const ODE_stepper * );
ODE_uint ODE_stepper_order ( const ODE_stepper * s );


#endif /* _ODE_STEPPER_H_ */

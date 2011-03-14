#ifndef _ODE_MARCHER_H_
#define _ODE_MARCHER_H_

#include "ODE_marcher_common.h"
#include "ODE_utils.h"

#include "ODE_stepper.h"
#include "ODE_control.h"

/* General marcher object.
 */
typedef struct {
  size_t dim;
  ODE_R * y0;
  ODE_R * yerr;
  ODE_R * dydt_in;
  ODE_R * dydt_out;
  ODE_R last_step;

  unsigned long int count;
  unsigned long int failed_steps;
}
ODE_marcher;


/* Marcher object methods.
 */
ODE_marcher * ODE_marcher_alloc ( ODE_uint dim );
int ODE_marcher_apply ( ODE_marcher *, ODE_stepper * step,
                        ODE_step_control * con, const ODE_system * dydt,
                        ODE_R * t, ODE_R t1, ODE_R * h, ODE_R y[]);
int ODE_marcher_reset ( ODE_marcher * );
void ODE_marcher_free ( ODE_marcher * );


#endif /* _ODE_MARCHER_H_ */

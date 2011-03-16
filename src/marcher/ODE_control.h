#ifndef _ODE_CONTROL_H_
#define _ODE_CONTROL_H_

#include "marcher/ODE_marcher_common.h"
#include "marcher/ODE_stepper.h"

/* General step size control object.
 *
 * The hadjust() method controls the adjustment of
 * step size given the result of a step and the error.
 * Valid hadjust() methods must return one of the codes below.
 *
 * The general data can be used by specializations
 * to store state and control their heuristics.
 */

typedef struct
{
  const char * name;
  void * (*alloc) ( void );
  int (*init) ( void * state, ODE_R eps_abs, ODE_R eps_rel,
                ODE_R a_y, ODE_R a_dydt );
  int (*hadjust) ( void * state, size_t dim, ODE_uint ord,
                   const ODE_R y[], const ODE_R yerr[],
                   const ODE_R yp[], ODE_R * h );
  void (*free) ( void * state );

}
ODE_step_control_type;

typedef struct
{
  const ODE_step_control_type * type;
  void * state;
}
ODE_step_control;

/* Possible return values for an hadjust() evolution method.
 */
#define ODE_STEP_HADJ_INC   1  /* step was increased */
#define ODE_STEP_HADJ_NIL   0  /* step unchanged     */
#define ODE_STEP_HADJ_DEC (-1) /* step decreased     */

ODE_step_control * ODE_step_control_alloc ( const ODE_step_control_type * T );
int ODE_step_control_init ( ODE_step_control * c, ODE_R eps_abs, ODE_R eps_rel, ODE_R a_y, ODE_R a_dydt );
int ODE_step_control_hadjust ( ODE_step_control * c, ODE_stepper * s, const ODE_R y[], const ODE_R yerr[], const ODE_R dydt[], ODE_R * h );
const char * ODE_step_control_name ( const ODE_step_control * c );
void ODE_step_control_free ( ODE_step_control * c );

/* Implemented step control types */
ODE_step_control * ODE_step_control_standard_new ( ODE_R eps_abs, ODE_R eps_rel, ODE_R a_y, ODE_R a_dydt );
ODE_step_control * ODE_step_control_y_new ( ODE_R eps_abs, ODE_R eps_rel );
ODE_step_control * ODE_step_control_yp_new( ODE_R eps_abs, ODE_R eps_rel );
/* ODE_step_control * ODE_step_control_scaled_new ( ODE_R eps_abs, ODE_R eps_rel, ODE_R a_y, ODE_R a_dydt, const ODE_R scale_abs[], size_t dim ); */



#endif /* _ODE_CONTROL_H_ */

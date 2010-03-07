#ifndef _ODE_MARCHER_COMMON_H_
#define _ODE_MARCHER_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../solver/ODE_common.h"
#include "../error/ODE_error.h"

/* TODO:
 * size_t to ODE_uint
 * [ OK ] S_DOUBLE to ODE_R
 * [ ] unsigned int
 * [ ] what headers to include
 */


#define _ODE_MAX(a,b) ((a) > (b) ? (a) : (b))
#define _ODE_MIN(a,b) ((a) < (b) ? (a) : (b))

#define ODE_TRUE 1;
#define ODE_FALSE 0;


#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

__BEGIN_DECLS


typedef struct
{
  int (* func) (ODE_R t, const ODE_R y[],
                ODE_R dydt[], void * params);
  
  int (* jac)  (ODE_R t, const ODE_R y[],
                ODE_R * dfdy, ODE_R dfdt[],
                void * params);

  size_t dimension; /* what size_t is ? */
  void * params; 
}
ODE_system;


#define _ODE_FUNC_EVAL(S,t,y,f)  (*((S)->func))(t,y,f,(S)->params) /* ODE_system function evaluate macro */
#define _ODE_JAC_EVAL(S,t,y,dfdy,dfdt)  (*((S)->jac))(t,y,dfdy,dfdt,(S)->params) /* ODE_system jacobian evaluate macro */

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
int  ODE_stepper_reset ( ODE_stepper * s );
void ODE_stepper_free ( ODE_stepper * s );

const char * ODE_stepper_name ( const ODE_stepper * );
ODE_uint ODE_stepper_order ( const ODE_stepper * s );



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
ODE_step_control * ODE_step_control_scaled_new ( ODE_R eps_abs, ODE_R eps_rel, ODE_R a_y, ODE_R a_dydt, const ODE_R scale_abs[], size_t dim );



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


__END_DECLS

#endif /* _ODE_MARCHER_COMMON_H_ */

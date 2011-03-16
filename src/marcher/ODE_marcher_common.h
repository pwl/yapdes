#ifndef _ODE_MARCHER_COMMON_H_
#define _ODE_MARCHER_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "error/ODE_error.h"

/** \todo
 * size_t to ODE_uint
 * [ OK ] S_DOUBLE to ODE_R
 * [ ] unsigned int
 * [ ] what headers to include
 */


#define _ODE_MAX(a,b) ((a) > (b) ? (a) : (b))
#define _ODE_MIN(a,b) ((a) < (b) ? (a) : (b))

#define ODE_TRUE 1
#define ODE_FALSE 0


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
  int (* func) ( ODE_R t, const ODE_R y[],
                 ODE_R dydt[], void * params );

  int (* jac)  ( ODE_R t, const ODE_R y[],
                 ODE_R * dfdy, ODE_R dfdt[],
                 void * params );

  size_t dimension; /* what size_t is ? */
  void * params;
}
ODE_system;


#define _ODE_FUNC_EVAL(S,t,y,f)  (*((S)->func))(t,y,f,(S)->params) /* ODE_system function evaluate macro */
#define _ODE_JAC_EVAL(S,t,y,dfdy,dfdt)  (*((S)->jac))(t,y,dfdy,dfdt,(S)->params) /* ODE_system jacobian evaluate macro */


/* Implemented step types:
 *   * Runge Kutte Fehlberg method
 */
/* const ODE_step_type *ODE_step_rkf45; */


__END_DECLS

#endif /* _ODE_MARCHER_COMMON_H_ */

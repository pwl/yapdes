#ifndef _ODE_STEPPER_H_
#define _ODE_STEPPER_H_

#include "ODE_common.h"

typedef struct _ODE_stepper ODE_stepper;

struct _ODE_stepper
{
  ODE_R t;
  ODE_R dt;
  ODE_R e_abs, e_rel;
  int (*rhs) ( void * params,
		ODE_R t,
		ODE_R f,
		ODE_R f_new );
  void * params;
};


ODE_stepper * ODE_stepper_init( void );

int ODE_stepper_step( ODE_stepper * );

int ODE_stepper_free( ODE_stepper * );


#endif /* _ODE_STEPPER_H_ */

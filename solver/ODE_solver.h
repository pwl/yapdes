#ifndef _ODE_SOLVER_H_
#define _ODE_SOLVER_H_

#include "ODE_state.h"

typedef struct _ODE_solver ODE_solver;

struct _ODE_solver
{
  ODE_state * state;
  ODE_modules * modules;
  ODE_uint status;
};

ODE_solver * ODE_solver_init( void );

void ODE_solver_free ( ODE_solver * );

ODE_solver_status ODE_solver_run (  );

#endif /* _ODE_SOLVER_H_ */

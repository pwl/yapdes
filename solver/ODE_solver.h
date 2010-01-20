#ifndef _ODE_SOLVER_H_
#define _ODE_SOLVER_H_

#include "ODE_common.h"
#include "modules/ODE_modules.h"
#include "ODE_state.h"

typedef struct _ODE_solver ODE_solver;

struct _ODE_solver
{
  ODE_state * state;
  ODE_module * modules;
  ODE_uint status;
  char * output_dir;
};

ODE_solver * ODE_solver_init( void );

void ODE_solver_free ( ODE_solver * );

int ODE_solver_run ( void );

#endif /* _ODE_SOLVER_H_ */

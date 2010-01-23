#ifndef _ODE_SOLVER_H_
#define _ODE_SOLVER_H_

#include "ODE_typedefs.h"
#include "modules/ODE_modules.h"
#include "ODE_state.h"

struct _ODE_solver
{
  ODE_state * state;
  ODE_module ** modules;
  int mod_num;

  ODE_uint status;
  ODE_uint run_time;
  char output_dir[100];
};

ODE_solver * ODE_solver_init( void );

void ODE_solver_free ( ODE_solver * );

int ODE_solver_run ( ODE_solver * );

int ODE_solver_module_add( ODE_solver * s, ODE_module * m );

int ODE_solver_modules_init( ODE_solver * );

int ODE_solver_modules_free( ODE_solver * s );

int ODE_module_add ( ODE_solver *, ODE_module * );

#endif /* _ODE_SOLVER_H_ */

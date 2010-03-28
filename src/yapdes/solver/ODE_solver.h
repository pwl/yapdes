#ifndef _ODE_SOLVER_H_
#define _ODE_SOLVER_H_

#include "solver/ODE_typedefs.h"
#include "solver/modules/ODE_modules.h"
#include "solver/ODE_state.h"
/* #include "ODE_stepper.h" */

struct _ODE_solver
{
  ODE_state * state;
  ODE_module ** modules;
  int mod_num;

  ODE_uint status;
  ODE_uint run_time;
/*   ODE_stepper ** stepper; */
  char output_dir[100];
};

ODE_solver * ODE_solver_init ( void );

void ODE_solver_free ( ODE_solver * );

int ODE_solver_run ( ODE_solver * );

int ODE_solver_add_module( ODE_solver * , ODE_module * );

int ODE_solver_modules_init( ODE_solver * );

int ODE_solver_modules_run( ODE_solver * );

int ODE_solver_modules_free( ODE_solver * );

int ODE_module_add ( ODE_solver *, ODE_module * );

/* int ODE_solver_add_stepper ( ODE_solver *, ODE_stepper * ); */

#endif /* _ODE_SOLVER_H_ */

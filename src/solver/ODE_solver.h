/**
 * @file   ODE_solver.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Tue Mar 15 19:42:50 2011
 *
 * The user interface and primary structure of the solver are defined
 * here. @sa ODE_state
 *
 * @addtogroup solver
 *
 */
#ifndef _ODE_SOLVER_H_
#define _ODE_SOLVER_H_

#include "common.h"
#include "solver/ODE_typedefs.h"
#include "solver/modules/ODE_modules.h"
#include "solver/ODE_state.h"
/* #include "ODE_stepper.h" */

/**
 * Ties state, modules and @a rhs of DE together.
 *
 * @todo include some structure to keep information on PDE
 * (i.e. method(s) of spatial differentiation used etc.)
 *
 */
struct ODE_solver
{
  ODE_state * state;
  ODE_module ** modules;	/**< table holding pointers to modules
				   @todo should point to a structure
				   holding modules and @c mod_num on
				   which accessors could be run */
  int mod_num;			/**< number of loaded modules */

  ODE_uint status;		/**< status of the solver */
  ODE_uint run_time;		/**< phase of DE solving
				   (init+ialization, marching,
				   etc.). Triggers access it to
				   determine the phase of evolution */
  /*   ODE_stepper ** stepper; */

  /** @todo change 100 to some predefined length e.g.
      @c MAX_FILE_NAME_LENGTH or something similar

      @todo more sophisticated data files management, probably
      including creation of automatically named directories or a
      database? This should probably hold a pointer to a structure
      responsible for data files management
  */
  char output_dir[100];		/**< directory name to output data
				   files */
};

/**
 * Allocates memory for the ODE_solver and initializes some of its
 * parts to their default values.
 *
 * For detailed information of what parts of ODE_solver are
 * initialized and what are the default values refer to the code.
 *
 * @return Pointer to allocated ODE_solver
 */

ODE_solver * ODE_solver_init ( void );

/**
 * Free ODE_solver and all its members
 * @attention Attention!
 * @pre aaa aaa
 * @post bbb bbb
 * @throw qqq
 *
 * @param s
 */
void ODE_solver_free ( ODE_solver * s );

/**
 * This function should run the solver until @f$t<T@f$. As a workhorse
 * of the whole solver part of yapdes it is responsible for calling
 * modules (by checking triggers) and marcher to push @ref ODE_state
 * in time.
 *
 * @param s
 *
 * @return ???
 */
int ODE_solver_run ( ODE_solver * s );

int ODE_solver_add_module( ODE_solver * , ODE_module * );

/**
 * Runs ODE_module->init() for every module added to s
 *
 * @todo send some information about which module failed to
 * initialize, e.g. module number, print module name etc, and return a
 * corresponding error code.
 *
 * @todo Implement transparent modules structure with accessors
 *
 * @param s Pointer to initialized solver
 *
 * @return ???
 */
int ODE_solver_modules_init( ODE_solver * );

int ODE_solver_modules_run( ODE_solver * );

int ODE_solver_modules_free( ODE_solver * );

int ODE_module_add ( ODE_solver *, ODE_module * );

/* int ODE_solver_add_stepper ( ODE_solver *, ODE_stepper * ); */

#endif /* _ODE_SOLVER_H_ */

/**
 * @file   ODE_solver.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Tue Mar 15 19:42:50 2011
 *
 * The user interface and primary structure of the solver are defined
 * here. @sa ODE_state
 *
 */
#ifndef _ODE_SOLVER_H_
#define _ODE_SOLVER_H_

#include "common.h"
#include "solver/ODE_typedefs.h"
#include "solver/ODE_module.h"
#include "solver/ODE_module_bundle.h"
#include "solver/ODE_state.h"
/* #include "ODE_stepper.h" */

__BEGIN_DECLS

/**
 * Ties state, modules and @a rhs of DE together.
 *
 * @todo include some structure to keep information on PDE
 * (i.e. method(s) of spatial differentiation used etc.)
 *
 * @todo develop a state machine for a solver
 *
 */
struct ODE_solver
{
  ODE_state * state;		/**< all parameters varying during a
				   solver run are stored here */
  /* ODE_module ** modules;	/\**< table holding pointers to modules */
  /* 				   @todo should point to a structure */
  /* 				   holding modules and @c mod_num on */
  /* 				   which accessors could be run *\/ */
  /* int mod_num;			/\**< number of loaded modules *\/ */
  ODE_module_bundle * module_bundle; /**< Bundle of modules assigned to
				      a solver */

  ODE_uint status;		/**< status of the solver */
  /*   ODE_stepper ** stepper; */

  /** @todo change 100 to some predefined length e.g.
      #MAX_FILE_NAME_LENGTH or something similar

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

/**
 * Add a module to a solver. Practically this is a wrapper to
 * ODE_module_bundle_add_module().
 *
 * @param s
 * @param m
 */
void ODE_solver_add_module ( ODE_solver * s, ODE_module * m );

__END_DECLS

#endif /* _ODE_SOLVER_H_ */

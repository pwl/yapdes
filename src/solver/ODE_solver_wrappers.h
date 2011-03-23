/**
 * @file   ODE_solver_wrappers.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Wed Mar 23 20:36:37 2011
 *
 * @brief  Collection of wrappers to a solver.
 *
 * Wrappers to a solver are functions which initialize a solver, add
 * some commonly used modules to it in a correct order, often along
 * with triggers, and return a pointer to an initialized ODE_solver.
 *
 *
 */
#ifndef _ODE_SOLVER_WRAPPERS_H_
#define _ODE_SOLVER_WRAPPERS_H_

#include "solver/ODE_solver.h"
#include "solver/modules/module_state_init.h"

/**
 * Initializes a solver with a state initialized to a size s.
 *
 * @param s number of dependent parameters stored in solver->state.
 *
 * @return solver with state initialized.
 */
ODE_solver * ODE_solver_wrapper_state( ODE_uint s );

/** @todo initialize grid */
/** @todo initialize initial conditions using given function */

#endif /* _ODE_SOLVER_WRAPPERS_H_ */

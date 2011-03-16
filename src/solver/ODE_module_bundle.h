/**
 * @file   ODE_module_bundle.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Wed Mar 16 09:41:48 2011
 *
 * @brief Module bundle is a structure used to manage modules loaded
 * to ODE_solver. This file contains barly a draft of whats yet to
 * come.
 *
 * @sa ODE_module
 *
 */
#ifndef _ODE_MODULE_BUNDLE_H_
#define _ODE_MODULE_BUNDLE_H_

#include "solver/modules/ODE_modules.h"
#include "solver/ODE_solver.h"

/**
 * A basic version of a module management structure consisting of a
 * list of modules and its length, to be expanded in future.
 *
 * @todo include new functios to access modules by name or by type
 *
 */

struct ODE_module_bundle
{
  /**@name temporary data format

     @todo to be replaced by some general structure (for example list)

     @{*/
  ODE_module ** modules;	/**< Table of pointers to
				   ODE_module */
  ODE_uint mod_num;		/**< number of loaded modules */

  ODE_uint max_mods;		/**< maximum number of modules to load
				   (corresponding to a memory size) */
  /**@}*/
  /* ODE_uint run_mode;		/\**< a switch to change global */
  /* 				   behaviour of modules *\/ */
  ODE_solver * solver;		/**< Pointer to a parent solver */
};


/**
 * Initialization function for ODE_module_bundle. Allocates memory and
 * defines a parent ODE_solver
 *
 * @param size Maximum number of modules to load
 *
 * @return A pointer to a ready to use ODE_module_bundle
 *
 */
ODE_module_bundle * ODE_module_bundle_init( ODE_solver * s, ODE_uint size );


/**
 * Adds an initialized module to a module bundle
 *
 * @param mb Bundle pointer to which ODE_module m will be added
 * @param m module to add
 *
 */
void ODE_module_bundle_add_module( ODE_module_bundle * mb, ODE_module * m );


/**
 * Tells a ODE_module_bundle mb to run all of its modules with respect
 * to a given flag. One of start(), step() or stop() is run for each
 * module in the bundle depending on a value of the flag provided a
 * trigger was set.
 *
 * @sa run_flags
 *
 * @param mb Bundle to run its module
 * @param flag
 */
void ODE_module_bundle_run( ODE_module_bundle * mb, ODE_uint flag );


/**
 * Runs ODE_module_free_common() for each module in a bundle and frees
 * the allocated memory of ODE_module_bundle.
 *
 * @attention This should always be run @b after
 * ODE_module_bundle_run( mb, MODULES_RUN_STOP ), which frees a
 * module-specific memory allocation, closes files etc.
 *
 * @sa ODE_module
 *
 */
void ODE_module_bundle_free( ODE_module_bundle * mb );

#endif /* _ODE_MODULE_BUNDLE_H_ */

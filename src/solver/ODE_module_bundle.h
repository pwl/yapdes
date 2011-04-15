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

#include "solver/ODE_module.h"
#include "solver/ODE_solver.h"

__BEGIN_DECLS

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

/** @name functions responsible for running modules from a bundle.
 *
 * @{*/
/**
 * Calls ODE_module_start() for each module in a bundle.
 *
 * @param mb
 */
void ODE_module_bundle_start( ODE_module_bundle * mb );

/**
 * Calls ODE_module_stop() for each module in a bundle.
 *
 * @param mb
 */
void ODE_module_bundle_stop( ODE_module_bundle * mb );

/**
 * Calls ODE_module_step() for each module in a bundle.
 *
 * @param mb
 */
void ODE_module_bundle_step( ODE_module_bundle * mb );
/**@}*/

/**
 * Runs ODE_module_free_common() for each module in a bundle and frees
 * the allocated memory of ODE_module_bundle. This function frees only
 * the memory common to all modules and memory allocated for
 * ODE_module_bundle. It does not stop modules.
 *
 * @attention This should always be run @b after
 * ODE_module_bundle_stop( mb ), which frees a module-specific memory
 * allocation, closes files etc.
 *
 * @sa ODE_module
 *
 */
void ODE_module_bundle_free( ODE_module_bundle * mb );

__END_DECLS

#endif /* _ODE_MODULE_BUNDLE_H_ */

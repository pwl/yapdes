/**
 * @file   ODE_trigger_bundle.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Wed Mar 16 17:04:32 2011
 *
 * @brief Trigger bundle to consistently manage triggers loaded to
 * ODE_module
 *
 *
 */
#ifndef _ODE_TRIGGER_BUNDLE_H_
#define _ODE_TRIGGER_BUNDLE_H_

#include "common.h"
#include "solver/modules/ODE_module.h"

struct ODE_trigger_bundle
{
  /**@name temporary data format

     @todo to be replaced by some general structure (for example list)

     @{*/
  ODE_trigger ** triggers;	/**< Table of pointers to
				   ODE_trigger */
  ODE_uint trig_num;		/**< number of loaded triggers */

  ODE_uint max_trigs;		/**< maximum number of triggers to load
				   (corresponding to a memory size) */
  /**@}*/
  /* ODE_uint run_mode;		/\**< a switch to change global */
  /* 				   behaviour of triggers *\/ */
  ODE_module * module;		/**< Pointer to a parent module */
};


/**
 * Function similar to ODE_module_bundle_init()
 *
 * @param m
 * @param size
 *
 * @return
 */
ODE_trigger_bundle * ODE_trigger_bundle_init( ODE_module * m, ODE_uint size);

/**
 * Function similar to ODE_module_bundle_add_module()
 *
 * @param mb
 * @param m
 */
void ODE_trigger_bundle_add_trigger( ODE_trigger_bundle * mb, ODE_trigger * m );

/**
 * Runs each of triggers and if ODE_trigger->run_flag and flag
 * coincide, return value is calculated. The logical conjugate of all
 * return values is then returned.
 *
 * @param mb
 * @param flag
 *
 * @return logical conjugate of return values of ODE_trigger's
 */
ODE_uint ODE_trigger_bundle_run( ODE_trigger_bundle * mb, ODE_uint flag );

/**
 * Function similar to ODE_module_bundle_free()
 *
 * @param mb
 */
void ODE_trigger_bundle_free( ODE_trigger_bundle * mb );


#endif /* _ODE_TRIGGER_BUNDLE_H_ */

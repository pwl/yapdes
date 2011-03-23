/**
 * @file   ODE_trigger.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Sun Mar 20 17:03:04 2011
 *
 * @brief Base structure for triggers is defined (ODE_trigger), along
 * with accessory functions. There is a lot of potential for
 * aggressive expansion here.
 *
 * Graph below represents the states (ODE_trigger_state) of an
 * ODE_trigger (states uninitialized and free are not states
 * formally). Each arrow represents a function which changes a state
 * of the trigger (prefixes "ODE_trigger_" and "TRIGGER_" were omitted
 * for clarity). After assigning an ERROR state to a trigger all the
 * functions consider it as broken @b beyond @b repair and as such the
 * state ERROR can be considered as an final-state for a trigger.
 *
 * @dot
 digraph "trigger states" {
 rankdir=LR
 node [shape=circle]
 uninitialized [shape=box]
 uninitialized -> STOPPED [label="init"]
 free [shape=box]
 STOPPED -> free [label="free"]
 STOPPED -> STARTED [label="start"]
 STOPPED -> ERROR [label="start"]

 STARTED -> STOPPED [label="stop"]
 STARTED -> STARTED [label="test"]
 STARTED -> ERROR [label="test"]
 STARTED -> ERROR [label="stop"]

 {rank=same; "free"; "uninitialized"}
 }
  @enddot
 *
 *
 */
#ifndef _ODE_MODULE_TRIGGER_H_
#define _ODE_MODULE_TRIGGER_H_

#include "common.h"
#include "solver/ODE_module.h"


/**
 * Triggers functionality is contained in ODE_trigger structure. Its
 * construction is similar to this of ODE_module.
 *
 */

struct ODE_trigger
{
  int (*start)( ODE_trigger *);	/**< Initializes the trigger,
				   allocating files and memory needed
				   for it to run */
  int (*stop)( ODE_trigger *);	/**< Contrary of ODE_trigger.start(),
				   frees memory and closes files if
				   necessary  */
  int (*test)( ODE_trigger *);	/**< The core function of the
				   ODE_trigger - returns 1 if test
				   succeeded and 0 otherwise  */

  ODE_module * module; /**< ODE_module to which this trigger is
		  assigned. */
  ODE_solver * solver;		/**< a ODE_solver to which a parent module
				   is assigned. */

  /** State of the trigger. In a normal run its value should proceed as follows

      NOT_STARTED -> STARTED -> STOPPED

      If there is an error somwhere ths state is changed to ERROR and
      a trigger is called no more.
  */
  ODE_trigger_state state;

  void * data;			/**< additional structures to be
				   defined for a particular trigger
				   should go here. */
};

/**
 * Analogous to ODE_module_init_common().
 *
 *
 * @return Partially initialized ODE_trigger.
 */
ODE_trigger * ODE_trigger_init ( void );

/**
 * Analogous to ODE_module_free_common().
 *
 * @param tr ODE_trigger to free.
 *
 */
void ODE_trigger_free( ODE_trigger * tr );

/**
 * Tests the trigger by running tr->test(), but only if its state is
 * TRIGGER_STARTED.
 *
 * @param tr Trigger to run.
 *
 * @retval TRUE trigger activated
 * @retval FALSE trigger not activated
 *
 */
int ODE_trigger_test( ODE_trigger * tr );

/**
 * Stops the trigger, but only if it is in a TRIGGER_STARTED state.
 *
 * @param tr
 */
void ODE_trigger_stop( ODE_trigger * tr );

/**
 * Starts the trigger, but only if it is in a TRIGGER_STOPPED state.
 *
 * @param tr
 */
void ODE_trigger_start( ODE_trigger * tr );

/**
 * Runs a sanity test for ODE_trigger. The vital pointers are checked
 * to be non NULL.
 *
 * @attention Vital pointers are start, stop, test, module and solver.
 *
 * @param tr
 *
 * @retval TRUE sanity test passed (all essential pointers are non NULL)
 * @retval FALSE sanity test failed
 */
int ODE_trigger_sanity_test( ODE_trigger * tr );

/**
 * Print some info on the trigger.
 *
 * @param t
 */
void ODE_trigger_print( ODE_trigger * t );


#endif /* _ODE_MODULE_TRIGGER_H_ */

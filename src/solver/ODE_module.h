/**
 * @file   ODE_module.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Tue Mar 15 21:00:42 2011
 *
 * Datatype and functions concerning a single module. The relation of
 * ODE_module to ODE_trigger is analoguos to the relation of
 * ODE_solver to ODE_module. Each ODE_module contains
 * ODE_trigger_bundle which is a structure containing all the
 * triggers. The ODE_trigger_bundle has a set of fucntions to access
 * triggers in a feasible manner. Each trigger added to a module can
 * see its ODE_trigger_bundle only by refering to an ODE_module first.
 *
 * Graph below represents the states (ODE_module_state) of ODE_module
 * (states uninitialized and free are not states formally). Each arrow
 * represents a function which changes a state of the module (the
 * prefixes @v "ODE_module_" and @v "MODULE_" were omitted for
 * clarity). After assigning an @v ERROR state to a module all the
 * functions consider it as broken @b beyond @b repair and as such the
 * state ERROR can be considered as an final-state for a trigger. At
 * this moment a broken modules are not completely ignored by all the
 * functions as they may contain working triggers, and singals such @v
 * stop, @v start and @v free can be send to them.
 *
 *
 * @todo Consider adding an additional state in which module is broken
 * but triggers are fine.
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
 ERROR -> free [label="free"]

 {rank=same; "free"; "uninitialized"}
 }
  @enddot
 *
 * @attention a trigger added to a started module will be started. A
 * trigger will not be added to a broken module.
 *
 * @attention if a module is stopped, so are all of its triggers. This
 * may cause problems if two modules share a trigger.
 *
 */
#ifndef _ODE_MODULES_H_
#define _ODE_MODULES_H_

#include "common.h"
#include "solver/ODE_solver.h"
#include "solver/ODE_trigger.h"
#include "solver/ODE_trigger_bundle.h"



/**
 * Structure of a module contains pointers to methods acting on it as
 * well as some basic parameters.
 *
 * @todo add a structure member to indicate status of a module
 *
 */

struct ODE_module
{
  /** start is called to initialize module specific stuff */
  int (*start)( ODE_module *);
  /** run is called every time a trigger is activated */
  int (*step)( ODE_module *);
  /** stop is called to close files, stop plotting etc. */
  int (*stop)( ODE_module *);
  /** free is called to free module specific stuff (stored in
      module->data), used only in ODE_module_free() and run only if
      module state is MODULE_STOPPED */
  int (*free)( ODE_module *);

  /** solver to which module is assigned */
  ODE_solver * solver;

  ODE_trigger_bundle * trigger_bundle; /**< triggers loaded into
					  ODE_module */

  char type[ODE_MAX_STRING_LENGTH];	/**< name of the module */
  void * data;	    /**< data specific to a particular module */
  int times_run;    /**< number of times a module has been called */

  /** state of the module */
  ODE_module_state state;
};

/**
 * Provides default values for members of ODE_module. Run by the
 * ODE_module_module_name_init().
 *
 *
 * @return partially initialized ODE_module.
 */
ODE_module * ODE_module_init ( void );


/**
 * Starts a module by running m->start(m) and sets an appropriate
 * m->state (STARTED or ERROR) depending on the value returned by
 * m->start(m).
 *
 * @param m
 */
void ODE_module_start ( ODE_module * m );

/** @todo conditional triggers? arbitrary logical functions of several
    triggers? probably too complicated for the user and to Implement. */
/**
 * If m->status is STARTED, it runs ODE_trigger_bundle_run() to check
 * if at least one of the triggers is activated. If yes, m->step(m) is
 * executed, and if its return value is < 0 m->state is set to ERROR.
 *
 * @param m
 */
void ODE_module_step ( ODE_module * m );

/**
 * If m->status is STARTED it stops a module by running m->stop(m) and
 * depending on the value it returns sets m->state to STOPPED or
 * ERROR.
 *
 * @attention if a module is stopped, so are all of its triggers. This
 * may cause problems if two modules share a trigger.
 *
 * @param m
 */
void ODE_module_stop ( ODE_module * m );

/**
 * Free memory assigned to a m and its members.
 *
 * @param m
 */
void ODE_module_free ( ODE_module * m );

/**
 * Add a trigger to a module. This is a wrapper to a
 * ODE_trigger_bundle_add_trigger() but its action depends on a state
 * of the module. E.g. for started modules, the trigger is set to
 * start as well, for broken modules, the trigger is not added etc.
 *
 * @param m
 * @param t
 */void ODE_module_add_trigger ( ODE_module * m, ODE_trigger * t );

/**
 * Prints some information on a module.
 *
 * @param m
 */
void ODE_module_print ( ODE_module * m );

/**
 * Checks if module has a vital pointers assigned.
 *
 * @attention vital pointers are trigger_bundle, solver, start, step
 * and stop
 *
 * @param m
 *
 * @retval TRUE if neither of the vital pointers NULL.
 * @retval FALSE otherwise.
 */
int ODE_module_sanity_check( ODE_module * m );

#endif /* _ODE_MODULES_H_ */

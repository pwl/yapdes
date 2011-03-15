/**
 * @file   ODE_modules.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Tue Mar 15 21:00:42 2011
 *
 * Datatype and functions concerning a single module. @todo The module
 * bundle datatype and functions should be included in another file
 * (ODE_module_bundle.[ch]?). There should also be an analoguos file
 * to maintain triggers, e.g. trigger_bundle
 *
 *
 *
 * @todo Documentation!
 * @addtogroup solver
 *
 */
#ifndef _ODE_MODULES_H_
#define _ODE_MODULES_H_

#include "solver/ODE_typedefs.h"
#include "solver/ODE_solver.h"
#include "solver/modules/module_triggers/ODE_module_trigger.h"

struct _ODE_module
{
  int (*init)( ODE_module *);
  int (*run)( ODE_module *);
  int (*free)( ODE_module *);
  int (*data_free)( ODE_module *);

  ODE_solver * solver;	/**< solver to which module is
				   assigned */

  ODE_module_trigger ** triggers; /**< triggers assigned to this
					   module */
  int trig_num;			/**< number of triggers added, TODO:
				   to be changed */

  char * type;	    /**< name of the module TODO: decrease table size */
  void * data;	    /**< data specific to a particular module */
  int times_run;
  int times_run_failed;
};

ODE_module * ODE_module_init_common ( void );

int ODE_module_run_common( ODE_module * m );

int ODE_module_free_common ( ODE_module * m );

int ODE_module_add_trigger ( ODE_module *, ODE_module_trigger * );

int ODE_module_run_triggers ( ODE_module * );

int ODE_module_triggers_free ( ODE_module * m );

int ODE_module_print ( ODE_module * m );


#endif /* _ODE_MODULES_H_ */

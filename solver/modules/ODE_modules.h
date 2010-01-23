#ifndef _ODE_MODULES_H_
#define _ODE_MODULES_H_

#include "ODE_typedefs.h"
#include "ODE_solver.h"
#include "modules/module_triggers/ODE_module_trigger.h"

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

  char * name;	    /* name of the module TODO: decrease table size */
  void * data;	    /* data specific to a particular module */
  int times_run;
};

ODE_module * ODE_module_init_common ( void );

int ODE_module_free_common ( ODE_module * m );

int ODE_module_add_trigger ( ODE_module *, ODE_module_trigger * );

int ODE_module_run_triggers ( ODE_module * );

int ODE_module_triggers_free ( ODE_module * m );


#endif /* _ODE_MODULES_H_ */

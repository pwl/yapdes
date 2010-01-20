#ifndef _ODE_MODULES_H_
#define _ODE_MODULES_H_

#include "module_triggers/ODE_module_trigger.h"

typedef struct _ODE_module ODE_module;

struct _ODE_module
{
  void (*init)( ODE_module *);
  void (*run)( ODE_module *);
  void (*free)( ODE_module *);
  void (*data_free)( ODE_module *);

  struct _ODE_solver * solver;		/**< solver to which module is
				   assigned */

  ODE_module_trigger ** triggers;	/**< triggers assigned to this
					   module */
  int trig_num;			/**< number of triggers added, TODO:
				   to be changed */

  char * name;  /* name of the module TODO: decrease table size */
  void * data;	   /* data specific to a particular module */
};

void ODE_module_add_trigger ( ODE_module *, ODE_module_trigger * );

#endif /* _ODE_MODULES_H_ */

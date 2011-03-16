#ifndef _ODE_MODULE_TRIGGER_H_
#define _ODE_MODULE_TRIGGER_H_

#include "solver/ODE_typedefs.h"
#include "common.h"
#include "solver/modules/ODE_modules.h"


struct ODE_module_trigger
{
  int (*init)( ODE_module_trigger *);
  int (*free)( ODE_module_trigger *);
  int (*test)( ODE_module_trigger *);

  ODE_module * module;	/**< module to which this trigger is
				  assigned to */

  ODE_uint run_time;
  void * data;
};


ODE_module_trigger * ODE_module_trigger_init_common ( void );

int ODE_module_trigger_free_common( ODE_module_trigger * tr );

#endif /* _ODE_MODULE_TRIGGER_H_ */

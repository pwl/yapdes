#ifndef _ODE_MODULE_TRIGGER_H_
#define _ODE_MODULE_TRIGGER_H_

#include "ODE_typedefs.h"
#include "ODE_common.h"
#include "modules/ODE_modules.h"


struct _ODE_module_trigger
{
  int (*start)( ODE_module_trigger *);
  int (*stop)( ODE_module_trigger *);
  int (*test)( ODE_module_trigger *);

  struct _ODE_module * module;	/**< module to which this trigger is
				  assigned to */

  ODE_uint run_time;
  void * data;
};


ODE_module_trigger * ODE_module_trigger_init_common ();



#endif /* _ODE_MODULE_TRIGGER_H_ */

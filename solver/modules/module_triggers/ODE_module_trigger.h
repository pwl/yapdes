#ifndef _ODE_MODULE_TRIGGER_H_
#define _ODE_MODULE_TRIGGER_H_

#include "ODE_common.h"

typedef struct _ODE_module_trigger ODE_module_trigger;

struct _ODE_module_trigger
{
  void (*start)( ODE_module_trigger *);
  void (*stop)( ODE_module_trigger *);
  int (*test)( ODE_module_trigger *);

  struct _ODE_module * module;	/**< module to which this trigger is
				  assigned to */

  void * data;
};

#endif /* _ODE_MODULE_TRIGGER_H_ */

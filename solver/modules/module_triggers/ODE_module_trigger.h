#ifndef _ODE_MODULE_TRIGGER_H_
#define _ODE_MODULE_TRIGGER_H_

typedef struct _ODE_module_trigger ODE_module_trigger;

struct ODE_module_trigger
{
  void (*init)( ODE_module_trigger *);
  void (*stop)( ODE_module_trigger *);
  void (*test)( ODE_module_trigger *);
  void (*action)( ODE_module_trigger *);

  ODE_module * module;		/**< module to which this trigger is
				   assigned to */

  void * data;
};

#endif /* _ODE_MODULE_TRIGGER_H_ */

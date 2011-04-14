#ifndef _MODULE_TEST_H_
#define _MODULE_TEST_H_

#include "solver/ODE_module.h"

__BEGIN_DECLS

/* standard module functions */
int module_test_start ( ODE_module * );

int module_test_step ( ODE_module * );

int module_test_stop ( ODE_module * );

/* module init function, can be programmed to take any arguments,
   and is called by the user */

ODE_module * ODE_module_test_init ( void );

__END_DECLS

#endif /* _MODULE_TEST_H_ */

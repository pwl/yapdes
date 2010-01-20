#ifndef _MODULE_TEST_H_
#define _MODULE_TEST_H_

#include "ODE_modules.h"

/* standard module functions */
void module_test_start ( ODE_module * );

void module_test_run ( ODE_module * );

void module_test_stop ( ODE_module * );

/* module init function, can be programmed to take any arguments,
   and is called by the user */

ODE_module * ODE_module_module_test_init ( );


#endif /* _MODULE_TEST_H_ */

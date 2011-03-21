#ifndef _MODULE_TEST_H_
#define _MODULE_TEST_H_

#include "solver/ODE_module.h"

/* standard module functions */
int module_test_init ( ODE_module * );

int module_test_run ( ODE_module * );

int module_test_free ( ODE_module * );

/* module init function, can be programmed to take any arguments,
   and is called by the user */

ODE_module * ODE_module_test_init ( void );


#endif /* _MODULE_TEST_H_ */

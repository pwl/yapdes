#ifndef _TRIGGER_TEST_H_
#define _TRIGGER_TEST_H_

#include "ODE_module_trigger.h"

#include "stdio.h"
#include "stdlib.h"

int trigger_test_start ( ODE_module_trigger * );

int trigger_test_stop( ODE_module_trigger * );

int trigger_test_test ( ODE_module_trigger * );

ODE_module_trigger * ODE_module_trigger_test_init ( void );

#endif /* _TRIGGER_TEST_H_ */

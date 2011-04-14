#ifndef _TRIGGER_TEST_H_
#define _TRIGGER_TEST_H_

#include "solver/ODE_trigger.h"

#include "stdio.h"
#include "stdlib.h"

__BEGIN_DECLS

int trigger_test_start ( ODE_trigger * );

int trigger_test_stop( ODE_trigger * );

int trigger_test_test ( ODE_trigger * );

ODE_trigger * ODE_trigger_test_init ( void );

__END_DECLS

#endif /* _TRIGGER_TEST_H_ */

#ifndef _ODE_COMMON_H_
#define _ODE_COMMON_H_

#include "stdio.h"
#include "stdlib.h"

#define ODE_R long double
#define ODE_uint unsigned int


#define MAX_TRIG_NUMB 10
#define MAX_MOD_NUMB 30

#define SOLVER_INITIALIZED 0x01
#define SOLVER_STATE_READY 0x02
#define SOLVER_MODULES_READY 0x04
#define SOLVER_READY 0x08

#endif /* _ODE_COMMON_H_ */

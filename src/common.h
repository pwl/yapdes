/**
 * @file   ODE_common.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Thu Jan 21 17:58:06 2010
 *
 * @brief This file contains the defines and includes used throughout
 * whole library
 *
 *
 */

#ifndef _ODE_COMMON_H_
#define _ODE_COMMON_H_

#include "stdio.h"
#include "stdlib.h"

#include "solver/ODE_typedefs.h"


/** @name default maximum size of trigger and module bundles */
/**@{*/
#define MAX_TRIG_NUMB 10
#define MAX_MOD_NUMB 30
/**@}*/

/** String length to contain module type

    @todo should be increased to avoid errors and consistent with
    other string lengths */
#define MODULE_TYPE_SIZE 100

/** @name solver states
    @{ */
#define SOLVER_ST_INITIALIZED 0x01
#define SOLVER_ST_STATE_READY 0x02
#define SOLVER_ST_MODULES_READY 0x04
#define SOLVER_ST_READY 0x08
/**@}*/

/** @name trigger run times
    @{*/
#define TRIG_RUN_NEVER   0x00
#define TRIG_RUN_START   0x01
#define TRIG_RUN_STEP    0x02
#define TRIG_RUN_STOP    0x04
/** used for triggers to be run at a mixture of stages */
#define TRIG_RUN_ALWAYS  (TRIG_RUN_START | TRIG_RUN_STEP | TRIG_RUN_STOP)
/**@}*/

/** @name solver run times */
/**@{*/
#define SOLVER_RUN_NOT_RUNNING 0x00
#define SOLVER_RUN_START   0x01
#define SOLVER_RUN_STEP    0x02
#define SOLVER_RUN_STOP    0x04
/**@}*/

/** default run_time for trigger */
#define TRIG_RUN_DEFAULT TRIG_RUN_NEVER

#endif /* _ODE_COMMON_H_ */

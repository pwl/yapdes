/**
 * @file   common.h
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

#include "helper/macro.h"
#include "error/ODE_error.h"
/** @todo split typedefs and move them to their respective folders */
#include "solver/ODE_typedefs.h"

/** @name boolean data types */
/**@{*/
#define FALSE				0
#define TRUE				!(FALSE)
/**@}*/

/** @name default maximum size of trigger and module bundles */
/**@{*/
#define MAX_TRIG_NUMB			10
#define MAX_MOD_NUMB			30
/**@}*/

/** String length to contain module type

    @todo should be increased to avoid errors and consistent with
    other string lengths */
#define MODULE_TYPE_SIZE		100

/** @name solver states
    @{ */
#define SOLVER_ST_INITIALIZED		0x01
#define SOLVER_ST_STATE_READY		0x02
#define SOLVER_ST_MODULES_READY		0x04
#define SOLVER_ST_READY			0x08
/**@}*/

/** maximal numbers of modules to load into a ODE_module_bundle */
#define MODULE_BUNDLE_MAX_MODULES	100

/** maximum length of strings used in yapdes. global variable */
#define ODE_MAX_STRING_LENGTH		100

/** This are the possible states of a module, @sa ODE_module.h */
typedef enum
  {
    MODULE_STARTED = 'S',
    MODULE_STOPPED = '-',
    MODULE_ERROR = 'E'
  } ODE_module_state;

/** This are the possible states of a trigger, @sa ODE_trigger.h */
typedef enum
  {
    TRIGGER_STARTED = 'S',
    TRIGGER_STOPPED = '-',
    TRIGGER_ERROR = 'E'
  } ODE_trigger_state;

#define ODE_FMT "%i"

#endif				/* _ODE_COMMON_H_ */

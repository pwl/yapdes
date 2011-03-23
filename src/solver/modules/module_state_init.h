/**
 * @file   module_state_init.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Wed Mar 23 20:24:59 2011
 *
 * @brief Module used to initialize state of the solver given number
 * of equations.
 *
 * This is an example of a module responsible for initialization of a
 * solver. At initialization user enters a number of equations as an
 * argument, which is then stored in a data part of this
 * module. During a start of the solver it will allocate memory for a
 * solver state. It might seem to be an awkward way to initialize a
 * part of a solver but a motivation here is simple -- it strips one
 * parameter from a solver initialization. It is also a typical
 * example of an initialization module, which is responsible for
 * allocating and freeing some parts of a solver but stays inactive
 * during the step phase.
 *
 *
 */
#ifndef _MODULE_STATE_INIT_H_
#define _MODULE_STATE_INIT_H_

#include "solver/ODE_module.h"


/** @name standard module interface
    @{*/
int module_state_init_start ( ODE_module * m );

int module_state_init_step ( ODE_module * m );

int module_state_init_stop ( ODE_module * m );

/**
 * Here a module is initialized with a given equation number.
 *
 * @param size Number of ODE equations to solve
 *
 * @return Initialized module with size saved in its void * data.
 */
ODE_module * ODE_module_state_init_init ( ODE_uint size );

/**
 * data is freed.
 *
 * @param m
 *
 * @return
 */
int module_state_init_free( ODE_module * m );
/**@}*/

#endif /* _MODULE_STATE_INIT_H_ */

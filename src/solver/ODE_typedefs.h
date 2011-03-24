/**
 * @file   ODE_typedefs.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Wed Mar 16 12:09:32 2011
 *
 * @brief Contains typedefs of data types used in whole yapdes as well
 * as typedefs used to forward declare structs.
 *
 *
 */
#ifndef _ODE_TYPEDEFS_H_
#define _ODE_TYPEDEFS_H_


/** @name Default data types for solver */
/**@{*/
typedef long double ODE_R;     /**< type for continuous variables */
typedef unsigned int ODE_uint; /**< type for unsigned in, (mainly flags) */
/**@}*/

/** @name Forward declaration of structs for solver
   @{*/
typedef struct ODE_module ODE_module;
typedef struct ODE_solver ODE_solver;
typedef struct ODE_state ODE_state;
typedef struct ODE_trigger ODE_trigger;
typedef struct ODE_module_bundle ODE_module_bundle;
typedef struct ODE_trigger_bundle ODE_trigger_bundle;
typedef struct ODE_table ODE_table;
typedef struct ODE_stepper ODE_stepper;
/**@}*/

/** @name Forward declaration of structs for mesh
   @{*/
typedef struct ODE_mesh ODE_mesh;
/**@}*/



#endif /* _ODE_TYPEDEFS_H_ */

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


/** @todo split typedefs and move them to their respective folders */

/** @name Forward declaration of structs for solver
   @{*/
typedef struct ODE_module		ODE_module;
typedef struct ODE_solver		ODE_solver;
typedef struct ODE_state		ODE_state;
typedef struct ODE_trigger		ODE_trigger;
typedef struct ODE_module_bundle	ODE_module_bundle;
typedef struct ODE_trigger_bundle	ODE_trigger_bundle;
typedef struct ODE_table		ODE_table;
typedef struct ODE_stepper		ODE_stepper;
typedef struct ODE_pde			ODE_pde;
/**@}*/

/** @name Forward declaration of structs for mesh
   @{*/
typedef struct ODE_mesh ODE_mesh;
/**@}*/

/** @name Forward declaration of structs for helpers
   @{*/
typedef struct ODE_dictionary	ODE_dictionary;
typedef struct ODE_storage      ODE_storage;
/** @}*/

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

#endif /* _ODE_TYPEDEFS_H_ */

/**
 * @file   ODE_state.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Tue Mar 15 18:28:58 2011
 *
 * Definitions and functions concerning ODE_state struct.
 *
 * @todo replace all free and mallocs with appropriate macros.
 *
 *
 */
#ifndef _ODE_STATE_H_
#define _ODE_STATE_H_

#include "solver/ODE_table.h"
#include "common.h"

/** Structure designed to hold a time-dependent information on the
    function being evolved. This is a core data structure of a solver
    and is evolved by marcher using some rhs formula (@todo provide
    rhs formula).
    @todo a state machine for #ODE_state
*/
struct ODE_state
{
  /** @name Vector values
   *
   *  #f and #df contain current function values and rhs
   *  respectively
   *  @{*/
  ODE_table * f;		/**< Function value */
  ODE_table * df;		/**< rhs */
  /** @} */
  /** @name Scalar values
   * @{ */
  ODE_R t;			/**< Calculational time */
  ODE_R dt;			/**< Current stepsize */
  ODE_uint i;			/**< Step number @bug possible overflow*/
  /** @} */
};


/**
 * Function
 *
 * @param[in] length
 *
 * @return Pointer to ODE_state
 */

ODE_state * ODE_state_init(int length );

/**
 * Free allocated memory
 *
 * @param[in,out] ODE_state to be freed
 */

void ODE_state_free( ODE_state * state );


#endif /* _ODE_STATE_H_ */

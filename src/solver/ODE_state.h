/**
 * @file   ODE_state.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Tue Mar 15 18:28:58 2011
 *
 * Definitions and functions concerning @ref ODE_state struct.
 *
 *
 */
#ifndef _ODE_STATE_H_
#define _ODE_STATE_H_

#include "ODE_typedefs.h"
#include "ODE_splitted_table.h"

/** Structure designed to hold a time-dependent information on the
    function being evolved. This is a core data structure of a solver
    and is evolved by marcher. */
struct _ODE_state
{
  /** @name Vector values
   *
   *  @c f and @c df contain current function values and rhs
   *  respectively
   *  @{*/
  ODE_table * f;		/**< Function value */
  ODE_table * df;		/**< @a rhs value */
  /** @} */
  /** @name Scalar values
   * @{ */
  ODE_R t;			/**< Calculational time */
  ODE_R dt;			/**< Current stepsize */
  long int i;			/**< Step number */
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

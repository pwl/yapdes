#ifndef _ODE_STATE_H_
#define _ODE_STATE_H_

#include "ODE_splitted_table.h"

typedef struct _ODE_state ODE_state; /**< This structure keeps the
				   current state of the equation, this
				   is the core data structure of the
				   solver */


struct _ODE_state
{
  ODE_splitted_table * f;	/**< structure to hold the state of
				   the eqn variables */
  ODE_splitted_table * df;	/**< Evolutional increment of f
				   calculated from f */
  ODE_R t;			/**< Calculational time */
  ODE_R dt;			/**< Current stepsize */
  long int i;			/**< Step number */
};

ODE_state * ODE_state_init( int N, int * length );

void ODE_state_free( ODE_state * );

#endif /* _ODE_STATE_H_ */

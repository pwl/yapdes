#ifndef _ODE_TABLE_H_
#define _ODE_TABLE_H_

#include "common.h"

struct ODE_table
{
  ODE_R * table;
  int length;
};


/**
 * Allocate memory for @p ODE_table of length @p length
 *
 * @param[in] length Length of the table to initialize
 *
 * @return Pointer to allocated @c ODE_table
 */
ODE_table * ODE_table_init( int length );

/**
 * Free memory taken by @c ODE_table @c t
 *
 * @param[in,out] t Pointer to a @c ODE_table
 */
void ODE_table_free( ODE_table * t );

/**
 * ODE_table accessor
 *
 * @param[in] t
 * @param[in] n
 *
 * @return @a n-th element of @c t
 */
ODE_R ODE_table_get( ODE_table * t, int n );

#endif /* _ODE_TABLE_H_ */

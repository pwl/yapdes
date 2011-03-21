/**
 * @file   ODE_table.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Sun Mar 20 17:00:41 2011
 *
 * @brief Helper file defining ODE_table and accessory functions.
 *
 *
 */
#ifndef _ODE_TABLE_H_
#define _ODE_TABLE_H_

#include "common.h"

/**
 * ODE_table is a simply a table with its maximum length stored in a
 * single structure
 *
 */

struct ODE_table
{
  ODE_R * table;		/**< table */
  int length;			/**< maximum length of ODE_table.table */
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

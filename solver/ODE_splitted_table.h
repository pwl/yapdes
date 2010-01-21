#ifndef _ODE_SPLITTED_TABLE_H_
#define _ODE_SPLITTED_TABLE_H_

#include "ODE_table.h"
#include "ODE_common.h"


typedef struct _ODE_splitted_table ODE_splitted_table;

struct _ODE_splitted_table
{
  int N;			/* number of tables */
  int * length;			/* length of the particular table */
  ODE_R * table;		/* table to by sliced */
};

/**
 *
 *
 * @param N number of elements in length
 * @param length length of slices
 *
 * @return
 */

ODE_splitted_table * ODE_splitted_table_init (int N, int * length);

/**
 *
 *
 * @param st
 */

void ODE_splitted_table_free( ODE_splitted_table * st );

/**
 * This function fills t with n-th data set from st
 *
 * @param st
 * @param n
 *
 * @return
 */

int ODE_splitted_table_get( ODE_splitted_table * st, int n, ODE_table * t );

/**
 * This function returns the pointer to the n-th array from
 * ODE_splitted_table
 *
 * @param st
 * @param n
 *
 * @return
 */

ODE_R * ODE_splitted_table_to_ptr( ODE_splitted_table * st, int n );

#endif /* _ODE_SPLITTED_TABLE_H_ */

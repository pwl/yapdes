#ifndef _ODE_SPLITTED_TABLE_H_
#define _ODE_SPLITTED_TABLE_H_

typedef _ODE_splitted_table ODE_splitted_table;

struct _ODE_splitted_table
{
  int N;			/* number of tables */
  int * length;			/* length of the particular table */
  ODE_R ** table;		/* tables */
};

/**
 * @file   ODE_splitted_table.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Wed Jan 20 13:10:20 2010
 *
 * @brief The function below initializes the basic data structure for
 * the ODE_solver
 */

ODE_splitted_table * ODE_splitted_table_init (int N, int * length);

/**
 * @file   ODE_splitted_table.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Wed Jan 20 13:20:06 2010
 *
 * @brief The functio below frees the memory used by type
 * ODE_splitted_table
 */

void ODE_splitted_table_free( ODE_splitted_table * st );


#endif /* _ODE_SPLITTED_TABLE_H_ */

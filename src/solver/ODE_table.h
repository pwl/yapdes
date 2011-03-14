#ifndef _ODE_TABLE_H_
#define _ODE_TABLE_H_

#include "ODE_common.h"

typedef struct _ODE_table ODE_table;

struct _ODE_table
{
  ODE_R * table;
  int length;
};


ODE_table * ODE_table_init( int length );

void ODE_table_free( ODE_table * t );


#endif /* _ODE_TABLE_H_ */

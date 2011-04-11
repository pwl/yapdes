#include "solver/pde.h"

ODE_pde * ODE_pde_init( void )
{
  ODE_pde * pde = ODE_MALLOC( 1, ODE_pde );
  
  pde->mesh_n	 = 0;
  pde->mesh	 = NULL;
  pde->f	 = NULL;
  pde->rhs	 = NULL;
  
  return pde;
}


void ODE_pde_free( ODE_pde * pde )
{
  ODE_FREE( pde );
}

int ODE_pde_size( ODE_pde * pde )
{
  int i, size=0;

  for( i = 0; i < pde->mesh_n; i++ )
    size += (pde->mesh[i]->n) * (pde->mesh[i]->ind);

  return size;
}

void ODE_pde_add_mesh( ODE_pde * pde, ODE_mesh * m)
{
  /* int	mn  = pde->mesh_n; */
  /* int size1; */
  /* int size2; */
  /* int size3; */

  /* calculate new sizes */
  /* for(  */
  
  /* /\* set the indices of the last mesh*\/ */
  /* if( mn > 0 ) */
  /*   { */
  /*     n1 = pde->mesh[mn-1]->n; */
  /*     ind1 = pde->mesh[mn-1]->ind; */
  /*   } */
  

  /* /\* 1. prepare memory *\/ */
  /* pde->mesh = */
  /*   ODE_REALLOC( pde->mesh, mn + 1, ODE_mesh * ); */

  /* /\** @todo how to apply DRY here? *\/ */
  /* pde->f = ODE_REALLOC( pde->f, mn + 1, ODE_R ** ); */
  /* pde->f[0] = ODE_REALLOC( pde->f[0], n, ODE_R * ); */
  /* pde->f[0][0] = ODE_REALLOC( pde->f[0][0], n * ind, ODE_R ); */

  /* pde->rhs = ODE_REALLOC( pde->rhs, mn + 1, ODE_R ** ); */
  /* pde->rhs[0] = ODE_REALLOC( pde->rhs[0], n, ODE_R * ); */
  /* pde->rhs[0][0] = ODE_REALLOC( pde->rhs[0][0], n * ind, ODE_R ); */

  /* /\* 2. set the pointers *\/ */
  /* { */
  /*   int i; */
  /*   pde->f[mn]=pde->f[mn-1]+n1; */
  /*   pde->rhs[mn]=pde->rhs[mn-1]+n1; */
  /*   for( i = 0; i <  */
  /*     pde->f[0][] = pde->f[0] */
  /* 	   pde->f[mn] = pde->f[mn-1]+pde->mesh[mn-1]->; */
  /* 	 } */
    
}

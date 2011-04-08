#include "mesh.h"

ODE_mesh * ODE_mesh_init( int n, int ind, int maxrk )
{
  ODE_mesh * m = ODE_MALLOC( 1, ODE_mesh );

  m->mesh  = ODE_MALLOC( n, ODE_R );
  m->f	   = (ODE_R **) ODE_MALLOC( ind * n, ODE_R );
  m->cache = (ODE_R ***) ODE_MALLOC( ind * n * maxrk, ODE_R );
  m->dict  = ODE_dictionary_init( );

  m->dim   = 1;
  m->n	   = n;
  m->ind   = ind;
  m->maxrk = maxrk;

  printf("%f\n", m->cache[0][0][0]);

  return m;
}


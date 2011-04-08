#include "mesh.h"

ODE_mesh * ODE_mesh_init( int n, int ind, int maxrk )
{
  ODE_mesh * m = ODE_MALLOC( 1, ODE_mesh );

  /** @todo assuming all the memory is will be allocated is pretty
      dangerous here */
  /* This is an initialization of the 2,3-dimensional tables as a
     continuous block. Such approach drastically reduces the calls to
     mallocs */


  /* @todo a horror! */
  m->mesh = ODE_MALLOC( n, ODE_R );
  m->f	  = (ODE_R**)malloc( n * sizeof(ODE_R*));
  m->f[0] = (ODE_R*)malloc( ind * n * sizeof(ODE_R) );
  {
    int i;
    for( i = 1; i < n; i++ )
      m->f[i] = m->f[0] + i*n;
  }
    
  m->cache	 = (ODE_R ***) malloc( n * sizeof(ODE_R**) );
  m->cache[0]	 = (ODE_R **) malloc( n * ind * sizeof(ODE_R*) );
  m->cache[0][0] = (ODE_R *) malloc( n * ind  * maxrk * sizeof(ODE_R));
  {
    int i,j;
    for( i = 1; i < n; i++ )
      {
	m->cache[i]=m->cache[0]+i*n;
	for( j = 1; j < ind; j++ )
	  m->cache[i][j]=m->cache[0][0]+i*n+j*n*ind;
      }
  }
  
  /* dictionary is empty on initialization */
  m->dict  = ODE_dictionary_init( );

  m->dim   = 1;
  m->n	   = n;
  m->ind   = ind;
  m->maxrk = maxrk;

  return m;
}

void ODE_mesh_free( ODE_mesh * m )
{
  ODE_FREE( m->mesh );

  ODE_FREE( m->f[0] );
  ODE_FREE( m->f );

  ODE_FREE( m->cache[0][0] );
  ODE_FREE( m->cache[0] );
  ODE_FREE( m->cache );

  ODE_dictionary_free( m->dict );
  
  free(m);
}

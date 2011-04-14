#include "mesh.h"

ODE_mesh * ODE_mesh_init( int n, int ind, int maxrk , int * names)
{
  ODE_mesh * m = ODE_MALLOC( 1, ODE_mesh );

  /** @todo assuming all the memory is will be allocated is pretty
      dangerous here */
  
  m->mesh = ODE_MALLOC( n, ODE_R );
  
  /* This is an initialization of the 2,3-dimensional tables as a
     continuous block. Such approach drastically reduces the calls to
     mallocs */
  
  /* @todo a horror! */
  /* @todo use ODE_storage_init_array() to allocate this memory? */
  m->f	  = ODE_MALLOC( ind, ODE_R* );
  m->f[0] = ODE_MALLOC( ind * n, ODE_R );
  {
    int i;
    for( i = 0; i < ind; i++ )
      m->f[i] = m->f[0] + i*n;
  }
    
  m->cache	 = ODE_MALLOC( ind, ODE_R** );
  m->cache[0]	 = ODE_MALLOC( ind * maxrk, ODE_R* );
  m->cache[0][0] = ODE_MALLOC( ind * maxrk * n, ODE_R );
  {
    int i,j;
    for( i = 0; i < ind; i++ )
      {
	m->cache[i]=m->cache[0]+i*maxrk;
	for( j = 0; j < maxrk; j++ )
	  m->cache[i][j]=m->cache[0][0]+(i*maxrk+j)*n;
      }
  }
  
  /* dictionary is empty on initialization */
  m->dict  = ODE_dictionary_init( );

  /* if *names is given we assume it contains _all_ the names */
  if( names )
  {
    int i;
    for( i = 0; i < n; i++ )
      ODE_dictionary_set_index(m->dict, i, names[i]);
  }
  

  m->dim   = 1;
  m->n	   = n;
  m->ind   = ind;
  m->maxrk = maxrk;

  return m;
}

void ODE_mesh_free( ODE_mesh * m )
{
  ODE_FREE( m->mesh );

  /*ODE_FREE the continuous blocks */

  /* the if here is to help ODE_pde to manage memory */
  if( m->f )
    {
      ODE_FREE( m->f[0] );
      ODE_FREE( m->f );
    }
  
  ODE_FREE( m->cache[0][0] );
  ODE_FREE( m->cache[0] );
  ODE_FREE( m->cache );

  ODE_dictionary_free( m->dict );
  
  ODE_FREE(m);
}

/* void ODE_mesh_give_names( ODE_mesh * m, const int * names ) */
/* { */
/*   int i; */
/*   for( i = 0; i < m->ind; i++ ) */
/*     ODE_dictionary_set_index(m->dict, i, names[i] ); */
/* } */


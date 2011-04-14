#include "solver/pde.h"

ODE_pde * ODE_pde_init( void )
{
  ODE_pde * pde = ODE_MALLOC( 1, ODE_pde );
  
  pde->mesh_n = 0;
  pde->mesh   = NULL;
  pde->dict   = ODE_dictionary_init();
  pde->s_f    = NULL;
  pde->s_rhs    = NULL;
  
  return pde;
}


void ODE_pde_free( ODE_pde * pde )
{
  int i;
  
  if( pde->s_f )
    ODE_storage_free( pde->s_f );

  if( pde->s_rhs )
    ODE_storage_free( pde->s_rhs );

  for( i = 0; i < pde->mesh_n; i++ )
    {
      /* before freeing a mesh we have to set mesh->f to NULL to
	 prevent ODE_mesh_free from freeing a part of a memory block
	 allocated by ODE_storage */
      pde->mesh[i]->f = NULL;
      ODE_mesh_free( pde->mesh[i] );
    }

  ODE_FREE( pde->mesh );
  
  ODE_dictionary_free( pde->dict );
  
  ODE_FREE( pde );
}

int ODE_pde_size( ODE_pde * pde )
{
  /* int i, size=0; */
  return
    pde->s_f->size[ pde->s_f->depth - 1 ];
  /* for( i = 0; i < pde->mesh_n; i++ ) */
  /*   size += (pde->mesh[i]->n) * (pde->mesh[i]->ind); */

  /* return size; */
}

void ODE_pde_add_mesh( ODE_pde * pde, ODE_mesh * m , int name)
{
  int depth = 3;
  int n = pde->mesh_n;
  int * dim = ODE_MALLOC( depth, int );
  ODE_storage * s;

  /* add a mesh to a mesh table */
  pde->mesh = ODE_REALLOC( pde->mesh, n + 1, ODE_mesh * );
  pde->mesh[n] = m;
  pde->mesh_n++;

  /* initialize a storage */
  dim[0]=1;
  dim[1]=m->n;
  dim[2]=m->ind;

  s = ODE_storage_init_array( 3, dim );
  /* ODE_storage_print( s ); */
  
  if( ! pde->s_f )
    pde->s_f = ODE_storage_copy( s );
  else
    ODE_storage_add( pde->s_f, s );

  /* here comes a tricky part, we need to move a pointer m->f to point
     to an appropriate part of a storage, but we have to free a memory
     which ODE_mesh has already allocated */
  ODE_FREE(m->f[0]);
  ODE_FREE(m->f);
  /* after this operation mesh will address a memory allocated by
     pde */
  m->f = (ODE_R**) pde->s_f->ptrs[0][n];

  /* index of a newly added mesh is pde->s_f->size[0] - 1 */
  ODE_dictionary_set_index( pde->dict, pde->s_f->size[0] - 1, name );

  /* free temporary storage */
  ODE_storage_free( s );
  ODE_FREE( dim );
}

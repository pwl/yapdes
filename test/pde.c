#include "pde.h"

int main(int argc, char *argv[])
{
  ODE_pde * pde = ODE_pde_init();
  ODE_mesh * m1 = ODE_mesh_init( 3, 2, 2 );
  ODE_mesh * m2 = ODE_mesh_init( 5, 3, 1 );
  
  ODE_pde_add_mesh( pde, m1 , 'm1');
  ODE_pde_add_mesh( pde, m2 , 'm2');

  ODE_storage_print(pde->s_f);

  printf("meshes are the same: %i %i %i\n",
	 m1 == ODE_pde_get_mesh( pde, 'm1' ),
	 m2 == ODE_pde_get_mesh( pde, 'm2' ),
	 NULL == ODE_pde_get_mesh( pde, 'm999' ));
      
  ODE_pde_free( pde );
  
  return 0;
}

#include "pde.h"

int main(int argc, char *argv[])
{
  ODE_pde * pde = ODE_pde_init();
  ODE_mesh * m1 = ODE_mesh_init( 3, 2, 2 );
  ODE_mesh * m2 = ODE_mesh_init( 5, 3, 1 );
  
  ODE_pde_add_mesh( pde, m1 , 'name');
  ODE_pde_add_mesh( pde, m2 , 'abc');

  ODE_storage_print(pde->s_f);
  
  ODE_pde_free( pde );
  
  return 0;
}

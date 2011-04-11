#include "pde.h"

int main(int argc, char *argv[])
{
  ODE_pde * pde = ODE_pde_init();

  ODE_pde_free( pde );
  
  return 0;
}

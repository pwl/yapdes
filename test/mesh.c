#include "mesh.h"

int main(int argc, char *argv[])
{
  int x = 1, y=2, z=1;
  ODE_mesh * m = ODE_mesh_init(x,y,z);

  /* Check if one can write to appropriate variables */
  m->mesh[0]=1.;
  m->f[0][0]=1.;
  m->cache[0][0][0]=1.;

  /* Last position in the tables */
  m->mesh[x-1]=1.;
  m->f[x-1][y-1]=1.;
  m->cache[x-1][y-1][z-1]=1.;

  printf("%d\n", m->cache[0]);
  
  
  ODE_mesh_free( m );
  
  return 0;
}

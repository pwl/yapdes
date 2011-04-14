#include "mesh.h"

int main(int argc, char *argv[])
{
  int x = 3, y=2, z=1;
  int names[] = {'a','b','c'};
  ODE_mesh * m = ODE_mesh_init(x,y,z,names);

  /* Check if one can write to appropriate variables */
  m->mesh[0]=1.;
  m->f[0][0]=1.;
  m->cache[0][0][0]=1.;

  /* Last position in the tables */
  m->mesh[x-1]=1;
  m->f[y-1][x-1]=1;
  m->cache[y-1][z-1][x-1]=1;

  ODE_mesh_free( m );
  
  return 0;
}

#include "mesh.h"

int main(int argc, char *argv[])
{
  ODE_mesh * m = ODE_mesh_init(10,10,10);

  m->mesh[0]=1.;
  m->f[0][0]=1.;
  m->cache[0][0][0]=1.;
  
  
  /* printf("%d\n",m->cache[0][0][0]); */
  
  ODE_mesh_free( m );
  
  return 0;
}

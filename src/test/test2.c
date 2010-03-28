#include "test2.h"

int func ( ODE_R t, const ODE_R y[], ODE_R f[], void *params );
int jac ( ODE_R t, const ODE_R y[], ODE_R *dfdy, 
          ODE_R dfdt[], void *params );


int func ( ODE_R t, const ODE_R y[], ODE_R f[], void *params )
{
  ODE_R mu = *(ODE_R *)params;
  f[0] = y[1];
  f[1] = -y[0] - mu*y[1]*(y[0]*y[0] - 1);
  return ODE_TRUE;
}

int jac ( ODE_R t, const ODE_R y[], ODE_R *dfdy, 
          ODE_R dfdt[], void *params )
{
  return ODE_TRUE;
}

int main ( int argc, char *argv[] )
{
  FILE *file = fopen("file", "w");

  const ODE_step_type * T = ODE_step_rkf45;
  
  ODE_stepper * s = ODE_stepper_alloc( T, 2 );

  ODE_step_control * c = ODE_step_control_standard_new( 1e-16L, 0.0L , 0.5L, 0.5L );

  ODE_marcher * m = ODE_marcher_alloc( 2 );
  
  ODE_R mu = 0.L;

  ODE_system sys = {func, jac, 2, &mu};
     
  ODE_R t = 0.0L, t1 = 50.0L;

  ODE_R h = 1e-18L;

  ODE_R y[] = { 1.L, 0.L };

  clock_t hStart, hStop; /* Host timer variable */

  hStart = clock();
  
  while( t < t1 ) {
      int status = ODE_marcher_apply( m, s, c, &sys, &t, t1,&h, y );
      
      if( status!=ODE_TRUE ) break;
      
      fprintf (file, "%.16Le %.16Le %.16Le\n", t, y[0]-cos(t), y[1]+sin(t) );
  }

  hStop = clock();

  printf(" Time elapsed host (host timer): %f (s)\n",  ( ((double) hStop - (double) hStart)/CLOCKS_PER_SEC ) );

  
  ODE_marcher_free( m );
  
  ODE_step_control_free( c );

  ODE_stepper_free( s );

  fclose( file );
  
  return 0;
}

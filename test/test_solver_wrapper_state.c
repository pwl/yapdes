#include "test_solver_wrapper_state.h"

int main(int argc, char *argv[])
{
  ODE_uint size = 10;
  ODE_solver * s = ODE_solver_wrapper_state( size );

  ODE_solver_free( s );

  return 0;
}

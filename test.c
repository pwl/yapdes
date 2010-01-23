#include "test.h"

int main(int argc, char *argv[])
{
  ODE_solver * s;
  ODE_module * m;
  ODE_module_trigger * t;

  m = ODE_module_module_test_init();
  t = ODE_module_trigger_test_init();
  t->run_time = TRIG_RUN_ALWAYS;
  s = ODE_solver_init();

  ODE_module_print( m );

  ODE_module_add_trigger( m, t );

  ODE_solver_add_module( s, m );

  ODE_solver_run(s);

  ODE_module_print( m );

  ODE_solver_free(s);

  return 0;
}

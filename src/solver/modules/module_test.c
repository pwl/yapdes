#include "module_test.h"

int module_test_init ( ODE_module * m )
{
  return printf("module_test start\n");
}

int module_test_run ( ODE_module * m )
{
  return printf("module_test run\n");
}

int module_test_free ( ODE_module * m )
{
  return printf("module_test stop\n");
}


ODE_module * ODE_module_module_test_init ( void )
{
  ODE_module * m = ODE_module_init_common ();

  sprintf( m->type, "Test module" );

  m->start =
    module_test_init;
  m->run =
    module_test_run;
  m->stop =
    module_test_free;

  return m;
}

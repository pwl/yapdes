#include "module_test.h"

int module_test_start ( ODE_module * m )
{
  printf("module_test start\n");
  return 0;
}

int module_test_step ( ODE_module * m )
{
  ODE_module_print( m );
  printf("module_test run\n");
  return 0;
}

int module_test_stop ( ODE_module * m )
{
  printf("module_test stop\n");
  return 0;
}

ODE_module * ODE_module_test_init ( void )
{
  ODE_module * m = ODE_module_init ();

  sprintf( m->type, "Test module" );

  m->start =
    module_test_start;
  m->step =
    module_test_step;
  m->stop =
    module_test_stop;

  return m;
}

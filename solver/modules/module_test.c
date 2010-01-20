#include "module_test.h"

void module_test_start ( ODE_module * m )
{
  printf("module_test start\n");
}

void module_test_run ( ODE_module * m )
{
  printf("module_test run\n");
}

void module_test_stop ( ODE_module * m )
{
  printf("module_test stop\n");
}


ODE_module * ODE_module_module_test_init ( )
{
  ODE_module * m = module_init_common ();

  m->start =
    module_test_start;
  m->run =
    module_test_run;
  m->stop =
    module_test_stop;
  m->data_free =
    NULL;

  return m;
}

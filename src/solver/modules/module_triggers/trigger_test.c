#include "trigger_test.h"

int trigger_test_start ( ODE_trigger * t)
{
  printf("trigger_test_starting\n");
  return 1;
}


int  trigger_test_stop ( ODE_trigger * t)
{
  printf("trigger_test stopping\n");
  return 1;
}


int trigger_test_test ( ODE_trigger * t)
{
  ODE_trigger_print( t );
  printf("trigger_test returning TRUE\n");
  return TRUE;
}

ODE_trigger * ODE_trigger_test_init ( )
{
  ODE_trigger * t = ODE_trigger_init();

  t->start = trigger_test_start;
  t->stop = trigger_test_stop;
  t->test = trigger_test_test;

  return t;
}

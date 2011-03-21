#include "trigger_test.h"

int trigger_test_start ( ODE_trigger * t)
{
  return printf("trigger_test_starting\n");
}


int  trigger_test_stop ( ODE_trigger * t)
{
  return printf("trigger_test stopping\n");
}


int trigger_test_test ( ODE_trigger * t)
{
  printf("trigger_test returning 1\n");

  return 1;
}

ODE_trigger * ODE_trigger_test_init ( )
{
  ODE_trigger * t = malloc( sizeof( ODE_trigger ) );

  t->data = NULL;
  t->module = NULL;

  t->start = trigger_test_start;
  t->stop = trigger_test_stop;
  t->test = trigger_test_test;

  return t;
}

#include "ODE_modules.h"

ODE_module * ODE_module_init_common ( void )
{
  ODE_module * m = malloc( sizeof( ODE_module ) );
  m->trig_num = 0;
  m->triggers = malloc( MAX_TRIG_NUMB * sizeof( ODE_module_trigger ) );
  return m;
}

void ODE_module_add_trigger (ODE_module * m, ODE_module_trigger * t)
{
  m->triggers[m->trig_num]=t;
  t->module=m;
  m->trig_num++;
}

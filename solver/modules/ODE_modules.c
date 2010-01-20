#include "ODE_modules.h"

void ODE_module_add_trigger (ODE_module * m, ODE_module_trigger * t)
{
  m.triggers[m.trig_num]=t;
  t.module=m;
  m.trig_num++;
}

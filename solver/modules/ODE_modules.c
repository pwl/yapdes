#include "ODE_modules.h"

ODE_module * ODE_module_init_common ( void )
{
  ODE_module * m = malloc( sizeof( ODE_module ) );

  m->trig_num = 0;
  m->triggers = malloc( MAX_TRIG_NUMB * sizeof( ODE_module_trigger ) );

  return m;
}

int ODE_module_add_trigger (ODE_module * m, ODE_module_trigger * t)
{
  if( m->trig_num >= MAX_TRIG_NUMB )
    return -1;

  m->triggers[m->trig_num]=t;
  t->module=m;
  m->trig_num++;

  return 0;
}

int ODE_module_run_triggers ( ODE_module * m )
{
  int i;
  int ret_val = 0;		/* boole value, defaults to true */
  ODE_module_trigger * tr;

  for (i = 0; i < m->trig_num; ++i)
    {
      tr = m->triggers[i];
      ret_val =
	ret_val			/* ret_val is positive */
	|| (tr->test( tr )	/* test is positive */
	    && (tr->run_time
	    	& m->solver->run_time)); /* run_times match */
    }

  return ret_val;
}

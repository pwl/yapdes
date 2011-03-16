#include "ODE_modules.h"

ODE_module * ODE_module_init_common ( void )
{
  ODE_module * m = malloc( sizeof( ODE_module ) );

  m->times_run = 0;
  m->times_run_failed = 0;
  m->trig_num = 0;
  m->triggers = malloc( MAX_TRIG_NUMB * sizeof( ODE_module_trigger ) );

  m->data = NULL;
  m->solver = NULL;
  m->type = malloc( MODULE_TYPE_SIZE * sizeof( char ) );

  m->start = NULL;
  m->run = NULL;
  m->stop = NULL;
  m->data_free = NULL;

  return m;
}

int ODE_module_run_common( ODE_module * m , ODE_uint flag)
{
  int ret_val;

  if( ! ODE_module_run_triggers( m ) )
    return -1; /** \todo return value may overlap the return code of
		   m->run */

  if( (ret_val = m->run( m ) ) < 0 )
    {
      m->times_run_failed++;
      return ret_val;
    }

  m->times_run++;

  return 0;
}

int ODE_module_free_common ( ODE_module * m )
{
  ODE_module_triggers_free( m );
  free( m->triggers );
  free( m );
  return 0;
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
	|| ((tr->run_flag
	     & m->solver->run_time) /* run_times match */
	    && (tr->test( tr ))	   /* test is positive */
	    );
    }

  return ret_val;
}

int ODE_module_triggers_free ( ODE_module * m )
{
  int i;
  int ret_val;
  ODE_module_trigger * tr;

  for (i = 0; i < m->trig_num; ++i)
    {
      tr = m->triggers[i];
      if( (ret_val = tr->stop( tr )) < 0 ||
	  (ret_val = ODE_module_trigger_free_common( tr )) < 0 )
	return ret_val;
    }

  return 0;
}

int ODE_module_print ( ODE_module * m )
{

  printf("M: Type: %s\n", m->type);
  printf("M: Number of triggers assigned: %i\n",m->trig_num);
  printf("M: Times run: %i\n",m->times_run);
  printf("M: Times failed to run: %i\n",m->times_run_failed);
  printf("M: Data structure assigned: %s\n",m->data?"Yes":"No");
  printf("M: Solver assigned: %s\n", m->solver?"Yes":"No");

  return 0;
}

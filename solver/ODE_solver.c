#include "ODE_solver.h"


ODE_solver * ODE_solver_init ( void )
{
  ODE_solver * s = malloc( sizeof( ODE_solver ) );
  s->modules = ODE_modules_init( );
  s->mod_num=0;
  s->status = SOLVER_INITIALIZED;
  return s;
}

ODE_module ** ODE_modules_init( void )
{
  return malloc( MAX_MOD_NUMB * sizeof( ODE_module * ) );
}

int ODE_modules_add( ODE_solver * s, ODE_module * m )
{
  if ( s->mod_num >= MAX_MOD_NUMB )
    return -1;
  else
    {
      s->modules[s->mod_num] = m;
      s->mod_num++;
      m->solver = s;
    }
  return 0;
}


int ODE_solver_run ()
{

  return 0;
}

void ODE_solver_free (ODE_solver * s)
{

}

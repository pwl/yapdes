#include "solver/ODE_trigger_bundle.h"


ODE_trigger_bundle * ODE_trigger_bundle_init( ODE_module * m, ODE_uint size)
{
  ODE_trigger_bundle * tb = ODE_MALLOC( 1, ODE_trigger_bundle );

  tb->triggers	= ODE_MALLOC( size,  ODE_trigger *  );
  tb->trig_num	= 0;
  tb->max_trigs	= size;
  tb->module	= m;

  return tb;
}

void ODE_trigger_bundle_add_trigger( ODE_trigger_bundle * tb, ODE_trigger * t )
{
  if( tb->trig_num < tb->max_trigs )
    {
      t->module = tb->module;
      t->solver = tb->module->solver;
      tb->triggers[tb->trig_num] = t;
      tb->trig_num++;
    }
  else
    /** @todo report! */
    return;

}


void ODE_trigger_bundle_free( ODE_trigger_bundle * tb )
{
  ODE_uint i;
  for( i=0; i < tb->trig_num; i++ )
    ODE_trigger_free( tb->triggers[i] );

  free( tb->triggers );
  free( tb );
}

void ODE_trigger_bundle_start( ODE_trigger_bundle * tb )
{
  ODE_uint i;
  for( i=0; i < tb->trig_num; i++ )
    ODE_trigger_start( tb->triggers[i] );
}

void ODE_trigger_bundle_stop( ODE_trigger_bundle * tb )
{
  ODE_uint i;
  for( i=0; i < tb->trig_num; i++ )
    ODE_trigger_stop( tb->triggers[i] );
}

ODE_uint ODE_trigger_bundle_test( ODE_trigger_bundle * tb )
{
  ODE_uint i;

  for( i=0; i < tb->trig_num; i++ )
    /* stop at the first test thet passes and return TRUE. This is a
       short circuit mechanism which stops evaluating tests after
       evaluating the first one which returns TRUE. */
    if( ODE_trigger_test( tb->triggers[i] ) )
      return TRUE;

  /* all tests failed or there were no triggers assigned (for
     tb->trig_num == 0 for loop quits before evaluating its
     body) */
  return FALSE;
}


ODE_uint ODE_trigger_bundle_count( ODE_trigger_bundle * tb )
{
  return tb->trig_num;
}

void ODE_trigger_bundle_update( ODE_trigger_bundle * tb )
{
  ODE_uint i;
  for( i = 0; i < tb->trig_num; i++ )
    tb->triggers[i]->solver = tb->module->solver;
}

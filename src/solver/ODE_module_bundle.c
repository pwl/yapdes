#include "ODE_module_bundle.h"

ODE_module_bundle * ODE_module_bundle_init( ODE_solver * s, ODE_uint size )
{
  ODE_module_bundle * mb = malloc( sizeof( ODE_module_bundle ) );

  mb->modules	= malloc( size * sizeof( ODE_module * ) );
  mb->mod_num	= 0;
  mb->max_mods	= size;
  mb->solver	= s;

  return mb;
}

void ODE_module_bundle_add_module( ODE_module_bundle * mb, ODE_module * m )
{
  if( mb->mod_num < mb->max_mods )
    {
      /* Add a new module */
      m->solver = mb->solver;
      /* Update solver information for triggers */
      ODE_trigger_bundle_update( m->trigger_bundle );

      mb->modules[mb->mod_num] = m; /**< @todo log success */
      /* increase number of assigned modules */
      mb->mod_num++;
    }
  else
    /** @todo report */
    return;
}

void ODE_module_bundle_start( ODE_module_bundle * mb )
{
  ODE_uint i;
  for( i = 0; i < mb->mod_num; i++ )
    ODE_module_start( mb->modules[i] );
}

void ODE_module_bundle_stop( ODE_module_bundle * mb )
{
  ODE_uint i;
  for( i = 0; i < mb->mod_num; i++ )
    ODE_module_stop( mb->modules[i] );
}

void ODE_module_bundle_step( ODE_module_bundle * mb )
{
  ODE_uint i;
  for( i = 0; i < mb->mod_num; i++ )
    ODE_module_step( mb->modules[i] );
}


void ODE_module_bundle_free( ODE_module_bundle * mb )
{
  ODE_uint i;
  for ( i = 0; i < mb->mod_num; i++ )
    ODE_module_free(  mb->modules[i] );

  free( mb->modules );

  free( mb );
}


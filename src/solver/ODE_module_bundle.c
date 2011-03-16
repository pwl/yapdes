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
  if( mb->mod_num >= mb->max_mods )
    /* do nothing */
    return;			/**< @todo log error */
  else
    {
      /* Add a new module */
      mb->modules[mb->mod_num] = m; /**< @todo log success */
      /* increase number of modules held */
      mb->mod_num++;
    }
}

void ODE_module_bundle_run( ODE_module_bundle * mb, ODE_uint flag )
{
  ODE_uint i;

  for ( i = 0; i <= mb->mod_num; i++ )
    ODE_module_run_common( mb->modules[i], flag );
}

void ODE_module_bundle_free( ODE_module_bundle * mb )
{
  ODE_uint i;
  for ( i = 0; i <= mb->mod_num; i++ )
    ODE_module_free_common(  mb->modules[i] );

  free( mb->modules );

  free( mb );
}


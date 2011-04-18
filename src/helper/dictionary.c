#include "helper/dictionary.h"

ODE_dictionary * ODE_dictionary_init( void )
{
  ODE_dictionary * d = ODE_MALLOC( 1, ODE_dictionary );
  d->n = 0;
  /* d->mc=ODE_MALLOC(0,int); */
  d->mc=(int*)NULL;
  return d;
}


int ODE_dictionary_get_index( ODE_dictionary * d, int mc )
{
  int i;
  for( i = 0; i < d->n; i++ )
    if( d->mc[i] == mc )
      return i;

  /* could not find a corresponding index, @todo report */
  return -1;
}

/* this is a very bad implementation! */
int ODE_dictionary_set_index( ODE_dictionary * d, int index, int mc)
{
  int * newmc;
  
  /* increase the size of d->mc */
  if( index >= d->n )
    {
      /** @bug, d->mc[i] for a span of i upto index is not
	  initialized (see valgrind test/dictionary) */
  
      /** @todo enclose the following with a macro */

      /** @bug new memory should be initialized to 0 */
      newmc = ODE_REALLOC( d->mc, index + 1, int, d->n );
      {
	int i;
	for( i = d->n; i < index; i++)
	  newmc[i] = 0;
      }
            
      if( ! newmc )
	/* error to be handled by a programmer */
	/** @todo report! */
	return 1;
      else
	{
	  d->mc = newmc;	/* new chunk of memory */
	  d->n = index + 1;	/* new size of the dictionary */
	}
    }
  
  d->mc[index] = mc;

  /* everything went fine */
  return 0;
}

void ODE_dictionary_free( ODE_dictionary * d )
{
  /* if there are some entries present */
  if( d->n > 0 )
    ODE_FREE( d->mc );
  ODE_FREE( d );
}

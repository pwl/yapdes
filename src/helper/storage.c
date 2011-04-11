#include "helper/storage.h"

void ODE_storage_add( ODE_storage * s1, ODE_storage * s2 )
{
  int d = s1->depth;
  
  /* 1. check if both storages are of the same depth */
  if( d != s2->depth )
    return;
  
  /* 2. reallocate the memory */
  /* after memory is reallocated all the pointers have to be recalculated */
  {
    int i,j;
    void * old;
    
    for( i = 0; i < d - 1; i++ )
      {
	/* save old pointers */
	old = s1->ptrs[i];
	s1->ptrs[i] =
	  ODE_REALLOC( s1->ptrs[i], s1->size[i] + s2->size[i], void * );
	
	/* do we need to recalculate pointers? */
    	if( s1->ptrs[i] != old && i > 0)
	  /* alter every pointer in an upper layer */
	  for( j = 0; j < s1->size[i-1]; j++ )
	    s1->ptrs[i-1][j] = s1->ptrs[i-1][j] - old + s1->ptrs[i];
      }

    old = s1->data;
    s1->data =
      ODE_REALLOC( s1->data, s1->size[d-1] + s1->size[d-1], ODE_R );

    if( s1->data != old )
      for( j = 0; j < s1->size[d-2]; j++ )
	s1->ptrs[d-2][j] = s1->ptrs[d-2][j] - old + s1->data;
            
  }
  
  /* 3. copy the s2->data to s1->data */
  memcpy( s1->data + s1->size[d-1], s2->data, s2->size[d-1] * sizeof(ODE_R) );

  /* 4. assign pointers to data copied to s1 */
  {
    int i,j,S1,S2,start;
    for ( i = 0; i < d - 1; i++ )
      for( j = 0; j < s2->size[i]; j++ )
      {
	S1 = s1->size[i];
	S2 = s1->size[i+1];
	
	if( i+1 < d-1 )
	  start = s1->ptrs[i+1];
	else
	  start = s1->data;
	
	printf("--------%i %i %i %i %i\n",
	       i, S1, S2,
	       s2->ptrs[i][j] - s2->ptrs[i][0],
	       s1->ptrs[i][0] - start );
	
	s1->ptrs[i][S1+j] =
	  s2->ptrs[i][j] - s2->ptrs[i][0] /* this is the address shift */
	  + start + S2;	/* new addresses in s1 start here */
      }
  }

  /* 5. alter s1->size */
  {
    int i;
    for ( i = 0; i < d; i++)
      s1->size[i]+=s2->size[i];
  }
}

void ODE_storage_print( ODE_storage * s, int offset )
{
  char fmt[] = " %6i |";
  
  printf("Storage dump:\n");
  printf("Size: {");
	
  {
    int i,j;

    for( i = 0; i < s->depth; i++ )
      printf(" %i", s->size[i]);
    printf(" }\n");
    
    for( i = 0; i < s->depth - 1; i++ )
      {
	/* print pointer offset */
	printf("lvl %3i (%i el.):  |", i, s->size[i] );
	
	if( s->size[i] <= 10 )
	  for( j = 0; j < s->size[i]; j++ )
	    printf(fmt, s->ptrs[i][j] - s->ptrs[i][0]);
	else
	  {
	    for( j = 0; j < offset; j++ )
	      printf(fmt, s->ptrs[i][j] - s->ptrs[i][0]);
	    
	    printf(" (...) |");

	    for( j = s->size[i]; j > s->size[i] - offset; j-- )
	      printf(fmt, s->ptrs[i][j] - s->ptrs[i][0]);
	  }
	printf("\n");
	
      }
    
    printf("lvl %3i (%i el.):  |", i, s->size[s->depth - 1] );

    if( s->size[s->depth-1] <= 6 )
      for( j = 0; j < s->size[s->depth-1]; j++ )
	printf(" " ODE_FMT " |", s->data[j]);
    else
      {
	
	for( j = 0; j < offset; j++ )
	  printf(" " ODE_FMT " |", s->data[j]);
    
	printf(" (...) |");
    
	for( j = s->size[s->depth-1]; j > s->size[s->depth-1] - offset; j-- )
	  printf(" " ODE_FMT " |", s->data[j]);
      }
    printf("\n");
  }
}

ODE_storage * ODE_storage_init( int depth, int * size )
{
  ODE_storage * s = ODE_MALLOC( 1, ODE_storage );

  s->size = ODE_MALLOC( depth, int );
  s->ptrs = ODE_MALLOC( depth - 1, void **);
  s->data = ODE_MALLOC( size[depth-1], ODE_R );

  memcpy( s->size, size, depth * sizeof(int) );
  
  {
    int i,j;
    for( i = 0; i < depth - 1; i++ )
      s->ptrs[i] = ODE_MALLOC( size[i], void * );
    
    for( i = 0; i < depth - 2; i++ )
      s->ptrs[i][0] = s->ptrs[i+1];
    
    s->ptrs[depth-2][0] = (void * ) s->data;

    for( i = 0; i < depth - 1; i++ )
      for (j = 0; j < size[i]; j++)
	s->ptrs[i][j] = s->ptrs[i][0];
    
    for( i = 0; i < size[depth-1]; i++ )
      s->data[i] = i;
  }

  
  s->depth = depth;
  
  return s;
}

void ODE_storage_free( ODE_storage * s )
{
  int i;
  
  for ( i = 0; i < s->depth - 1; i++)
    ODE_FREE(s->ptrs[i]);
  
  ODE_FREE(s->ptrs);
  ODE_FREE(s->data);
  ODE_FREE(s->size);
  ODE_FREE(s);
}

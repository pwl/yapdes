#include "helper/storage.h"

void ODE_storage_realloc(ODE_storage *s1, ODE_storage *s2)
{
  int d = s1->depth;
  int i,j,shift;
    
  {
    void *** old;
    
    for( i = 0; i < d - 1; i++ )
      {
	/* save old pointer */
	old = s1->ptrs[i];
	/* reallocate memory and rewrite s1->ptrs[i] */
	s1->ptrs[i] =
	  ODE_REALLOC( s1->ptrs[i], s1->size[i] + s2->size[i], void ** );

	/* calculate new relative poistion */
	shift = (void**)s1->ptrs[i] - (void**)old;
	      
	/* did a realloc moved a block of memory? if yes we need to
	   recalculate pointers. */
	
	if( shift != 0 && i > 0 )
	  for( j = 0; j < s1->size[i-1]; j++ )
	    {
	      printf("-----------%i %i %i %i\n",
	      	     i, j, (void**)s1->ptrs[i-1][j]-(void**)old, shift);
	      /* translate the pointers to a new memory block
		 position */
	      s1->ptrs[i-1][j] = (void*)((void **)s1->ptrs[i-1][j] + shift);
	    }
      }
  }

  /* analogous to the above 'for' loop but used to reallocate
     s1->data */
  {
    ODE_R * old = s1->data;
    s1->data =
      ODE_REALLOC( s1->data, s1->size[d-1] + s1->size[d-1], ODE_R );

    /* calculate new relative poistion */
    shift = s1->data - old;

    /* if a memory block has moved */
    if( shift != 0 )
      for( j = 0; j < s1->size[d-2]; j++ )
	{
	  printf("-----------%i %i %i %i\n",
	  	 i, j, (ODE_R*)s1->ptrs[d-2][j] - old, shift);
	  s1->ptrs[d-2][j] = (void*)((ODE_R*)s1->ptrs[d-2][j] + shift);
	}
  }
}

void ODE_storage_recalculate_pointers(ODE_storage *s1, ODE_storage *s2)
{
  int d = s1->depth;
  int i,j,S1,S2;
  for ( i = 0; i < d - 1; i++ )
    for( j = 0; j < s2->size[i]; j++ )
      {
	S1 = s1->size[i];
	S2 = s1->size[i+1];
	
	if( i < d-2 )
	  {
	    void *** start;
  	    start = s1->ptrs[i+1];
	    s1->ptrs[i][S1+j] = (void*)
	      ((void**)s2->ptrs[i][j] - (void**)s2->ptrs[i][0] /* this is the address shift */
	       + start + S2);	/* new addresses in s1 start here */    
	  }
	
	else
	  {
	    ODE_R * start;
	    start = s1->data;
	    s1->ptrs[i][S1+j] = (void*)
	      ((ODE_R*)s2->ptrs[i][j] - (ODE_R*)s2->ptrs[i][0] /* this is the address shift */
	       + start + S2);	/* new addresses in s1 start here */    
	  }
      }
}

void ODE_storage_add( ODE_storage * s1, ODE_storage * s2 )
{
  int d = s1->depth;
  
  /* 1. check if both storages are of the same depth */
  /** @todo this is not required since we can add two storages so that
      the last level (data) corresponds, still to be implemented */
  if( d != s2->depth )
    return;
  
  /* 2. reallocate the memory */
  /* after memory is reallocated all the pointers have to be recalculated */
  ODE_storage_realloc(s1, s2);
  
  /* 3. copy the s2->data to s1->data */
  memcpy( s1->data + s1->size[d-1], s2->data, s2->size[d-1] * sizeof(ODE_R) );

  /* 4. assign pointers to data copied to s1 */
  ODE_storage_recalculate_pointers(s1, s2);


  /* 5. alter s1->size */
  {
    int i;
    for ( i = 0; i < d; i++)
      s1->size[i]+=s2->size[i];
  }
}


void ODE_storage_print( ODE_storage * s)
{
  char fmt[] = " %3i |";
  int offset = 4, d = s->depth, shift;
  
  printf("Storage dump:\n");
  printf("Size: {");
	
  {
    int i,j;

    for( i = 0; i < s->depth; i++ )
      printf(" %i", s->size[i]);
    printf(" }\n");

    /* there are always three cases to be treated separately
     1. s->ptrs[i] with i=0.. depth-3 which contain pointers to (void *)
     2. s->ptrs[depth-2] which contains pointers to (ODE_R *)
     3. s->data which contains ODE_R */
    /* 1. */
    for( i = 0; i < s->depth - 1; i++ )
      {
	/* print pointer offset */
  	printf("lvl %3i (%i el.):  |", i, s->size[i] );
	
  	if( s->size[i] <= 10 )
  	  for( j = 0; j < s->size[i]; j++ )
	    {
	      if (i == d-2)
		shift =((ODE_R*)s->ptrs[i][j] - (ODE_R*)s->ptrs[i][0]);
	      else
		shift = s->ptrs[i][j] - s->ptrs[i][0];
	      printf(fmt,shift);
	    }
	
  	else
  	  {
  	    for( j = 0; j < offset; j++ )
	      {
		if (i == d-2)
		shift =((ODE_R*)s->ptrs[i][j] - (ODE_R*)s->ptrs[i][0]);
	      else
		shift = s->ptrs[i][j] - s->ptrs[i][0];
		printf(fmt, shift);
	      }
	    
	    
  	    printf(" (...) |");

  	    for( j = s->size[i]-1; j > s->size[i] - offset - 1; j-- )
	      {
		if (i == d-2)
		  shift =((ODE_R*)s->ptrs[i][j] - (ODE_R*)s->ptrs[i][0]);
		else
		  shift = s->ptrs[i][j] - s->ptrs[i][0];
		printf(fmt, s->ptrs[i][j] - s->ptrs[i][0]);
	      }
	    
  	  }
  	printf("\n");
      }

    /* last row is printed according to a data type stored in it */
    printf("lvl %3i (%i el.):  |", i, s->size[s->depth - 1] );

    if( s->size[s->depth-1] <= 10 )
      for( j = 0; j < s->size[s->depth-1]; j++ )
    	printf(" " ODE_FMT " |", s->data[j]);
    else
      {
    	for( j = 0; j < offset; j++ )
    	  printf(" " ODE_FMT " |", s->data[j]);
    
    	printf(" (...) |");
    
    	for( j = s->size[s->depth-1] - 1; j > s->size[s->depth-1] - offset - 1; j-- )
    	  printf(" " ODE_FMT " |", s->data[j]);
      }
    printf("\n");
  }
}

ODE_storage * ODE_storage_init( int depth, int * size )
{
  ODE_storage * s = ODE_MALLOC( 1, ODE_storage );

  s->size = ODE_MALLOC( depth, int );
  s->ptrs = ODE_MALLOC( depth - 1, void ***);
  s->data = ODE_MALLOC( size[depth-1], ODE_R );

  memcpy( s->size, size, depth * sizeof(int) );
  
  {
    int i,j;
    for( i = 0; i < depth - 1; i++ )
      s->ptrs[i] = ODE_MALLOC( size[i], void ** );
    
    for( i = 0; i < depth - 2; i++ )
      s->ptrs[i][0] = (void **)s->ptrs[i+1];
    
    s->ptrs[depth-2][0] = (void **) s->data;

    for( i = 0; i < depth - 1; i++ )
      for (j = 0; j < size[i]; j++)
	s->ptrs[i][j] = s->ptrs[i][0];
    
    for( i = 0; i < size[depth-1]; i++ )
      s->data[i] = (ODE_R)i;
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

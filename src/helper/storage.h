/**
 * @file   storage.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Mon Apr 11 15:59:12 2011
 * 
 * @brief  Storage.
 *
 * @sa #ODE_storage
 * 
 */
#include "common.h"

#ifndef _STORAGE_H_
#define _STORAGE_H_

/**
 * Structure to maintain n-dimensional table. Table entries are stored
 * in #data and #ptrs is a table of pointers used to access the #data
 * in a convenient way. A typical usage example:
 *
 * @code
 * int * a = {2,3,4};
 * ODE_storage * s = ODE_storage_init_array( 3, a );
 * ODE_R *** table = (ODE_R***)ODE_storage_get_array( s );
 * table[1][2][3] = (ODE_R)1.;
 * @endcode
 *
 * Here a table of dimension 3 is generated and accessed by casting
 * #ptrs to (ODE_R ***). Now it is possible to access a table element
 * by referencing to it by table[1][2][3].
 *
 * Most important of all, #data is allocated as a one continuous block
 * of memory, and it can be accessed by #data[i]. The inside structure
 * is maintained by #ptrs in a following way. #ptrs[0] is a table of
 * pointers to elements of #ptrs[1], which are in turn pointers to
 * #ptrs[2] etc., with an exception for #ptrs[depth-2] which holds
 * pointers to #data. This way after if #ptrs is casted to (ODE_R
 * *(...)*) with #depth being a number of stars we obtain a perfectly
 * valid pointer structure.
 *
 * #ODE_storage is a more general structure which can store any type
 *   of cascade pointers. An empty pointer structure is allocated
 *   using ODE_storage_init(n,size) where n is a number of levels of
 *   cascade and size is a table of lengths of each level.
 *
 */

struct ODE_storage
{
  /** pointer cascade */
  void **** ptrs;
  /** data is stored in this linear table */
  ODE_R * data;
  /** size of each level */
  int * size;
  /** number of cascade levels, or length of #ptrs+1 (+1 is from #data) */
  int depth;
};

/** 
 * Function used to add two ODE_storages in place. This means that s1
 * holds a result of addition. Addition is realized by appending #ptrs
 * and #data of #s2 to #s1 and recalculating the pointers.
 *
 * @attention s1 is overwritten by this operation
 * 
 * @param s1 result of addition
 * @param s2 storage to be appended to s1
 */
void ODE_storage_add( ODE_storage * s1, ODE_storage * s2 );

/** 
 * Function used to print contents of s
 * 
 * @param s 
 */
void ODE_storage_print( ODE_storage * s);

/** 
 * Function used to initialize an empty storage
 * 
 * @param depth 
 * @param size 
 * 
 * @return ODE_storage
 */
ODE_storage * ODE_storage_init( int depth, int * size );

/** 
 * Function used to initialize ODE_storage which holds a pointer
 * structure of a #depth -dimensional matrix.
 * 
 * @param depth dimension of a matrix
 * @param dim size of each level of a matrix
 * 
 * @return ODE_storage
 */
ODE_storage * ODE_storage_init_array( int depth, int * dim );

/** 
 * Free a storage
 * 
 * @param s Storage to be freed
 */
void ODE_storage_free( ODE_storage * s );

/** 
 * Helper function used to increase a size of an ODE_storage by #size
 * 
 * @param s1 
 * @param size
 */
void ODE_storage_realloc(ODE_storage *s1, int * size);

/** 
 * Helper function used to fill the new space after applying
 * ODE_storage_reallo(s1, s2->size) with pointer structure from s2.
 * 
 * @param s1 
 * @param s2
 * @param add if 0 then recalculates pointers for addition,
 *  if 1 then recalculates pointers for copying
 */
void ODE_storage_recalculate_pointers(ODE_storage *s1, ODE_storage *s2, int add);

/** 
 * Accessor to the pointer to be casted to an array
 * 
 * @param s 
 * 
 * @return pointer to be casted to an array
 */
void * ODE_storage_get_array( ODE_storage * s );

/** 
 * Creates an exact copy of the storage.
 * 
 * @param src storage to be copied
 * 
 * @return copied src
 */
ODE_storage * ODE_storage_copy( ODE_storage * src );

#endif /* _STORAGE_H_ */

/**
 * @file   macro.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Thu Apr  7 11:50:54 2011
 * 
 * @brief  Macros used by yapdes
 * 
 * 
 */

#ifndef _MACRO_H_
#define _MACRO_H_

/** 
 * macro to wrap a malloc
 * 
 * @param size number of table elements to alloc
 * @param type type of an element
 * 
 * @return pointer to an allocated memory casted to an appropriate type
 *
 * @todo fix this to include check weather a memory has been allocated
 * successfuly
 */

#define ODE_MALLOC(size,type) (type *)malloc(size * sizeof(type))

/** @todo report a double free error if ptr==NULL */
#define ODE_FREE(ptr) {if(ptr) free(ptr); ptr=NULL;}

/** 
 * Realloc
 * 
 * @param ptr  Pointer to reallocate
 * @param n    New size (should be >0, see bug)
 * @param type Type of the variable to allocate
 * 
 * @return pointer to a type (cast included)
 */
/** @bug possible bug if ODE_REALLOC is used with n=0, which is the
    case when it works as free instead of ODE_FREE */
#define ODE_REALLOC(ptr,n,type) (type *)realloc((void * )ptr, (n) * sizeof(type))

/** 
 * MAXXX!!!!
 * 
 * @param a loose
 * @param b win
 * 
 * @return win!
 */
#define MAX(a,b) (a<b?b:a)

/** 
 * MINNN!!!!
 * 
 * @param a loose
 * @param b win
 * 
 * @return loose!
 */
#define MIN(a,b) (a>b?b:a)

#endif /* _MACRO_H_ */

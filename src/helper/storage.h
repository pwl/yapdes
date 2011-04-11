/**
 * @file   storage.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Mon Apr 11 15:59:12 2011
 * 
 * @brief  storage structure to help managing this nasty structure
 * 
 * 
 */
#include "common.h"

#ifndef _STORAGE_H_
#define _STORAGE_H_

struct ODE_storage
{
  void *** ptrs;
  ODE_R * data;
  int * size;
  int depth;
};


void ODE_storage_add( ODE_storage * s1, ODE_storage * s2 );

void ODE_storage_print( ODE_storage * s, int offset );

ODE_storage * ODE_storage_init( int depth, int * size );


void ODE_storage_free( ODE_storage * s );


#endif /* _STORAGE_H_ */

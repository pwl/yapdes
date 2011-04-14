/**
 * @addtogroup helper
 * @{
 * 
 * @file   dictionary.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Tue Apr  5 12:59:36 2011
 *
 * @brief Simple dictionary structure to translate multicharacter
 * constants (represented as ints) to an index of a table
 *
 * @todo Global! Use realloc each time an element is added instead of
 * allocating big chunks of memory in advance.
 *
 * @todo implement dictionary for modules and triggers.
 *
 * Dictionary is a facility to translate a multicharacter constant to
 * an index of a table. It is used to make a user friendly
 * identification system for tables of structures. Instead of
 * remembering which index corresponds to an index we are looking for
 * we embedd a dictionary in a structure containing a table and use it
 * to store and retrieve an index using a multichar. The translations
 * can be symbollicaly written as follows @n
 *
 * 'f1' => 2@n
 * 'ym' => 3
 *
 * A simplest way to implement a dictionary is to use a table of
 * integers containing multicharacter constants. Then an index we are
 * looking for is a position of a respective multicharacter in such
 * table.
 *
 * @attention This simple implementation does not facility removing
 * indices from a table.
 *
 * @todo increase a dictionary performence by adding a "last accessed"
 * index
 * 
 *
 */
#pragma once
#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include "common.h"

/**
 * This implementation relies on the following structure, where #mc is
 * a table of multicharacter constants of which indices are used to
 * translate multicharacter to an integer value, i.e. multicharacter
 * has index @v i iff mc[i]=multicharacter.
 * 
 */

struct ODE_dictionary
{
  /** multicharacter constants to be stored here */
  int * mc;
  /** length of #mc */
  int n;
};


/** 
 * Get an index from a dictionary given #mc
 * 
 * @param d dictionary to search
 * @param mc multi-char constant
 * 
 * @return index related to #mc
 * @retval -1 if #mc is not in a dictionary
 */
int ODE_dictionary_get_index( ODE_dictionary * d, int mc );

/** 
 * Set a multi-char #mc constant to be related to a given index
 * 
 * @param d dictionary to change
 * @param index to be related to #mc
 * @param mc multi-char constant
 *
 * @return added mc?
 *
 * @retval 0 success
 * @retval 1 error adding a word to a dictionary
 */
int ODE_dictionary_set_index( ODE_dictionary * d, int index, int mc );

/** 
 * Standard initialization
 * 
 * 
 * @return A pointer to an initialized dictionary
 */
ODE_dictionary * ODE_dictionary_init( void );

/** 
 * Standard free
 * 
 * @param d Pointer to an allocated dictionary.
 */
void ODE_dictionary_free( ODE_dictionary * d );

#endif /* _DICTIONARY_H_ */

/** @} */

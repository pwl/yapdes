/**
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
 */

struct ODE_dictionary
{
  /** multicharacter constants to be stored here */
  int * mc;
  /** length of #mc */
  int n;
};


int ODE_dictionary_get_index( ODE_dictionary * d, int mc );

int ODE_dictionary_push_record( ODE_dictionary * d, int mc );


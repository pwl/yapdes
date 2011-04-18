/**
 * @file   data_type.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Fri Apr 15 00:38:59 2011
 *
 * @brief File containing forward declarations of most data types used
 * in yapdes
 *
 *
 */
#pragma once
#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_

/** define a type used by the whole library */
/* #define ODE_R_LONG_DOUBLE */
/* #define ODE_R_DOUBLE */
#define ODE_R_MPREAL		/* as for now no othe type works */

#undef ODE_REAL

/**@name predefined data types along with formatting of the output
   @{*/
#ifdef ODE_R_LONG_DOUBLE
#define ODE_FMT "% 1.1Lf"
#define ODE_REAL long double
#define ODE_INIT()		/* empty definition */
#endif

#ifdef ODE_R_DOUBLE
#define ODE_FMT "% 1.1f"
#define ODE_REAL double
#define ODE_INIT()		/* empty definition */
#endif

#ifdef ODE_R_MPREAL
#include <iostream>
#include <mpreal.h>
#include <dlmalloc.h>
/* #define malloc dlmalloc */
/* #define calloc dlcalloc */
/* #define realloc dlrealloc */
/* #define free dlfree */
#define ODE_FMT ""
#define ODE_REAL mpreal
using namespace mpfr;
using namespace std;
#define ODE_INIT()				\
  {						\
    mpreal::set_default_prec(1000);		\
    cout.precision(15);				\
  }
#endif
/**@}*/

#ifndef ODE_REAL
#error "===ODE_REAL undefined==="
#error "Define it in data_type.h"
#endif

/** ODE_R is a data type used thoroughout the whole yapdes and is
    intended to store real variables */
typedef ODE_REAL ODE_R;
/* #define ODE_R ODE_REAL */

/** @name Default data types for solver */
/**@{*/
/** type for unsigned int, (mainly flags) - @bug obsolate, use int instead */
typedef unsigned int	ODE_uint;
/**@}*/

#endif /* _DATA_TYPE_H_ */

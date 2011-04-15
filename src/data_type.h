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
#define ODE_R_GMPF

#undef ODE_REAL

/**@name predefined data types along with formatting of the output
   @{*/
#ifdef ODE_R_LONG_DOUBLE
#define ODE_FMT "% 1.1Lf"
#define ODE_REAL long double
#endif

#ifdef ODE_R_DOUBLE
#define ODE_FMT "% 1.1f"
#define ODE_REAL double
#endif

#ifdef ODE_R_GMPF
#include <gmpxx.h>
#define ODE_FMT ""
#define ODE_REAL mpf_class
#endif
/**@}*/

#ifndef ODE_REAL
#error "===ODE_REAL undefined==="
#error "Define it in data_type.h"
#endif

/** ODE_R is a data type used thoroughout the whole yapdes and is
    intended to store real variables */
typedef ODE_REAL ODE_R;

/** @name Default data types for solver */
/**@{*/
/** type for unsigned int, (mainly flags) - @bug obsolate, use int instead */
typedef unsigned int	ODE_uint;
/**@}*/

#endif /* _DATA_TYPE_H_ */

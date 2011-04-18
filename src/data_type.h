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
#define ODE_R_MPREAL

#undef ODE_REAL


/**@name predefined data types along with formatting of the output
   @{*/
#ifdef ODE_R_LONG_DOUBLE
#include "data_type/long_double.h"
#endif

#ifdef ODE_R_DOUBLE
#include "data_type/double.h"
#endif

#ifdef ODE_R_MPREAL
#include "data_type/mpreal.h"
#endif
/**@}*/

#ifndef ODE_REAL
#error "===ODE_REAL undefined==="
#error "Define it in data_type.h"
#endif

/* default ODE_INIT */
#ifndef ODE_INIT
#define ODE_INIT() {}
#endif

/* default print */
#ifndef ODE_RP
#define ODE_RP() {}
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

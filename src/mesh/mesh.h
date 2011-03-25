/**
 * @addtogroup Mesh
 * @{
 *
 * @file   mesh.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Thu Mar 24 17:06:09 2011
 *
 * @brief A prototype of a mesh structure to store a set of points
 * along with a numerical differentiation, interpolation etc.
 *
 * What should mesh do:
 * - Interpolation
 * - Numerical differentiation (with caching)
 * - Initialization from a function(s)
 *
 *
 */

#include "common.h"

#ifndef _MESH_H_
#define _MESH_H_

struct ODE_mesh
{
  int (*interpolate_at_point) ( ODE_mesh *, ODE_R, ODE_table * );
  int (*interpolate_at_points)( ODE_mesh *, ODE_table *, ODE_table * );
  int (*fill_from_function)   ( ODE_mesh *, ODE_R (*f)( ODE_R ));
  int (*calculate_derivative) ( ODE_mesh * m, ODE_R * d, ODE_uint * k);

  ODE_table * f;
  ODE_table * mesh;
  ODE_table ** cache;
  void * data;
};

#endif /* _MESH_H_ */

/** @}*/

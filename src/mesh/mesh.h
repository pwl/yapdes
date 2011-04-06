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
 * - Numerical differentiation (with optional caching)
 * - Initialization from a function(s) <- probably to be left to a module
 * -
 *
 */

#include "common.h"

#ifndef _MESH_H_
#define _MESH_H_

/**
 * Mesh is a predefined set of points @f$x_i@f$ (#mesh) and function
 * values associated with those points @f$f_j(x_i)@f$ (#f) with a set
 * of facilities to perform a numerical differentiation. How the
 * differentiation is performed is dependent on a particular
 * implementation, #ODE_mesh is only a framework structure to create a
 * universal interface to such implementations.
 *
 */
struct ODE_mesh
{
  /**@name Derivative calculation
     Theese are a functions dependent on a particular implementation.
     @{*/
  int (*interpolate_at_point) ( ODE_mesh * m, ODE_R, ODE_table * );
  int (*interpolate_at_points)( ODE_mesh * m, ODE_table *, ODE_table * );
  int (*fill_from_function)   ( ODE_mesh * m, ODE_R (*f)( ODE_R ));
  int (*calculate_derivative) ( ODE_mesh * m, ODE_R * d, ODE_uint * k);
  /**@}*/

  /** Dimension of the mesh, can be = 0, not supported right now */
  int dim;

  /** number of mesh points */
  int n;

  /** Number of functions defined at each point of the mesh */
  int ind;

  /** Maximal rank of derivative this mesh can calculate. @c maxrk=1
      means only the first derivative can be calculated */
  int maxrk;

  /** Values of the mesh points, table of size #n, elements are\n
      @c mesh[i] @f$=x_i, \quad i\in@f$ [0,@c n-1]*/
  ODE_R * mesh;

  /** Values at the mesh points, table of size #ind x #n, elements are\n
      @c f[i][j] @f$=f_i(x_j), \quad (i,j)\in@f$ [0,@c ind-1]x[0,@c n-1]*/
  ODE_R ** f;

  /** Values of cached derivatives, table of size #maxrk x #ind x #n,
      elements are\n @c cache[i][j][k] @f$=D^{i+1} f_j(x_k), \quad
      (i,j,k)\in@f$ [0,@c maxrk-1]x[0,@c ind-1]x[0,@c n-1]*/
  ODE_R *** cache;

  /** #dict contains the aliases of the function names. Using it one
       can keep track on the functions indices by giving them names
       (multichars) */
  ODE_dictionary * dict;

  /** To be filled with data specific to a particular mesh
      implementation */
  void * data;
};

/** 
 * use this function to get a pointer to a function with the name
 * #mc. A returned pointer can be used to access memory fast.
 * 
 * @param m 
 * @param mc multicharacter name
 * 
 * @return pointer to a function with a name #mc
 */
ODE_R * ODE_mesh_get_f_ptr(ODE_mesh * m, int mc);

/** 
 * Use this to set an i-th member of the function named #mc to a value
 * #val. This way is probably slow as it has to search for a correct
 * name in a dictionary at every call.
 * 
 * @param m 
 * @param mc
 * @param i
 * @param val 
 * 
 */
void ODE_mesh_set_f(ODE_mesh * m, int mc, int i, ODE_R val);

#endif /* _MESH_H_ */

/** @}*/

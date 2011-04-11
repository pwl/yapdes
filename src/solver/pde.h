/**
 * @file   pde.h
 * @author Pawel Biernat <pawel.biernat@gmail.com>
 * @date   Mon Apr  4 12:42:16 2011
 *
 * @brief  Structure to connect #ODE_mesh with #ODE_rhs.
 *
 *
 */
#ifndef _PDE_H_
#define _PDE_H_

#include "common.h"
#include "mesh/mesh.h"

/**
 * Keeps a mesh and a calculated rhs of the equation together.
 *
 */

struct ODE_pde
{
  /** table of meshes */
  ODE_mesh ** mesh;

  /** A place to store the function values on different meshes. The
      memory structure is exactely the same as #rhs, in order to pass
      #f to any marcher */
  ODE_R *** f;

  /** Calculated rhs is stored here, its structure is as follows
   rhs[i][j][k] corresponds to d/dt of mesh[i]->f[j] at
   mesh[i]->x[k]. The underlying memory structure is a one block, so
   that rhs[0][0] can be given to a marcher  */
  ODE_R *** rhs;

  /** number of meshes assigned to ODE_pde */
  int mesh_n;
};

/**
 * This function allocates
 *
 *
 * @return
 */
ODE_pde * ODE_pde_init( void );

void ODE_pde_free( ODE_pde * pde );

/**
 * Adds a mesh to an already allocated ODE_pde, thus calling realloc
 * to expand #f and #rhs.
 *
 * @param m mesh to be added.
 */
void ODE_pde_add_mesh( ODE_pde * pde, ODE_mesh * m );

/**
 * Calculates a size of a memory chunk (i.e. a number of values
 * stored) allocated in #f and #rhs (which is assumed to be the same)
 *
 * @param pde
 *
 * @return length of #f[0][0]
 */
int ODE_pde_size( ODE_pde * pde );



#endif /* _PDE_H_ */

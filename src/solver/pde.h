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
#include "helper/storage.h"

/**
 * Keeps a mesh and a calculated rhs of the equation together.
 *
 */

struct ODE_pde
{
  /** table of meshes */
  ODE_mesh ** mesh;

  /* /\** A place to store the function values on different meshes. The */
  /*     memory structure is exactely the same as #rhs, in order to pass */
  /*     #f to any marcher *\/ */
  /* ODE_R * f; */

  /* /\** Calculated rhs is stored here, its structure is as follows */
  /*  rhs[i][j][k] corresponds to d/dt of mesh[i]->f[j] at */
  /*  mesh[i]->x[k]. The underlying memory structure is a one block, so */
  /*  that rhs[0][0] can be given to a marcher  *\/ */
  /* ODE_R * rhs; */

  /**@name storages used to align memory for #f and #rhs
     @{*/
  ODE_storage * s_f;
  ODE_storage * s_rhs;
  /**@}*/
  
  /** number of meshes assigned to ODE_pde */
  int mesh_n;

  /** dictionary to hold mesh names */
  ODE_dictionary * dict;
};

/**
 * This function allocates
 *
 *
 * @return
 */
ODE_pde * ODE_pde_init( void );

/** 
 * Standard free
 * 
 * @param pde 
 */
void ODE_pde_free( ODE_pde * pde );

/**
 * Adds a mesh to an already allocated ODE_pde, thus calling realloc
 * to expand #f and #rhs.
 *
 * @param m mesh to be added.
 */
void ODE_pde_add_mesh( ODE_pde * pde, ODE_mesh * m , int name);

/**
 * Calculates a size of a memory chunk (i.e. a number of values
 * stored) allocated in #f and #rhs (which is assumed to be the same)
 *
 * @param pde
 *
 * @return length of #f[0][0]
 */
int ODE_pde_size( ODE_pde * pde );

/** 
 * Get a mesh by giving its name
 * 
 * @param pde pde to extract a mesh from
 * @param name name of the mesh
 * 
 * @return Mesh matching a name
 * @retval NULL no mesh of a given name was found
 */
ODE_mesh * ODE_pde_get_mesh( ODE_pde * pde, int name );

/** 
 * Helper function to ODE_pde_get_mesh_f()
 * 
 * @param pde pde to search
 * @param mesh_name multicharacter name
 * @param f_name multicharacter name
 * @param out two dimensional array to store found indices. out[0] is
 * an index of a mesh, out[1] is an index of a function
 * 
 * @retval 0 success
 * @retval -1 failed to find either mesh or function index
 * 
 */
int ODE_pde_get_mesh_and_f_index( ODE_pde * pde, int mesh_name, int f_name, int * out );

/** 
 * Points *f and *rhs to a starting point of a memory where a function
 * (or a rhs respectively) named f_name and defined on a mesh
 * mesh_name is located. If f or rhs is NULL it is ignored.
 * 
 * @param[in] pde 
 * @param[in] mesh_name 
 * @param[in] f_name 
 * @param[out] f 
 * @param[out] rhs 
 */
void ODE_pde_get_mesh_f( ODE_pde * pde, int mesh_name,
			 int f_name, ODE_R ** f, ODE_R ** rhs );

/** 
 * Points *f and *rhs to a beginning of a long memory block where all
 * the data from all meshes is located. If f or rhs is NULL it is
 * ignored.
 * 
 * @param pde 
 * @param f 
 * @param rhs 
 */  
void ODE_pde_get_vector( ODE_pde * pde, ODE_R ** f, ODE_R ** rhs );

#endif /* _PDE_H_ */

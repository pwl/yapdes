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

/**
 * Keeps a mesh and a calculated rhs of the equation together.
 *
 */

struct ODE_pde
{
  ODE_mesh * mesh;
  ODE_R * rhs;
};


#endif /* _PDE_H_ */

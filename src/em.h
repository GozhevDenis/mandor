/** \file em.h
  * \brief Maxwell solver: electromagnetic, FDTD, scheme of Yee.
  *
  * See [A. Taflove "Computational Electrodynamics: The Finite-Difference
  * Time-Domain Method",  ISBN-13: 978-1580538329, ISBN-10: 1580538320 ].
  *
  * Second order Yee scheme with central differences and staggered meshes.
  *
  * Scheme conserves div(E) and div(H) with numerical accuracy.
  *
  * Node locations:
  *
  * t = n·Δt:
  *     Ex(i, j, k)   =>  Ex( (i - 1/2)·Δx,     j·Δy,         k·Δz     )
  *     Ey(i, j, k)   =>  Ey(     i·Δx,     (j - 1/2)·Δy,     k·Δz     )
  *     Ez(i, j, k)   =>  Ez(     i·Δx,         j·Δy,     (k - 1/2)·Δz )
  *
  * t = (n - 1/2)·Δt:
  *     Hx(i, j, k)   =>  Hx(     i·Δx,   , (j - 1/2)·Δy, (k - 1/2)·Δz )
  *     Hy(i, j, k)   =>  Hy( (i - 1/2)·Δx,     j·Δy,     (k - 1/2)·Δz )
  *     Hz(i, j, k)   =>  Hz( (i - 1/2)·Δx, (j - 1/2)·Δy,     k·Δz     )
  *
  * So, each component is shifted <b>in negative direction by the half of
  * respected step</b>: electric field - along the corresponding component,
  * magnetic field - in both remaining directions. Magnetic field also is
  * defined on the half timestep into the past.
  *
  * The same information in LaTeX form, for the Doxygen:
  * \f[
  *   \begin{array}{llll}
  *   \vec H[i][j][k] = & \{ H_{x\ i,\     j-1/2,\ k-1/2}^{n-1/2};  \quad
  *                     &    H_{y\ i-1/2,\ j,\     k-1/2}^{n-1/2};  \quad
  *                     &    H_{z\ i-1/2,\ j-1/2,\ k    }^{n-1/2} \}\\[3mm]
  *   \vec E[i][j][k] = & \{ E_{x\ i-1/2,\ j,\     k    }^{n};
  *                     &    E_{y\ i,\     j-1/2,\ k    }^{n};
  *                     &    E_{z\ i,\     j,    \ k-1/2}^{n} \}
  *   \end{array}
  * \f]
  *
  * In other words, 'E(i+1, j, k).v.x' is 'Ex((i + 0.5)*h₁, j*h₂, k*h₃)'.
  *
  * Time step
  * ---------
  * E is defined in [-1, I+1] domain.
  * H is defined in [ 0, I+1] domain.
  *
  * HStep: evaluates new H in [0, I+1] domain.
  * EStep: evaluates new E in [0, I-1] domain.
  *
  * Boundary conditions restore E in nodes {-1, I, I+1}.
  */
#pragma once


#include "type_vector.h"
#include "type_mesh.h"



void em_HStep(mesh_t<vec3d_t> &E, mesh_t<vec3d_t> &H);
void em_EStep(mesh_t<vec3d_t> &E, mesh_t<vec3d_t> &H);


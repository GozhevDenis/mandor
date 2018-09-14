#include <cassert>
#include <cmath>

#include "em.h"
#include "testConstMacros.h"


void em_HStep(mesh_t<vec3d_t> &E, mesh_t<vec3d_t> &H)
{
   //static_assert(DR == DX && DR == DY && DR == DZ);
   assert( std::fabs( dr - dx ) < EPS &&
           std::fabs( dr - dy ) < EPS &&
           std::fabs( dr - dz ) < EPS );

// TODO: ticket Den about the source for ca, cb.

   const double db = dt / dr;
   for (int i = cpu_min[0] ; i <= cpu_max[0] ; ++i)
   for (int j = cpu_min[1] ; j <= cpu_max[1] ; ++j)
   for (int k = cpu_min[2] ; k <= cpu_max[2] ; ++k) {
      H(i, j, k).v.x += db * ( E(i, j, k+1).v.y - E(i, j,   k).v.y +
                               E(i, j, k  ).v.z - E(i, j+1, k).v.z );
      H(i, j, k).v.y += db * ( E(i+1, j, k).v.z - E(i, j, k  ).v.z +
                               E(i,   j, k).v.x - E(i, j, k+1).v.x );
      H(i, j, k).v.z += db * ( E(i, j+1, k).v.x - E(i,   j, k).v.x +
                               E(i, j,   k).v.y - E(i+1, j, k).v.y );
   }
}

void em_EStep(mesh_t<vec3d_t> &E, mesh_t<vec3d_t> &H)
{
   //static_assert(DR == DX && DR == DY && DR == DZ);
   assert( std::fabs( dr - dx ) < EPS &&
           std::fabs( dr - dy ) < EPS &&
           std::fabs( dr - dz ) < EPS );
// TODO: ticket Den about the source for ca, cb.

   const double cb = dt / dr;
   for (int i = cpu_min[0] ; i <= cpu_max[0] ; ++i)
   for (int j = cpu_min[1] ; j <= cpu_max[1] ; ++j)
   for (int k = cpu_min[2] ; k <= cpu_max[2] ; ++k) {
      E(i, j, k).v.x += cb * ( H(i, j, k  ).v.z - H(i, j-1, k).v.z +
                               H(i, j, k-1).v.y - H(i, j,   k).v.y );
      E(i, j, k).v.y += cb * ( H(i,   j, k).v.x - H(i, j, k-1).v.x +
                               H(i-1, j, k).v.z - H(i, j, k  ).v.z );
      E(i, j, k).v.z += cb * ( H(i, j,   k).v.y - H(i-1, j, k).v.y +
                               H(i, j-1, k).v.x - H(i,   j, k).v.x );
   }
}

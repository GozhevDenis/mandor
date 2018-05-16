#include <iostream>

#include "testConstMacros.h"

#include "PeriodicBoundaryConditions.h"

void PeriodicConditions( mesh_t<vec3d_t> & V )
{
   for ( int j = cpu_min[1] ; j <= cpu_max[1] ; ++j )
   for ( int k = cpu_min[2] ; k <= cpu_max[2] ; ++k ) {
      V(cpu_min[0] - 1, j, k) = V(cpu_max[0], j, k);
      V(cpu_max[0] + 1, j, k) = V(cpu_min[0], j, k);
   }

   for ( int i = cpu_min[0] + 1 ; i <= cpu_max[0] + 1 ; ++i )        // NOLINT
   for ( int k = cpu_min[2]     ; k <= cpu_max[2]     ; ++k ) {
      V(i, cpu_min[1] - 1, k) = V(i, cpu_max[1], k);
      V(i, cpu_max[1] + 1, k) = V(i, cpu_min[1], k);
   }

   for ( int i = cpu_min[0] - 1 ; i <= cpu_max[0] + 1 ; ++i )        // NOLINT
   for ( int j = cpu_min[1] - 1 ; j <= cpu_max[1] + 1 ; ++j ) {
      V(i, j, cpu_min[2] - 1) = V(i, j, cpu_max[2]);
      V(i, j, cpu_max[2] + 1) = V(i, j, cpu_min[2]);
   }
}

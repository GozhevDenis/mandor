#include <iostream>
#include <fstream>

#include "easylogging/easylogging++.h"

#include "type_vector.h"
#include "type_mesh.h"
#include "planeWave.h"
#include "PeriodicBoundaryConditions.h"

#include "em.h"


// TODO: `easylogging::CHECK` doesn't abort MPI applications correctly (check
//       atexit).

// TODO: do -lto (link time optimization) and -pgo (profile guided optimization).


INITIALIZE_EASYLOGGINGPP // NOLINT


int main()
{
   // TODO: here we may utilize `node(cpu_min) - node(1, 1, 1)` algebra.
   mesh_t<vec3d_t> E( cpu_min[0] - 1, cpu_min[1] - 1, cpu_min[2] - 1,
                      cpu_max[0] + 1, cpu_max[1] + 1, cpu_max[2] + 1,
                      "E" ),
                   H( cpu_min[0] - 1, cpu_min[1] - 1, cpu_min[2] - 1,
                      cpu_max[0] + 1, cpu_max[1] + 1, cpu_max[2] + 1,
                      "E" );

   EWaveStart( E, H );

   std::ofstream fout( "output.dat" );

   int tN = 1000;
   for ( int t  = 0 ; t < tN ; ++t ) {
      em_EStep( E, H );
      PeriodicConditions( E );

      em_HStep( E, H );
      PeriodicConditions( H );

      std::cout << t << std::endl;
      if ( t % 1 == 0 ) {
         fout << t << "\t" << E(1, 5, 10).v.y << "\n";
      }
   }

   return 0;
}

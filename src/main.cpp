#include <iostream>
#include <fstream>

#include "easylogging/easylogging++.h"

#include "type_vector.h"
#include "type_mesh.h"
#include "planeWave.h"
#include "PeriodicBoundaryConditions.h"
#include "initCondit.h"

#include "em.h"


// TODO: `easylogging::CHECK` doesn't abort MPI applications correctly (check
//       atexit).

// TODO: do -lto (link time optimization) and -pgo (profile guided optimization).


INITIALIZE_EASYLOGGINGPP // NOLINT

// Подумать, как эти параметры переписать подругому
int    min[3];
int    max[3];

double dx,
       dy,
       dz;
double l[3];

double dt,
       nStep;
int cpu_min[3],
    cpu_max[3];

const double dr = 0.01;


int main()
{
   // Initialization parameteres
   setInitCond();
   // TODO: here we may utilize `node(cpu_min) - node(1, 1, 1)` algebra.
   mesh_t<vec3d_t> E( cpu_min, cpu_max, "E" );
   mesh_t<vec3d_t> H( cpu_min, cpu_max, "H" );


   EWaveStart( E, H );


   for ( int t  = 0 ; t < nStep ; ++t ) {
      em_HStep( E, H );
      PeriodicConditions( H );

      em_EStep( E, H );
      PeriodicConditions( E );

      std::cout << t << std::endl;
      if ( t % 100 == 0 ) {
         E.save( "../output/EM/EM", t  );
      }
   }

   return 0;
}

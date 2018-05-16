#include <iostream>
#include <fstream>

#include "easylogging/easylogging++.h"

#include "type_vector.h"
#include "type_mesh.h"
#include "planeWave.h"
#include "PeriodicBoundaryConditions.h"

#include "em.h"


INITIALIZE_EASYLOGGINGPP // NOLINT

int main()
{
    mesh_t<vec3d_t> E(0, 0, 0, 102, 102, 102, "E"),
					H(0, 0, 0, 102, 102, 102, "H");

    EWaveStart(E);
    PeriodicConditions(E);
    em_HStep(E, H);
    PeriodicConditions(H);

    std::ofstream fout("output.dat");
    double tN = 1000;
    for (int t = 0 ; t < tN ; ++t) {
		em_EStep(E, H);
		PeriodicConditions(E);
		em_HStep(E, H);
		PeriodicConditions(H);
		std::cout << t << std::endl;
		if (t % 1 == 0) {
			fout << t << "\t" << E(1, 5, 10).v.y << "\n";
		}
	}
    fout.close();

	return 0;
}

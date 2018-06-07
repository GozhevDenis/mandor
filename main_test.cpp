#include "easylogging\easylogging++.h"
#include <ctime>
#include "type_vector.h"
#include "type_mesh.h"
#include "planeWave.h"
#include "PeriodicBoundaryConditions.h"
#include "em.h"
#include <fstream>

#include <iostream>

INITIALIZE_EASYLOGGINGPP

int main()
{
	double tN = 1000;
   unsigned int start_time = clock();
	std::ofstream fout("output.dat");
	mesh_t<vec3d_t> E(0, 0, 0, 102, 102, 102, "E"),
					H(0, 0, 0, 102, 102, 102, "H");
	EWaveStart(E);
	PeriodicConditions(E);
	//std::cout  << E(E.imin, 10, 10).v.y << " " <<  E(E.imin + 1, 10, 10).v.y << std::endl;
	//em_HStep(E, H);
	HWaveStart(H);
	PeriodicConditions(H);
	for (int t = 0; t < tN; ++t) {
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
   unsigned int end_time = clock(); // конечное время
   unsigned int search_time = end_time - start_time;
   std::cout << search_time << std::endl;
	//system("pause");
	return 0;
}

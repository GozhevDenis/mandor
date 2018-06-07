#include "PeriodicBoundaryConditions.h"
#include <iostream>

void PeriodicConditions(mesh_t<vec3d_t> &V)
{
	for (int j = V.jmin + 1; j <= V.jmax - 1; ++j)
		for (int k = V.kmin + 1; k <= V.kmax - 1; ++k) {
			V(V.imin, j, k) = V(V.imax - 1, j, k);
			V(V.imax, j, k) = V(V.imin + 1, j, k);
		}
	for (int i = V.imin + 1; i <= V.imax - 1; ++i)
		for (int k = V.kmin + 1; k <= V.kmax - 1; ++k) {
			V(i, V.jmin, k) = V(i, V.jmax - 1, k);
			V(i, V.jmax, k) = V(i, V.jmin + 1, k);
		}
	for (int i = V.imin + 1; i <= V.imax - 1; ++i)
		for (int j = V.jmin + 1; j <= V.jmax - 1; ++j) {
			V(i, j, V.kmin) = V(i, j, V.kmax - 1);
			V(i, j, V.kmax) = V(i, j, V.kmin + 1);
		}
}

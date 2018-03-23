#include "em.h"
#include em.h

void em_HStep(mesh<vec3d_t> &E, mesh<vec3d_t> &H)
{
	static double c1 = DT/DX*MC_X,
				  c2 = DT/DY*MC_Y,
				  c3 = DT/DZ*MC_Z;
	for(unsigned i = H.imin; i <= H.imax; ++i)
		for(unsigned j = H.jmin; j <= H.jmax; ++j)
			for (unsigned k = H.kmin; k <= H.kmax; ++k) {
				H(i, j, k).x += c2*(E(i, j, k).z - E(i, j-1, k).z)
							  - c3*(E(i, j, k).y - E(i, j, k-1).y);
				H(i, j, k).y += c3 (E(i, j, k).x - E(i, j, k-1).x)
							  - c1*(E(i, j, k).z - E(i-1, j, k).z);
				H(i, j, k).z += c1*(E(i, j, k).y - E(i-1, j, k).y)
							  - c2*(E(i, j, k).x - E(i, j-1, k).x);
			}
}

void em_EStep(mesh<vec3d_t> &E, mesh<vec3d_t> &H)
{
	static double c1 = DT/DX,
				  c2 = DT/DY,
				  c3 = DT/DZ;
	for (unsigned i = H.imin; i <= H.imax; ++i)
		for (unsigned j = H.jmin; j <= H.jmax; ++j)
			for (unsigned k = H.kmin; k <= H.kmax; ++k) {
				E(i, j, k).x += c2(H(i, j, k).z - H(i, j+1, k).z)
							  - c3(H(i, j, k).y - H(i, j, k+1).y);
				E(i, j, k).y += c3(H(i, j, k).x - H(i, j, k+1).x)
							  - c1(H(i, j, k).z - H(i+1, j, k).z);
				E(i, j, k).z += c1(H(i, j, k).y - H(i+1, j, k).y)
							  - c2(H(i, j, k).x - H(i, j+1, k).x);
			}
}

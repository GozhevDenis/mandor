#include "em.h"
#include "testConstMacros.h"

void em_HStep(mesh_t<vec3d_t> &E, mesh_t<vec3d_t> &H)
{
	static double c1 = DT/DX*MC_X,
				  c2 = DT/DY*MC_Y,
				  c3 = DT/DZ*MC_Z;
	/*for(int i = H.imin; i <= H.imax; ++i)
		for(int j = H.jmin; j <= H.jmax; ++j)
			for (int k = H.kmin; k <= H.kmax; ++k) {
				H(i, j, k).v.x += c2*(E(i, j, k).v.z - E(i, j-1, k).v.z)
							  - c3*(E(i, j, k).v.y - E(i, j, k-1).v.y);
				H(i, j, k).v.y += c3*(E(i, j, k).v.x - E(i, j, k-1).v.x)
							  - c1*(E(i, j, k).v.z - E(i-1, j, k).v.z);
				H(i, j, k).v.z += c1*(E(i, j, k).v.y - E(i-1, j, k).v.y)
							  - c2*(E(i, j, k).v.x - E(i, j-1, k).v.x);
			}*/
}

void em_EStep(mesh_t<vec3d_t> &E, mesh_t<vec3d_t> &H)
{
	 static double c1 = DT/DX,
				   c2 = DT/DY,
				   c3 = DT/DZ;
	/*for (int i = H.imin; i <= H.imax; ++i)
		for (int j = H.jmin; j <= H.jmax; ++j)
			for (int k = H.kmin; k <= H.kmax; ++k) {
				E(i, j, k).v.x += c2*(H(i, j, k).v.z - H(i, j+1, k).v.z)
							  - c3*(H(i, j, k).v.y - H(i, j, k+1).v.y);
				E(i, j, k).v.y += c3*(H(i, j, k).v.x - H(i, j, k+1).v.x)
							  - c1*(H(i, j, k).v.z - H(i+1, j, k).v.z);
				E(i, j, k).v.z += c1*(H(i, j, k).v.y - H(i+1, j, k).v.y)
							  - c2*(H(i, j, k).v.x - H(i, j+1, k).v.x);
			}*/
}

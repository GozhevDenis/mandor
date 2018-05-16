#include "em.h"
#include "testConstMacros.h"

void em_HStep(mesh_t<vec3d_t> &E, mesh_t<vec3d_t> &H)
{
	static double //da = (1 - DT/2)/(1 + DT/2),
				  da = 1,
				  db = DT/DR;
	for (int i = H.imin + 1; i <= H.imax - 1; ++i)
    for (int j = H.jmin + 1; j <= H.jmax - 1; ++j)
    for (int k = H.kmin + 1; k <= H.kmax - 1; ++k) {
        H(i, j, k).v.x = da*H(i, j, k).v.x +
                         db*(E(i, j, k+1).v.y - E(i, j, k).v.y +
                             E(i, j, k).v.z - E(i, j+1, k).v.z);
        H(i, j, k).v.y = da*H(i, j, k).v.y +
                         db*(E(i+1, j, k).v.z - E(i, j, k).v.z +
                             E(i, j, k).v.x - E(i, j, k+1).v.x);
        H(i, j, k).v.z = da*H(i, j, k).v.z +
                         db*(E(i, j+1, k).v.x - E(i, j, k).v.x +
                             E(i, j, k).v.y - E(i+1, j, k).v.y);
    }
}

void em_EStep(mesh_t<vec3d_t> &E, mesh_t<vec3d_t> &H)
{
	 static double ca = (1 - DT/2)/(1 + DT/2),
				   cb = (DT/DR)/(1 + DT/2);
				   //cb2 = DT/DZ;
	for (int i = E.imin + 1; i <= E.imax - 1; ++i)
    for (int j = E.jmin + 1; j <= E.jmax - 1; ++j)
    for (int k = E.kmin + 1; k <= E.kmax - 1; ++k) {
        E(i, j, k).v.x = ca*E(i, j, k).v.x +
                         cb*(H(i, j, k).v.z - H(i, j-1, k).v.z +
                             H(i, j, k-1).v.y - H(i, j, k).v.y);
        E(i, j, k).v.y = ca*E(i, j, k).v.y +
                         cb*(H(i, j, k).v.x - H(i, j, k-1).v.x +
                             H(i-1, j, k).v.z - H(i, j, k).v.z);
        E(i, j, k).v.z = ca*E(i, j, k).v.z +
                         cb*(H(i, j, k).v.y - H(i-1, j, k).v.y +
                             H(i, j-1, k).v.x - H(i, j, k).v.x);
    }
}

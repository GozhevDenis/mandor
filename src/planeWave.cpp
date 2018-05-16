#include <cmath>

#include "planeWave.h"
#include "testConstMacros.h"

void EWaveStart(mesh_t<vec3d_t> &E)
{
	double A0 = 1,
		   lambda = 1;
	for (int i = E.imin + 1; i <= E.imax - 1; ++i)
    for (int j = E.jmin + 1; j <= E.jmax - 1; ++j)
    for (int k = E.kmin + 1; k <= E.kmax - 1; ++k) {
        E(i, j, k).v.y = A0*cos(2*PI*(i-3/2)*DX/lambda);
    }
}

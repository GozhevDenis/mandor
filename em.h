#pragma once
#include "type_vector.h"
#include "type_mesh.h"

void em_H(mesh<vec3d_t> &E, mesh<vec3d_t> &H);
void em_EStep(mesh<vec3d_t> &E, mesh<vec3d_t> &H);


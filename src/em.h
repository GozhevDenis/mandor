#pragma once
#include "type_vector.h"
#include "type_mesh.h"

void em_HStep(mesh_t<vec3d_t> &E, mesh_t<vec3d_t> &H);
void em_EStep(mesh_t<vec3d_t> &E, mesh_t<vec3d_t> &H);


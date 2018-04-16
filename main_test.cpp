#include "easylogging\easylogging++.h"
#include "type_vector.h"
#include "type_mesh.h"

#include <iostream>

INITIALIZE_EASYLOGGINGPP

int main()
{
	//mesh_t<vec3d_t> vec(0, 0, 0, 10, 10, 10, "name");
	mesh_t<double> vec(0, 0, 0, 10, 10, 10, "name");
	//std::cout << vec(5, 4, 3).v.x << std::endl;
	system("pause");
	return 0;
}
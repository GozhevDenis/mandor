  //file type_mesh.h
#pragma once
#include <iostream>
//#include <vector>

///#include <stdio.h>					//доделать
///#include <string.h>

///#include "misc_partition.h"

template <typename T>
class mesh_t
{
private:
	int imin, imax;
	int jmin, jmax;
	int kmin, kmax;
	int width_z;
	int width_yz;
	T *storage;
	int origin;
	std::string name;

	void init();										//width initialization and memory allocation
public:
	mesh_t();
	mesh_t(int, int, int, int, int, int, const char*);
	~mesh_t();

	explicit mesh_t(int [3], int[3], const char*);
	void free();										////нужен ли этот метод?
	void resize(int, int, int, int, int, int);
	///void save();
	///void load();

	template <typename U> friend std::ostream& operator << (std::ostream&, const mesh_t<U>&);

};

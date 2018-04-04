#pragma once
#include <iostream>
#include "type_mesh.h"
#include <fstream>
#include "testConstMacros.h"
#include "easylogging\easylogging++.h"



template<typename T>
mesh_t<T>::mesh_t(): imin(0), jmin(0), kmin(0),
					 imax(0), jmax(0), kmax(0),
					 name("new_mesh")
{
	(*this).init();
}

template <typename T> 
mesh_t<T>::mesh_t(int Imin, int Jmin, int Kmin,
			   	  int Imax, int Jmax, int Kmax,
			   	  const char * Name): 		    imin(Imin), jmin(Jmin), kmin(Kmin),
						  						imax(Imax), jmax(Jmax), kmax(Kmax),
												name(Name)
{
	(*this).init();
}

template<typename T>
mesh_t<T>::~mesh_t()
{
	delete[] storage;
}

template <typename T> 
mesh_t<T>::mesh_t(int min[3],
				  int max[3],
				  const char* Name): imin(min[0]), jmin(min[1]), kmin(min[2]),
								 	 imax(max[0]), jmax(max[1]), kmax(max[2]),
									 name(Name)
{
	(*this).init();
}

template <typename T> 
void mesh_t<T>::init()
{
	int sizeX, sizeY, sizeZ;

	imin *= MC_X;   //доделать оси
	imax *= MC_X;
	jmin *= MC_Y;
	jmax *= MC_Y;
	kmin *= MC_Z;
	kmax *= MC_Z;

	CHECK(imin <= imax && jmin <= jmax && kmin <= kmax) << "Bad arguments";

	sizeX = imax - imin + 1;
	sizeY = jmax - jmin + 1;
	sizeZ = kmax - kmin + 1;

	width_z = sizeZ;
	width_yz = sizeY*sizeZ;

	storage = new (std::nothrow) T[sizeX*sizeY*sizeZ];					
	
	CHECK(storage) << "Memory is not allocated";						//возможно появление ошибки std::bad_array_new_length при первом выделение, не знаю как исправить

	origin = -imin*MC_X*width_yz - jmin*MC_Y*width_z - kmin*MC_Z;				///MC
}

template<typename T>													//проверка нахождение области внутри mesh
bool mesh_t<T>::IsInside(int Imin, int Jmin, int Kmin, 
						 int Imax, int Jmax, int Kmax) const
{
	CHECK(Imin <= Imax && Jmin <= Jmax && Kmin <= Kmax);
	return ((Imin - imin)*(imax - Imax) >= 0 &&
			(Jmin - jmin)*(jmax - Jmax) >= 0 &&
			(Kmin - kmin)*(kmax - Kmax) >= 0);
}

template <typename T> 
void mesh_t<T>::free()									//нужен ли этот метод? Подумать может его сделать закрытым
{
	delete[] storage;
	storage = nullptr;
}

template <typename T> 
void mesh_t<T>::resize(int Imin, int Jmin, int Kmin,
			   		   int Imax, int Jmax, int Kmax)
{
	imin = Imin;
	jmin = Jmin;
	kmin = Kmin;
	imax = Imax;
	jmax = Jmax;
	kmax = Kmax;
	(*this).free();
	(*this).init();
}

template<typename T>
T& mesh_t<T>::operator()(int i, int j, int k)
{
	return storage[i*MC_X*width_yz + j*MC_Y*width_z + k*MC_Z + origin];
}

template<typename T>
const T& mesh_t<T>::operator()(int i, int j, int k) const
{
	return storage[i*MC_X*width_yz + j*MC_Y*width_z + k*MC_Z + origin];
}

template<typename T>
void mesh_t<T>::save(const char * name, 
					 int Imin, int Jmin, int Kmin, 
					 int Imax, int Jmax, int Kmax) const
{
	CHECK((*this).IsInside(imin, jmin, kmin,
						   imax, jmax, kmax)) << "Bad arguments for save region";
	Imin *= MC_X;
	Imax *= MC_X;
	Jmin *= MC_Y;
	Jmax *= MC_Y;
	Kmin *= MC_Z;
	Kmax *= MC_Z;

	ofstream f(name, ios::binary);
	f.write((char*)&Imin, sizeof(Imin));
	f.write((char*)&Jmin, sizeof(Jmin));
	f.write((char*)&Kmin, sizeof(Kmin));
	f.write((char*)&Imax, sizeof(Imax));
	f.write((char*)&Jmax, sizeof(Jmax));
	f.write((char*)&Kmax, sizeof(Kmax));
	f.write((char*)this, sizeof(*this));									//надо ли?

	int size = (Imax - Imin + 1)*(Jmax - Jmin + 1)*(Kmax - Kmin + 1);
	f.write((char*)storage, size*sizeof(T));								//почему не так, а через цикл?
	f.close();
}

template <typename T> 
std::ostream& operator << (std::ostream& os, const mesh_t<T>& mesh)
{
	os << "(" << mesh.imin << "," << mesh.jmin << "," << mesh.kmin << ")\n";
	os << "(" << mesh.imax << "," << mesh.jmax << "," << mesh.kmax << ")\n";
	os << "(" << mesh.width_z << "," << mesh.width_yz << ")" << "\n";
	os << mesh.origin << "\n";
	os << mesh.name << "\n";
	return os;
}
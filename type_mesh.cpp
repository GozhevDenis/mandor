#pragma once
#include <iostream>
#include "type_mesh.h"
#include "easylogging\easylogging++.h"

#define MC_X 1      //для теста
#define MC_Y 1
#define MC_Z 1


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
	return storage[i*MC_X*width_yz + j*MC_Y*width_z + k*MC_Z + origin];			//сделать assert для того чтобы индексы были внутри диапазона?
}

template<typename T>
const T& mesh_t<T>::operator()(int i, int j, int k) const
{
	return storage[i*MC_X*width_yz + j*MC_Y*width_z + k*MC_Z + origin];
}

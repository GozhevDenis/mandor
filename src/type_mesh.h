  //file type_mesh.h
#pragma once

#include <iostream>

#include "easylogging/easylogging++.h"

#include "type_mesh.h"
#include "testConstMacros.h"

template <typename T>
class mesh_t
{
private:
	int  width_z;
	int  width_yz;
	T*   storage;
	int  origin;
	std::string name;

	void init();										//width initialization and memory allocation
public:
	int imin, imax;
	int jmin, jmax;
	int kmin, kmax;

	mesh_t();
	mesh_t(int, int, int, int, int, int, const char*);
	~mesh_t();

	explicit mesh_t(int [3], int[3], const char*);
	void free();										////нужен ли этот метод?
	void resize(int, int, int, int, int, int);

	T& operator()(int i, int j, int k);
	const T& operator()(int i, int j, int k) const;

	template <typename U> friend std::ostream& operator << (std::ostream&, const mesh_t<U>&);
};

//то что было в cpp кроме библиотек(тут оставть iostream)

template<typename T>
mesh_t<T>::mesh_t() : imin(0), jmin(0), kmin(0),
imax(0), jmax(0), kmax(0),
name("new_mesh")
{
	(*this).init();
}

template <typename T>
mesh_t<T>::mesh_t(int Imin, int Jmin, int Kmin,
	int Imax, int Jmax, int Kmax,
	const char * Name) : imin(Imin), jmin(Jmin), kmin(Kmin),
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
	const char* Name) : imin(min[0]), jmin(min[1]), kmin(min[2]),
	imax(max[0]), jmax(max[1]), kmax(max[2]),
	name(Name)
{
	(*this).init();
}

template <typename T>
void mesh_t<T>::init()
{
	int sizeX, sizeY, sizeZ;

	imin *= MC_X;   // доделать оси
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
	width_yz = sizeY * sizeZ;

	storage = new (std::nothrow) T[sizeX*sizeY*sizeZ];

    // Возможно появление ошибки std::bad_array_new_length при первом выделение,
    // не знаю как исправить.
	CHECK(storage) << "Memory is not allocated";

	origin = -MC_X*imin*width_yz - MC_Y*jmin*width_z - kmin*MC_Z;
}

// Нужен ли этот метод? Подумать, может его сделать закрытым.
template <typename T>
void mesh_t<T>::free()
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

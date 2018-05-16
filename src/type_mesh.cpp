#pragma once

#include "easylogging/easylogging++.cc"

#include "type_mesh.h"

#define MC_X 1      //для теста
#define MC_Y 1
#define MC_Z 1


template<typename T>
mesh_t<T>::mesh_t( int Imin, int Jmin, int Kmin,
                   int Imax, int Jmax, int Kmax,
                   const char * Name )
:  imin( Imin ), jmin( Jmin ), kmin( Kmin ),
   imax( Imax ), jmax( Jmax ), kmax( Kmax ),
   name( Name )
{
   ( *this ).init();
}

template<typename T>
mesh_t<T>::mesh_t( int min[3],
                   int max[3],
                   const char * Name )
:  imin( min[0] ), jmin( min[1] ), kmin( min[2] ),
   imax( max[0] ), jmax( max[1] ), kmax( max[2] ),
   name( Name )
{
   ( *this ).init();
}

template<typename T>
void mesh_t<T>::init()
{
   int sizeX, sizeY, sizeZ;

   // доделать оси
   imin *= MC_X;
   imax *= MC_X;
   jmin *= MC_Y;
   jmax *= MC_Y;
   kmin *= MC_Z;
   kmax *= MC_Z;

   CHECK( imin <= imax && jmin <= jmax && kmin <= kmax ) << "Bad arguments";
   //CHECK(true) << "Invalid index";

   sizeX = imax - imin + 1;
   sizeY = jmax - jmin + 1;
   sizeZ = kmax - kmin + 1;

   width_z  = sizeZ;
   width_yz = sizeY * sizeZ;

   // обработать исключение, чтобы было понятно где конкретно вылетела ошибка?
   storage.reserve( sizeX * sizeY * sizeZ );

   origin = -imin * MC_X * width_yz - jmin * MC_Y * width_z - kmin * MC_Z;
}

// нужен ли этот метод?
template<typename T>
void mesh_t<T>::free()
{
   std::vector<T>().swap( storage );
}

template<typename T>
void mesh_t<T>::resize( int Imin, int Jmin, int Kmin,
                        int Imax, int Jmax, int Kmax )
{
   imin = Imin;
   jmin = Jmin;
   kmin = Kmin;
   imax = Imax;
   jmax = Jmax;
   kmax = Kmax;
   std::vector<T>().swap( storage );
   this->init();
}

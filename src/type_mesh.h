//file type_mesh.h
#pragma once

#include <iostream>

#include "easylogging/easylogging++.h"
#include "H5Cpp.h"

#include "type_mesh.h"
#include "testConstMacros.h"

#include "log.h"

template<typename T>
class mesh_t {
private:
   int         widthZ;
   int         widthYZ;
   T *         storage;
   int         origin;
   std::string name;


public:
   int         imin, imax;
   int         jmin, jmax;
   int         kmin, kmax;

   mesh_t();

   mesh_t( int, int, int, int, int, int, const char * );

   ~mesh_t();

   explicit mesh_t( const int min[3], const int max[3], const char * name);

   void free();                              ////нужен ли этот метод?
   void resize( int, int, int, int, int, int );

   T& operator()( int i, int j, int k );

   const T& operator()( int i, int j, int k ) const;

   void save( const std::string& fileName, int step );

   template<typename U>
   friend std::ostream& operator<<( std::ostream&, const mesh_t<U>& );
};

// TODO: do delegating constructors [https://www.ibm.com/developerworks/community/blogs/5894415f-be62-4bc0-81c5-3956e82276f3/entry/introduction_to_the_c_11_feature_delegating_constructors?lang=en].
template<typename T>
mesh_t<T>::mesh_t( int Imin, int Jmin, int Kmin,
                   int Imax, int Jmax, int Kmax,
                   const char * Name )
:  imin( Imin ), jmin( Jmin ), kmin( Kmin ),
   imax( Imax ), jmax( Jmax ), kmax( Kmax ),
   name( Name )
{
    int sizeX, sizeY, sizeZ;

    // доделать оси
    // expansion of the indexes boundaries for the ghost cells and folding inactive axes
    // warning! DO NOT FORGOT THAT REAL SIZE IS LESS
    imin = ( imin - 1 ) * MC_X;
    imax = ( imax + 1 ) * MC_X;
    jmin = ( jmin - 1 ) * MC_Y;
    jmax = ( jmax + 1 ) * MC_Y;
    kmin = ( kmin - 1 ) * MC_Z;
    kmax = ( kmax + 1 ) * MC_Z;

    CHECK( imin <= imax && jmin <= jmax && kmin <= kmax ) << "Bad arguments";

    sizeX = imax - imin + 1;
    sizeY = jmax - jmin + 1;
    sizeZ = kmax - kmin + 1;

    widthZ  = sizeZ;
    widthYZ = sizeY * sizeZ;

    // TODO: handle memory allocation error as the error!
    storage = new( std::nothrow ) T[sizeX * sizeY * sizeZ];

    // Возможно появление ошибки std::bad_array_new_length при первом выделение,
    // не знаю как исправить.
    CHECK( storage ) << "Memory is not allocated";

    origin = -MC_X * imin * widthYZ - MC_Y * jmin * widthZ - kmin * MC_Z;
}


template<typename T>
mesh_t<T>::mesh_t()
:  mesh_t( 0, 0, 0,
           0, 0, 0,
         "new_mesh" ) {}

template<typename T>
mesh_t<T>::mesh_t( const int min[3],
                   const int max[3],
                   const char * Name )
:  mesh_t( min[0], min[1], min[2],
           max[0], max[1], max[2],
           Name ) {}

template<typename T>
mesh_t<T>::~mesh_t()
{
   free();
}

// Нужен ли этот метод? Подумать, может его сделать закрытым.
template<typename T>
void mesh_t<T>::free()
{
   delete[] storage;
   storage = nullptr;
}

template<typename T>
void mesh_t<T>::resize( int Imin, int Jmin, int Kmin,
                        int Imax, int Jmax, int Kmax )
{
   this->imin = Imin;
   this->jmin = Jmin;
   this->kmin = Kmin;
   this->imax = Imax;
   this->jmax = Jmax;
   this->kmax = Kmax;
   this->free();
   this->init();
}

template<typename T>
T& mesh_t<T>::operator()( int i, int j, int k )
{
   // сделать assert для того чтобы индексы были внутри диапазона?
   return storage[i * MC_X * widthYZ + j * MC_Y * widthZ + k * MC_Z + origin];
}

template<typename T>
const T& mesh_t<T>::operator()( int i, int j, int k ) const
{
   return storage[i * MC_X * widthYZ + j * MC_Y * widthZ + k * MC_Z + origin];
}

template<typename T>
void mesh_t<T>::save( const std::string& fileName, int step )
{
   int sizeX, sizeY, sizeZ;
   int RANK = 4;

   // доделать оси
   imin *= MC_X;
   imax *= MC_X;
   jmin *= MC_Y;
   jmax *= MC_Y;
   kmin *= MC_Z;
   kmax *= MC_Z;

   CHECK( imin <= imax && jmin <= jmax && kmin <= kmax ) << "Bad arguments";

   sizeX = imax - imin + 1;
   sizeY = jmax - jmin + 1;
   sizeZ = kmax - kmin + 1;

   H5::H5File f( fileName + string_format( "_%06d", step ) + ".h5", H5F_ACC_TRUNC );
   hsize_t dimsf[4];
   dimsf[0] = sizeX;
   dimsf[1] = sizeY;
   dimsf[2] = sizeZ;
   dimsf[3] = 3;
   H5::DataSpace dataspace( RANK, dimsf );

   H5::DataSet dataset = f.createDataSet( name, H5::PredType::NATIVE_DOUBLE, dataspace );
   dataset.write(storage, H5::PredType::NATIVE_DOUBLE);

    //stub for attributes
    double dx = DX,
           dy = DY,
           dz = DZ,
           t =  DT * step;
    H5::Attribute attDx =   dataset.createAttribute( "dx",   H5::PredType::NATIVE_DOUBLE, H5::DataSpace() );
    H5::Attribute attDy =   dataset.createAttribute( "dy",   H5::PredType::NATIVE_DOUBLE, H5::DataSpace() );
    H5::Attribute attDz =   dataset.createAttribute( "dz",   H5::PredType::NATIVE_DOUBLE, H5::DataSpace() );
    H5::Attribute attDNx =  dataset.createAttribute( "Nx",   H5::PredType::NATIVE_DOUBLE, H5::DataSpace() );
    H5::Attribute attDNy =  dataset.createAttribute( "Ny",   H5::PredType::NATIVE_DOUBLE, H5::DataSpace() );
    H5::Attribute attDNz =  dataset.createAttribute( "Nz",   H5::PredType::NATIVE_DOUBLE, H5::DataSpace() );
    H5::Attribute attTime = dataset.createAttribute( "time", H5::PredType::NATIVE_DOUBLE, H5::DataSpace() );
    attDx.write(   H5::PredType::NATIVE_INT, &dx    );
    attDy.write(   H5::PredType::NATIVE_INT, &dy    );
    attDz.write(   H5::PredType::NATIVE_INT, &dz    );
    attDNx.write(  H5::PredType::NATIVE_INT, &sizeX );
    attDNy.write(  H5::PredType::NATIVE_INT, &sizeY );
    attDNz.write(  H5::PredType::NATIVE_INT, &sizeZ );
    attTime.write( H5::PredType::NATIVE_INT, &t     );



}

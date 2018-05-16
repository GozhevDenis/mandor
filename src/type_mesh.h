//file type_mesh.h
#pragma once

#include <iostream>
#include <vector>

template<typename T>
class mesh_t {
private:
   int            width_z;
   int            width_yz;
   std::vector<T> storage;
   int            origin;
   std::string    name;

   // width initialization and and memory allocation
   void init();

public:
   int imin, imax;
   int jmin, jmax;
   int kmin, kmax;

   mesh_t();

   mesh_t( int, int, int, int, int, int, const char * );

   explicit mesh_t( int [3], int[3], const char * );

   void free();                              ////нужен ли этот метод?
   void resize( int, int, int, int, int, int );

   template<typename U>
   friend std::ostream& operator<<( std::ostream&, const mesh_t<U>& );
};

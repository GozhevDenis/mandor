#include "type_vector.h"

vec3d_t::vec3d_t()                               : r{ 0, 0, 0 }            {}
vec3d_t::vec3d_t( double X, double Y, double Z ) : r{ X, Y, Z }            {}
vec3d_t::vec3d_t( double R[3] )                  : r{ R[0], R[1], R[2] }   {}


vec3d_t& vec3d_t::operator()( double X, double Y, double Z )
{
   this->v.x = X;
   this->v.y = Y;
   this->v.z = Z;
   return *this;
}

vec3d_t& vec3d_t::operator+=( const vec3d_t& rhs )
{
   this->v.x += rhs.v.x;
   this->v.y += rhs.v.y;
   this->v.z += rhs.v.z;
   return *this;
}

vec3d_t& vec3d_t::operator-=( const vec3d_t& rhs )
{
   this->v.x -= rhs.v.x;
   this->v.y -= rhs.v.y;
   this->v.z -= rhs.v.z;
   return *this;
}

const vec3d_t vec3d_t::operator+( const vec3d_t& rhs ) const
{
   return vec3d_t( *this ) += rhs;
}

const vec3d_t vec3d_t::operator-( const vec3d_t& rhs ) const
{
   return vec3d_t( *this ) -= rhs;
}

vec3d_t& vec3d_t::operator*=( const double& rhs )
{
   this->v.x *= rhs;
   this->v.y *= rhs;
   this->v.z *= rhs;
   return *this;
}

const double vec3d_t::dot( const vec3d_t& rhs ) const
{
   return this->v.x * rhs.v.x + this->v.y * rhs.v.y + this->v.z * rhs.v.z;
}

const vec3d_t vec3d_t::cross( const vec3d_t& rhs ) const
{
   return vec3d_t( this->v.y * rhs.v.z - this->v.z * rhs.v.y,
                   this->v.z * rhs.v.x - this->v.x * rhs.v.z,
                   this->v.x * rhs.v.y - this->v.y * rhs.v.x );
}

const vec3d_t operator*( const double& lhs, const vec3d_t& rhs )
{
   return vec3d_t{ rhs } *= lhs;
}

const vec3d_t operator*( const vec3d_t& lhs, const double& rhs )
{
   return vec3d_t{ lhs } *= rhs;
}

std::ostream& operator<<( std::ostream& os, const vec3d_t& vec )
{
   os << '(' << vec.v.x << ' ' << vec.v.y << ' ' << vec.v.z << ')' << std::endl;
   return os;
}

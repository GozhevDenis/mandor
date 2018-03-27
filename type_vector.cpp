#include "type_vector.h"
#include <cassert>

vec3d_t::vec3d_t(): x(0), y(0), z(0) {}

vec3d_t::vec3d_t(double X, double Y, double Z) : x(X), y(Y), z(Z) {}


vec3d_t::vec3d_t(const double R[3]) : x(R[0]), y(R[1]), z(R[2]) {}

/*vec3d_t::~vec3d_t()
{
}*/

const double& vec3d_t::operator[](size_type axis) const
{
	assert(axis*(2 - axis) >= 0 && "bad index");				//не работает??
	return this->*r[axis];
}

double& vec3d_t::operator[](size_type axis)
{
	assert(axis*(2 - axis) >= 0 && "bad index");
	return this->*r[axis];
}

vec3d_t& vec3d_t::operator()(double X, double Y, double Z)
{
	this->x = X;
	this->y = Y;
	this->z = Z;
	return *this;
}

vec3d_t& vec3d_t::operator+=(const vec3d_t& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	return *this;
}

vec3d_t& vec3d_t::operator-=(const vec3d_t& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	return *this;
}

const vec3d_t vec3d_t::operator+(const vec3d_t& rhs) const
{
	return vec3d_t(*this) += rhs;
}

const vec3d_t vec3d_t::operator-(const vec3d_t& rhs) const
{
	return vec3d_t(*this) -= rhs;
}

vec3d_t& vec3d_t::operator*=(const double& rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	this->z *= rhs;
	return *this;
}
const vec3d_t operator*(const double& lhs, const vec3d_t& rhs)
{
	return vec3d_t(rhs) *= lhs;
}

const vec3d_t operator*(const vec3d_t& lhs, const double& rhs)
{
	return vec3d_t(lhs) *= rhs;
}

std::ostream & operator<<(std::ostream& os, const vec3d_t& vec)
{
	os << "(" << vec.x << "," << vec.y << "," << vec.z << ")" << std::endl;
	return os;
}

const double vec3d_t::dot(const vec3d_t& rhs) const
{
	return this->x*rhs.x + this->y*rhs.y + this->z*rhs.z;
}

const vec3d_t vec3d_t::cross(const vec3d_t& rhs) const
{
	return vec3d_t(this->y*rhs.z - this->z*rhs.y,
				   this->z*rhs.x - this->x*rhs.z,
				   this->x*rhs.y - this->y*rhs.x);
}

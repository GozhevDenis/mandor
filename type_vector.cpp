#pragma once
#include "type_vector.h"
#include "easylogging\easylogging++.cc"

vec3d_t::vec3d_t(): x(0), y(0), z(0) {}

vec3d_t::vec3d_t(const double X, const double Y, const double Z): x(X), y(Y), z(Z) {}

vec3d_t::vec3d_t(const double r[3]): x(r[0]), y(r[1]), z(r[2]) {}

vec3d_t& vec3d_t::operator () (double X, double Y, double Z)
{
    this->x = X;
    this->y = Y;
    this->z = Z;
    return *this;
}

vec3d_t& vec3d_t::operator += (const vec3d_t& rhs)
{
	this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
}

vec3d_t& vec3d_t::operator -= (const vec3d_t& rhs)
{
	this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    return *this;
}

const vec3d_t vec3d_t::operator + (const vec3d_t& rhs) const
{
	return vec3d_t(*this) += rhs;
}

const vec3d_t vec3d_t::operator - (const vec3d_t& rhs) const
{
	return vec3d_t(*this) -= rhs;
}

const double vec3d_t::operator * (const vec3d_t& rhs) const
{
    return this->x*rhs.x + this->y*rhs.y + this->z*rhs.z;
}

vec3d_t& vec3d_t::operator *= (const double& rhs)
{
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    return *this;
}

const double& vec3d_t::operator [] (int axis) const
{
    CHECK(axis >= 0 && axis < 3) << "Invalid index";
    switch (axis)
    {
    case X_axis:
        {
            return x;
            break;
        }
    case Y_axis:
        {
            return y;
            break;
        }
    case Z_axis:
        {
            return z;
            break;
        }
    default:
        {
            ///сообщение об ошибке
            ///остановить с ошибкой!!!
            //CHECK(false) << "Invalid index"; наверно уже не надо
        }
    }
}
double& vec3d_t::operator [] (int axis)
{
    return const_cast<double&>(static_cast<const vec3d_t&> (*this)[axis]);
}

const double vec3d_t::getX() const
{
	return (*this)[0];
}

const double vec3d_t::getY() const
{
	return (*this)[1];
}

const double vec3d_t::getZ() const
{
	return (*this)[2];
}

void vec3d_t::setX(double X)
{
	(*this)[0] = X;
}

void vec3d_t::setY(double Y)
{
	(*this)[1] = Y;
}

void vec3d_t::setZ(double Z)
{
	(*this)[2] = Z;
}

const vec3d_t vec3d_t::operator ^ (const vec3d_t& rhs) const
{
    return vec3d_t(this->y * rhs.z - this->z * rhs.y,
                   this->z * rhs.x - this->x * rhs.z,
                   this->x * rhs.y - this->y * rhs.x);
}


bool vec3d_t::operator == (const vec3d_t& rhs) const
{
	return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z);
}

bool vec3d_t::operator != (const vec3d_t& rhs) const
{
	return !(*this == rhs);
}


const vec3d_t operator * (const vec3d_t& lhs, const double& rhs)
{
    return vec3d_t(lhs) *= rhs;
}
const vec3d_t operator * (const double& lhs, const vec3d_t& rhs)
{
    return vec3d_t(rhs) *= lhs;
}

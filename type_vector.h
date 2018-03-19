#pragma once
#include <iostream> 

struct vec3d_t
{
public:
	union {
		struct { double x, y, z } v;
		double r[3];
	};

	vec3d_t();
	vec3d_t(double X, double Y, double Z);
	//~vec3d_t();

	vec3d_t& operator()(double X, double Y, double Z);				//нужна ли? напрямую работает быстрее?
	vec3d_t& operator+=(const vec3d_t& rhs);
	vec3d_t& operator-=(const vec3d_t& rhs);
	const vec3d_t operator+(const vec3d_t& rhs) const;
	const vec3d_t operator-(const vec3d_t& rhs) const;
	vec3d_t& operator*=(const double& rhs);										//return a*scale
	friend const vec3d_t operator*(const double& lhs, const vec3d_t& rhs);
	friend const vec3d_t operator*(const vec3d_t& lhs, const double& rhs);

	const double dot(const vec3d_t& rhs) const;
	const vec3d_t cross(const vec3d_t& rhs) const;

	friend std::ostream& operator<<(std::ostream& os, const vec3d_t& vec);
};


#pragma once
#include <iostream> 

class vec3d_t
{
private:
	typedef double vec3d_t::* const vec[3];
	static const vec r;
public:
	typedef size_t size_type;
	double x, y, z;
	
	vec3d_t();
	explicit vec3d_t(double X, double Y, double Z);
	explicit vec3d_t(const double r[3]);
	///explicit vec3d_t(const vec3d_t&); доделать!
	~vec3d_t();

	const double& operator[](size_type axis) const;
	double& operator[](size_type axis);

	vec3d_t& operator()(double X, double Y, double Z);

	///vec3d_t& operator=(const vec3d_t&); доделать!!

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

const vec3d_t::vec vec3d_t::r = { &vec3d_t::x, &vec3d_t::y, &vec3d_t::z };

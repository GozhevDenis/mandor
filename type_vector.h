///text

///#ifndef MF_VEC_DOT

/// Dot product: \f$ (\vec a, \vec b) = a_x\cdot b_x + a_y\cdot b_y + a_z\cdot b_z \f$.
///#define MF_VEC_DOT(a, b)		((a)[0]*(b)[0] + (a)[1]*(b)[1] + (a)[2]*(b)[2])

/// Cross product: \f$ \vec r = [\vec a, \vec b] \f$.
///#define MF_VEC_CROSS(res, a, b)		((res)[0] = (a)[1]*(b)[2] - (a)[2]*(b)[1], (res)[1] = (a)[2]*(b)[0] - (a)[0]*(b)[2], (res)[2] = (a)[0]*(b)[1] - (a)[1]*(b)[0])

/// Vector subtraction: \f$ \vec r = \vec a - \vec b \f$.
///#define MF_VEC_SUB(res, a, b)		((res)[0] = (a)[0] - (b)[0], (res)[1] = (a)[1] - (b)[1], (res)[2] = (a)[2] - (b)[2])

/// Vector addition: \f$ \vec r = \vec a + \vec b \f$.
///#define MF_VEC_ADD(res, a, b)		((res)[0] = (a)[0] + (b)[0], (res)[1] = (a)[1] + (b)[1], (res)[2] = (a)[2] + (b)[2])

/// Vector assignment (copy): \f$ \vec r = \vec a \f$.
///#define MF_VEC_COPY(res, a)		((res)[0] = (a)[0], (res)[1] = (a)[1], (res)[2] = (a)[2])

/// Vector clearing: \f$ \vec r = 0 \f$.
///#define MF_VEC_CLEAR(res)		((res)[0] = (res)[1] = (res)[2] = 0)

/// Vector negation: \f$ \vec r = - \vec a \f$.
//#define MF_VEC_NEG(res, a)		((res)[0] = - (a)[0], (res)[1] = - (a)[1], (res)[2] = - (a)[2])

/// Vector scaling: \f$ \vec r = \vec a * factor \f$.
///#define MF_VEC_SCALE(res, factores, a)	((res)[0] = (a)[0]*(factores), (res)[1] = (a)[1]*(factores), (res)[2] = (a)[2]*(factores))

/// Vector packing: \f$ \vec r = (x, y, z) \f$.
///#define MF_VEC_PACK(res, x, y, z)	((res)[0] = (x), (res)[1] = (y), (res)[2] = (z))

/// Vector unpacking: \f$ \vec r = (x, y, z) \f$.
///#define MF_VEC_UNPACK(resX, resY, resZ, a)	((resX) = (a)[0], (resY) = (a)[1], (resZ) = (a)[2])

/// Checks if all components are the same: \f$ \vec a == \vec b \f$.
///#define MF_VEC_EQ(a, b)			((a)[0] == (b)[0] && (a)[1] == (b)[1] && (a)[2] == (b)[2])

#pragma once

class vec3d_t
{
	private:
		double x;
		double y;
		double z;
	public:
		vec3d_t();
		vec3d_t(const double X, const double Y, const double Z);
		vec3d_t(const double r[3]);

		vec3d_t& operator () (double, double, double);					//change vec3d_t

		vec3d_t& operator += (const vec3d_t&);
		vec3d_t& operator -= (const vec3d_t&);
		const vec3d_t operator + (const vec3d_t&) const;				//return const vec.. or vec...
		const vec3d_t operator - (const vec3d_t&) const;				// const vec не даёт (a+b)=c, но создаёт новый объект, дорого обходится копирование
		const double operator * (const vec3d_t&) const;					// Returns dot product '(a, b) = a_x*b_x + a_y*b_y + a_z*b_z'.
		vec3d_t& operator *= (const double& rhs);						// Returns 'a*scale'		
		friend const vec3d_t operator * (const double&, const vec3d_t&);
        friend const vec3d_t operator * (const vec3d_t&, const double&);
        const vec3d_t operator ^ (const vec3d_t&) const;        	// Returns cross product '[a, b]', i.e. 'a×b'.


        const double& operator [] (int axis) const;						//returns &value by index
        double& operator [] (int axis);

        const double getX() const;
        const double getY() const;
        const double getZ() const;
        void setX(double);
        void setY(double);
        void setZ(double);

		bool operator == (const vec3d_t&) const;
		bool operator != (const vec3d_t&) const;

		void show() const;
};


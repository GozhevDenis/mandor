#include <cassert>

class vec3d_t
{
	private:
		double r[3];
	public:
		vec3d_t(): r{0,0,0} {};
		explicit vec3d_t(const double x, const double y, const double z): r{x,y,z} {};
		explicit vec3d_t(const double R[3]): r{R[0],R[1],R[2]} {};

        const double& operator [] (int axis) const
        {
        	assert(axis*(2 - axis) >= 0 && "bad index");
        	return r[axis];
        }
        double& operator [] (int axis)
        {
        	return const_cast<double&>(static_cast<const vec3d_t&> (*this)[axis]);
        }

        const double& x() const
        {
        	return r[0];
        }

        const double& y() const
        {
        	return r[1];
        }

        const double& z() const
        {
        	return r[2];
        }

        double& x()
        {
        	return const_cast<double&>(static_cast<const vec3d_t&> (*this).x());
        }

        double& y()
        {
        	return const_cast<double&>(static_cast<const vec3d_t&> (*this).y());
        }

        double& z()
        {
        	return const_cast<double&>(static_cast<const vec3d_t&> (*this).z());
        }

		void show() const;
};

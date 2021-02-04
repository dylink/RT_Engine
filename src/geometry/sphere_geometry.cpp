#include "sphere_geometry.hpp"

namespace RT_ISICG
{
	bool SphereGeometry::intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const
	{
		/// TODO !
		Vec3f oc = p_ray.getOrigin() - _center;
		float a	 = glm::dot( p_ray.getDirection(), p_ray.getDirection() );
		float b	 = 2 * dot( oc, p_ray.getDirection() );
		float c	 = dot( oc, oc ) - (_radius * _radius);

		float D = (b * b) - (4 * a * c);
		p_t1= (-b - sqrt( D )) / 2 * a;
		p_t2 = (-b + sqrt( D )) / 2 * a;

		return D >= 0;
	}

} // namespace RT_ISICG

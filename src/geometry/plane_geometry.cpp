#include "plane_geometry.hpp"

namespace RT_ISICG
{
	bool PlaneGeometry::intersect( const Ray & p_ray, float & p_t) const
	{
		/// TODO !
		float d = dot( _normal, p_ray.getDirection() );
		p_t		= dot( ( _point - p_ray.getOrigin() ), _normal ) / dot( p_ray.getDirection(), _normal );
		if (d < 0) return true;

		return false;
	}

} // namespace RT_ISICG

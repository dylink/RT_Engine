#include "plane_geometry.hpp"

namespace RT_ISICG
{
	bool PlaneGeometry::intersect( const Ray & p_ray, float & p_t) const
	{

		float		_d	= -dot( _point, _normal );
		const float den = glm::dot( p_ray.getDirection(), _normal );
		if ( den == 0.f ) return false;

		p_t = -( glm::dot( p_ray.getOrigin(), _normal ) + _d ) / den;

		return true;
		/// TODO !
	}

} // namespace RT_ISICG

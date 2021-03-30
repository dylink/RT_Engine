#include "aabb.hpp"

namespace RT_ISICG
{
	void AABB::extend( const Vec3f & p_v )
	{
		/// TODO
		/*_min.x = _min.x > p_v.x ? p_v.x : _min.x;
		_min.y = _min.y > p_v.y ? p_v.y : _min.y;
		_min.z = _min.z > p_v.z ? p_v.z : _min.z;

		_max.x = _max.x < p_v.x ? p_v.x : _max.x;
		_max.y = _max.y < p_v.y ? p_v.y : _max.y;
		_max.z = _max.z < p_v.z ? p_v.z : _max.z;*/
	}

	void AABB::extend( const AABB & p_aabb )
	{
		/// TODO
	}

	bool AABB::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		/// TODO
		return false;
	}
} // namespace RT_ISICG

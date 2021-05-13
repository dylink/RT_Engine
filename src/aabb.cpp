#include "aabb.hpp"

namespace RT_ISICG
{
	void AABB::extend( const Vec3f & p_v )
	{
		/// TODO
		
		_min.x = _min.x > p_v.x ? p_v.x : _min.x;
		_min.y = _min.y > p_v.y ? p_v.y : _min.y;
		_min.z = _min.z > p_v.z ? p_v.z : _min.z;

		_max.x = _max.x < p_v.x ? p_v.x : _max.x;
		_max.y = _max.y < p_v.y ? p_v.y : _max.y;
		_max.z = _max.z < p_v.z ? p_v.z : _max.z;
	}

	void AABB::extend( const AABB & p_aabb )
	{
		/// TODO
	}

	bool AABB::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		float xMin, xMax, yMin, yMax, zMin, zMax;
		xMin = ( _min.x - p_ray.getOrigin().x ) / p_ray.getDirection().x;
		xMax = ( _max.x - p_ray.getOrigin().x ) / p_ray.getDirection().x;

		if (xMin > xMax) { 
			float temp = xMin;
			xMin	   = xMax;
			xMax       = temp;
		}

		yMin = ( _min.y - p_ray.getOrigin().y ) / p_ray.getDirection().y;
		yMax = ( _max.y - p_ray.getOrigin().y ) / p_ray.getDirection().y;

		if (yMin > yMax) { 
			float temp = yMin;
			yMin	   = yMax;
			yMax	   = temp;
		}

		if ( ( xMin > yMax ) || ( yMin > xMax ) ) return false;

		if ( yMin > xMin ) xMin = yMin;

		if ( yMax < xMax ) xMax = yMax;

		zMin = ( _min.z - p_ray.getOrigin().z ) / p_ray.getDirection().z;
		zMax = ( _max.z - p_ray.getOrigin().z ) / p_ray.getDirection().z;

		if (zMin > zMax) { 
			float temp = zMin;
			zMin	   = zMax;
			zMax	   = temp;
		}

		if ( ( xMin > zMax ) || ( zMin > xMax ) ) return false;

		if ( zMin > xMin ) xMin = zMin;

		if ( zMax < xMax ) xMax = zMax;

		/// TODO
		return true;
	}
} // namespace RT_ISICG

#include "hexaedra_geometry.hpp"

namespace RT_ISICG
{
	bool HexaedraGeometry::intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const
	{

		float xMin, xMax, yMin, yMax, zMin, zMax;
		xMin = ( _min.x - p_ray.getOrigin().x ) / p_ray.getDirection().x;
		xMax = ( _max.x - p_ray.getOrigin().x ) / p_ray.getDirection().x;

		if ( xMin > xMax )
		{
			float temp = xMin;
			xMin	   = xMax;
			xMax	   = temp;
		}

		yMin = ( _min.y - p_ray.getOrigin().y ) / p_ray.getDirection().y;
		yMax = ( _max.y - p_ray.getOrigin().y ) / p_ray.getDirection().y;

		if ( yMin > yMax )
		{
			float temp = yMin;
			yMin	   = yMax;
			yMax	   = temp;
		}

		if ( ( xMin > yMax ) || ( yMin > xMax ) ) return false;

		if ( yMin > xMin ) xMin = yMin;

		if ( yMax < xMax ) xMax = yMax;

		zMin = ( _min.z - p_ray.getOrigin().z ) / p_ray.getDirection().z;
		zMax = ( _max.z - p_ray.getOrigin().z ) / p_ray.getDirection().z;

		if ( zMin > zMax )
		{
			float temp = zMin;
			zMin	   = zMax;
			zMax	   = temp;
		}

		if ( ( xMin > zMax ) || ( zMin > xMax ) ) return false;

		if ( zMin > xMin ) xMin = zMin;

		if ( zMax < xMax ) xMax = zMax;

		p_t1 = xMin;
		p_t2 = xMax;
		/// TODO
		return true;
	}

} // namespace RT_ISICG

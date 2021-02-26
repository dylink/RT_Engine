#ifndef __RT_ISICG_POINT_LIGHT__
#define __RT_ISICG_POINT_LIGHT__

#include "base_light.hpp"
#include "light_sample.hpp"
#include "../defines.hpp"

namespace RT_ISICG
{
	class PointLight : public BaseLight
	{
	  public:
		PointLight( const Vec3f p_color, const float p_power, const Vec3f & p_position ) : BaseLight(p_color, p_power),  _position( p_position ) {}
		virtual ~PointLight() = default;

		

		inline const Vec3f & getPosition() const { return _position; }

		virtual LightSample sample( const Vec3f & p_point ) const override
		{ 
			
			
			float distance = glm::distance( p_point, _position );
			Vec3f radiance	= _color * _power * ( 1 / (distance*distance));
			Vec3f direction = normalize( _position - p_point );
			return LightSample( direction, distance, radiance, 1.f );
		}

	  private:
		Vec3f _position = VEC3F_ZERO;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_PLANE_GEOMETRY__

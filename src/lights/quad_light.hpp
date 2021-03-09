#ifndef __RT_ISICG_QUAD_LIGHT__
#define __RT_ISICG_QUAD_LIGHT__

#include "../defines.hpp"
#include "utils/random.hpp"
#include "base_light.hpp"
#include "light_sample.hpp"

namespace RT_ISICG
{
	class QuadLight : public BaseLight
	{
	  public:
		QuadLight( const Vec3f p_color, const float p_power, const Vec3f & p_position, const Vec3f & p_u, const Vec3f & p_v )
			: BaseLight( p_color, p_power ), _position( p_position ), _u( p_u ), _v(p_v)
		{
			_area = glm::length( _u ) * glm::length( _v );
			_normal = normalize(cross( _u, _v ));
			_isSurface = true;
		}
		virtual ~QuadLight() = default;

		inline const Vec3f & getPosition() const { return _position; }

		virtual LightSample sample( const Vec3f & p_point ) const override
		{
			Vec3f randomPos = _position + (_u*randomFloat()) + (_v*randomFloat());
			
			float distance	= glm::distance( p_point, randomPos );
			Vec3f direction = normalize( randomPos - p_point );
			float pdf		= (1 / _area) * ( distance * distance ) * glm::dot(direction, _normal ); 
			Vec3f radiance	= _color * _power / pdf;
			
			return LightSample( direction, distance, radiance, pdf );
		}

		

	  private:
		Vec3f _position = VEC3F_ZERO;
		Vec3f _u		= VEC3F_ZERO;
		Vec3f _v		= VEC3F_ZERO;
		Vec3f _normal	= VEC3F_ZERO;
		float _area		= 0.f;
		
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_QUAD_LIGHT__

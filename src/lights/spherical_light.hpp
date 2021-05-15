#ifndef __RT_ISICG_SPHERICAL_LIGHT__
#define __RT_ISICG_SPHERICAL_LIGHT__

#include "../defines.hpp"
#include "base_light.hpp"
#include "light_sample.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	class SphericalLight : public BaseLight
	{
	  public:
		SphericalLight( const Vec3f p_color, const float p_power, const Vec3f & p_position )
			: BaseLight( p_color, p_power ), _position( p_position )
		{
			_isSurface = true;
		}
		virtual ~SphericalLight() = default;

		inline const Vec3f & getPosition() const { return _position; }

		virtual LightSample sample( const Vec3f & p_point ) const override
		{

			float theta = randomFloat() * 2 * PIf;

			float x = (randomFloat()*2.f) - 1.f;

			float s = sqrt( 1.f - x * x );
			
			Vec3f randomPos( _position.x + x, _position.y + s * cos( theta ), _position.z + s * sin( theta ) );

			

			Vec3f dir	   = randomPos - p_point;
			dir			   = glm::normalize( dir );
			float distance = glm::distance( p_point, randomPos );
			Vec3f radiance = _color * _power * ( 1 / ( distance * distance ) );
			
			return LightSample( dir, distance, radiance, 1.f );
		}

	  private:
		Vec3f _position = VEC3F_ZERO;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_SPHERICAL_LIGHT__

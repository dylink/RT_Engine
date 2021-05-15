#ifndef __RT_ISICG_GLOWING_MATERIAL__
#define __RT_ISICG_GLOWING_MATERIAL__

#include "base_material.hpp"
#include "defines.hpp"

namespace RT_ISICG
{
	class GlowingMaterial : public BaseMaterial
	{
	  public:
		GlowingMaterial( const std::string & p_name, const Vec3f & p_color, float power ) : BaseMaterial( p_name ), _color( p_color )
		{
			_emissive = p_color*power;
		}

		virtual ~GlowingMaterial() = default;

		Vec3f shade( const Ray & p_ray, const HitRecord & p_hit, const LightSample & p_lightSample ) const override
		{
			return _color;
		}

		inline const Vec3f & getFlatColor() const override { return _color; }

	  protected:
		Vec3f _color = Vec3f( 1.f, 1.f, 1.f );
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_GLOWING_MATERIAL__

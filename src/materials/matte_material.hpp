#ifndef __RT_ISICG_MATTE_MATERIAL__
#define __RT_ISICG_MATTE_MATERIAL__

#include "base_material.hpp"
#include "brdfs/oren_nayar_brdf.hpp"

namespace RT_ISICG
{
	class MatteMaterial : public BaseMaterial
	{
	  public:
		MatteMaterial( const std::string & p_name, const Vec3f & p_diffuse, float p_pente )
			: BaseMaterial( p_name ), _brdf( p_diffuse, p_pente ), _pente(p_pente)
		{
		}

		virtual ~MatteMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			return _brdf.evaluate( -p_ray.getDirection(), p_hitRecord._normal, p_lightSample._direction )
				   * std::max( 0.0f, dot( p_lightSample._direction, p_hitRecord._normal ) );
		}

		inline const Vec3f & getFlatColor() const override { return _brdf.getKd(); }

	  protected:
		OrenNayarBRDF _brdf;
		float		  _pente;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_MATTE_MATERIAL__

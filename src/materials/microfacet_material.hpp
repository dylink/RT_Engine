#ifndef __RT_ISICG_MICROFACET_MATERIAL__
#define __RT_ISICG_MICROFACET_MATERIAL__

#include "base_material.hpp"
#include "brdfs/oren_nayar_brdf.hpp"
#include "brdfs/microfacet_brdf.hpp"

namespace RT_ISICG
{
	class MicrofacetMaterial : public BaseMaterial
	{
	  public:
		MicrofacetMaterial( const std::string & p_name,
						 const Vec3f &		 p_diffuse,
						 const float & p_pente, 
						const float & p_metalness)
			: BaseMaterial( p_name ), _brdfMicrofacet(p_diffuse, p_pente ), _brdfOrenNayar( p_diffuse, p_pente ), _metalness(p_metalness)
		{
		}

		virtual ~MicrofacetMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			return ( 1 - _metalness )
					   * _brdfOrenNayar.evaluate( -p_ray.getDirection(), p_hitRecord._normal, p_lightSample._direction )
				   + _metalness
						 * _brdfMicrofacet.evaluate(
							 -p_ray.getDirection(), p_hitRecord._normal, p_lightSample._direction );
		}

		inline const Vec3f & getFlatColor() const override { return _brdfOrenNayar.getKd(); }

	  protected:
		MicrofacetBRDF	_brdfMicrofacet;
		OrenNayarBRDF _brdfOrenNayar;
		float		_metalness;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_MICROFACET_MATERIAL__

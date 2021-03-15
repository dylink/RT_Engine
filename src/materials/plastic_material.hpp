#ifndef __RT_ISICG_PLASTIC_MATERIAL__
#define __RT_ISICG_PLASTIC_MATERIAL__

#include "base_material.hpp"
#include "brdfs/phong_brdf.hpp"
#include "brdfs/lambert_brdf.hpp"

namespace RT_ISICG
{
	class PlasticMaterial : public BaseMaterial
	{
	  public:
		PlasticMaterial( const std::string & p_name, const Vec3f & p_diffuse, const Vec3f & p_specular, const float & p_coeff )
			: BaseMaterial( p_name ), _brdfLambert( p_diffuse ), _brdfPhong(p_specular, p_coeff)
		{
		}

		virtual ~PlasticMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			return _brdfPhong.evaluate( -p_ray.getDirection(), p_hitRecord._normal, p_lightSample._direction ) + _brdfLambert.evaluate();
		}

		inline const Vec3f & getFlatColor() const override { return _brdfLambert.getKd(); }

	  protected:
		PhongBRDF	_brdfPhong;
		LambertBRDF _brdfLambert;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_PLASTIC_MATERIAL__

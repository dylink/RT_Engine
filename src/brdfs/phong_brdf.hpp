#ifndef __RT_ISICG_BRDF_PHONG__
#define __RT_ISICG_BRDF_PHONG__

#include "defines.hpp"

namespace RT_ISICG
{
	class PhongBRDF
	{
	  public:
		PhongBRDF(const Vec3f & p_ks, const float & p_coeff ) : _ks(p_ks), _coeff(p_coeff) {};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( const Vec3f & wO, const Vec3f & normal, const Vec3f & wI ) const
		{
			const float cosA = glm::dot( -wO, glm::reflect( -wO, normal ) );
			Vec3f		h	  = glm::normalize( wO + wI );
			const float cosA2 = glm::dot( normal, h );
			return _ks * pow(cosA2, _coeff);
		}

		inline const Vec3f & getKs() const { return _ks; }

	  private:
		Vec3f _ks = WHITE;
		float _coeff;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_PHONG__

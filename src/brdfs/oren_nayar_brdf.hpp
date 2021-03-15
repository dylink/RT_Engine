#ifndef __RT_ISICG_BRDF_OREN_NAYAR__
#define __RT_ISICG_BRDF_OREN_NAYAR__

#include "defines.hpp"

namespace RT_ISICG
{
	class OrenNayarBRDF
	{
	  public:
		OrenNayarBRDF( const Vec3f & p_kd, const float & p_pente ) : _kd( p_kd ), _pente (p_pente) {
			_a		= 1 - (0.5 * ( glm::pow( _pente, 2 ) / ( glm::pow( _pente, 2 ) + 0.33 ) ));
			_b = 0.45 * ( glm::pow( _pente, 2 ) / ( glm::pow( _pente, 2 ) + 0.09 ) );
		};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( const Vec3f &		   wO,
							   const Vec3f &   normal,
							   const Vec3f & wI) const
		{
			const float cos_theta_r = glm::dot( wO, normal );
			const float cos_theta_i = glm::dot( wI, normal );
			const float theta_r		= glm::acos( cos_theta_r );
			const float theta_i		= glm::acos( cos_theta_i );

			const float cos_phi_diff
				= glm::dot(wO - normal * cos_theta_r , wI - normal * cos_theta_i );

			const float alpha = glm::max( theta_i, theta_r );
			const float beta  = glm::min( theta_i, theta_r );

			float b = cos_phi_diff >= 0 ? _b * cos_phi_diff * glm::sin( alpha ) * glm::tan( beta ) : 0.f;
			return _kd * INV_PIf
				   * ( _a + b );
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd = WHITE;
		float _pente;
		float _a;
		float _b;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_OREN_NAYAR__

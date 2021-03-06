#ifndef __RT_ISICG_BRDF_OREN_NAYAR__
#define __RT_ISICG_BRDF_OREN_NAYAR__

#include "defines.hpp"

namespace RT_ISICG
{
	class OrenNayarBRDF
	{
	  public:
		OrenNayarBRDF( const Vec3f & p_kd, const float & p_pente ) : _kd( p_kd ), _pente (p_pente) {
			_a		= 1.f - 0.5f * ( glm::pow( _pente, 2.f ) / ( glm::pow( _pente, 2.f ) + 0.33f ) );
			_b      = 0.45f * ( glm::pow( _pente, 2.f ) / ( glm::pow( _pente, 2.f ) + 0.09f ) );
		};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( const Vec3f &		   wO,
							   const Vec3f &   normal,
							   const Vec3f & wI) const
		{
			const float cos_theta_r = glm::max(0.f, glm::dot( wO, normal ));
			const float cos_theta_i = glm::max(0.f, glm::dot( wI, normal ));
			const float theta_r		= glm::acos( cos_theta_r );
			const float theta_i		= glm::acos( cos_theta_i );

			const float cos_phi_diff
				= glm::dot(wO - normal * cos_theta_r , wI - normal * cos_theta_i );

			const float alpha = glm::max( theta_i, theta_r );
			const float beta  = glm::min( theta_i, theta_r );

			float b = _b * glm::max(0.f,cos_phi_diff) * glm::sin( alpha ) * glm::tan( beta );
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

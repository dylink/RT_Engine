#ifndef __RT_ISICG_BRDF_MICROFACET__
#define __RT_ISICG_BRDF_MICROFACET__
#include "cstdio";
#include "defines.hpp"

#define G(x) (x/
namespace RT_ISICG
{
	class MicrofacetBRDF
	{
	  public:
		MicrofacetBRDF(const Vec3f p_color, const float & p_pente )
			: _f0(p_color), _pente( p_pente )
		{
		};

		inline float g1( const float & x ) const { 
			float _k = pow( _pente + 1, 2 ) / 8;
			return x / ( x * ( 1 - _k ) + _k );
		}

		inline float g( const Vec3f & wI, const Vec3f & wO, const Vec3f & normal ) const
		{
			return g1( dot(normal, wO )) * g1( dot(normal, wI ));
		}

		inline Vec3f f( const Vec3f & wO, const Vec3f & h) const
		{
			return _f0 + ( 1.f - _f0 ) * pow( ( 1.f - dot( h, wO ) ), 5.f );
		}

		inline float d( const Vec3f & h, const Vec3f & normal ) const { 
			float a = pow( _pente, 2 );
			float nH = dot( normal, h );
			return pow( a, 2 ) / ( PIf * pow( ( pow( nH, 2 ) * ( pow( a, 2 ) - 1 ) + 1 ), 2 ) );
		}


		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( const Vec3f & wO, const Vec3f & normal, const Vec3f & wI ) const
		{
			Vec3f h = glm::normalize( wO + wI );
			
			Vec3f dfg = d(h, normal) * f(wO, h) * g( wI, wO, normal );
			
			//printf( "(%f, %f, %f)\n", dfg.x, dfg.y, dfg.z );
			return dfg / ( 4 * ( dot( wO, normal ) * ( dot( wI, normal ) ) ) );
		}

	  private:
		Vec3f _f0;
		float _pente;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_MICROFACET__

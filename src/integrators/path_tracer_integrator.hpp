#ifndef __RT_ISICG_PATH_TRACER_INTEGRATOR__
#define __RT_ISICG_PATH_TRACER_INTEGRATOR__

#include "base_integrator.hpp"

namespace RT_ISICG
{
	class PathTracerIntegrator : public BaseIntegrator
	{
	  public:
		PathTracerIntegrator() : BaseIntegrator() {}
		virtual ~PathTracerIntegrator() = default;

		const IntegratorType getType() const override { return IntegratorType::PATH_TRACER; }

		// Return incoming luminance.
		Vec3f Li( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

		Vec3f recurs( const Scene & p_scene,
					  const Ray &	p_ray,
					  const float	p_tMin,
					  const float	p_tMax,
					  int tracerBounces,
					  const int		nbBounce,
					  const bool	isIn ) const;

		void coordonneesHemisphere( Vec3f & normale, Vec3f & vecx, Vec3f & vecz ) const;

		Vec3f rayonAleatoire( float r1, float r2 ) const;

		void setNbBounces( int nb ) { _maxBounces = nb; }
		
	  private:
		int	  _nbBounces	  = 5;
		int	  _maxBounces	  = 3;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_PATH_TRACER_INTEGRATOR__

#include "direct_light_integrator.hpp"

namespace RT_ISICG
{
	Vec3f DirectLightIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		HitRecord hitRecord;
		
		
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			Vec3f li = BLACK;
			for ( auto i : p_scene.getLights() ) {		
				Vec3f lContrib = BLACK;
				int nbLightSamples = i->getIsSurface() ? _nbLightSamples : 1;
				for (int j = 0; j < nbLightSamples; j++) {
					LightSample light = i->sample( hitRecord._point );
					Ray shadow( hitRecord._point, light._direction );
					shadow.offset( hitRecord._normal );
					if ( !p_scene.intersectAny( shadow, p_tMin, light._distance - SHADOW_EPSILON ) )
					{
						lContrib += hitRecord._object->getMaterial()->shade(p_ray, hitRecord, light) * light._radiance
								* glm::max( 0.f, glm::dot( light._direction, hitRecord._normal ) );
					}
				}
				lContrib /= nbLightSamples;
				
				li += lContrib;
				
			}
			/// TODO ! cos theta...
			return li;
		}
		else
		{
			return _backgroundColor;
		}
	}
} // namespace RT_ISICG

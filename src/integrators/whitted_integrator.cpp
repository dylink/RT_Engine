/*#include "whitted_integrator.hpp"
#include <cstdio>

namespace RT_ISICG
{
	Vec3f WhittedIntegrator::Li( const Scene & p_scene,
									 const Ray &   p_ray,
									 const float   p_tMin,
									 const float   p_tMax ) const
	{
		HitRecord hitRecord;
		float nbBounce = 0.f;
		//printf( "nbBounce %f\n", nbBounce );
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			
			Vec3f li = BLACK;
			if (hitRecord._object->getMaterial()->isMirror()) {
				if ( nbBounce > _nbBounces )
				{
					//nbBounce = 0;
					return BLACK;
				}
				nbBounce++;
				Vec3f direction = glm::reflect( p_ray.getDirection(), hitRecord._normal );
				Ray	  bounce( hitRecord._point, direction );
				bounce.offset( hitRecord._normal );
				li += Li( p_scene, bounce, p_tMin, p_tMax);
			}
			
			for ( auto i : p_scene.getLights() )
			{
				Vec3f lContrib		 = BLACK;
				int	  nbLightSamples = i->getIsSurface() ? _nbLightSamples : 1;
				for ( int j = 0; j < nbLightSamples; j++ )
				{
					LightSample light = i->sample( hitRecord._point );
					Ray			shadow( hitRecord._point, light._direction );
					shadow.offset( hitRecord._normal );
					if ( !p_scene.intersectAny( shadow, p_tMin, light._distance - SHADOW_EPSILON ) )
					{
						lContrib += hitRecord._object->getMaterial()->shade( p_ray, hitRecord, light ) * light._radiance
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
} // namespace RT_ISICG*/

//AUX

#include "whitted_integrator.hpp"
#include <cstdio>

namespace RT_ISICG
{
	Vec3f WhittedIntegrator::Li( const Scene & p_scene,
									 const Ray &   p_ray,
									 const float   p_tMin,
									 const float   p_tMax ) const
	{ 
		return recurs( p_scene, p_ray, p_tMin, p_tMax, 0, false );
	}

	Vec3f WhittedIntegrator::recurs( const Scene & p_scene,
									 const Ray &   p_ray,
									 const float   p_tMin,
									 const float   p_tMax,
									 const int	   nbBounce,
									 const bool	   isIn ) const
	{
		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			if ( nbBounce > _nbBounces ) { return BLACK; }
			Vec3f li = BLACK;
			if ( hitRecord._object->getMaterial()->isMirror() )
			{	
				
				Vec3f direction = glm::reflect( p_ray.getDirection(), hitRecord._normal );
				Ray	  bounce( hitRecord._point, direction );
				bounce.offset( hitRecord._normal );
				li+= recurs( p_scene, bounce, p_tMin, p_tMax, nbBounce+1, false );
			}
			if (hitRecord._object->getMaterial()->isTransparent()) {
				//if ( nbBounce > _nbBounces ) { return BLACK; }
				float kr		 = 0.f;
				float ior		 = 0.f;
				float n1		 = 0.f;
				float n2		 = 0.f;

				n1 = isIn ? hitRecord._object->getMaterial()->getIOR() : 1.f;
				n2 = isIn ? 1.f : hitRecord._object->getMaterial()->getIOR();
				ior				 = n1 / n2;
				Vec3f direction1 = glm::reflect( p_ray.getDirection(), hitRecord._normal );
				Ray	  bounce( hitRecord._point, direction1 );
				bounce.offset( hitRecord._normal );
				Vec3f		reflectedColor = recurs( p_scene, bounce, p_tMin, p_tMax, nbBounce + 1, isIn );
				Vec3f direction2
					= glm::refract( p_ray.getDirection(), hitRecord._normal, ior );
				Ray refract( hitRecord._point, direction2 );
				refract.offset( -hitRecord._normal );
				Vec3f refractedColor = recurs( p_scene, refract, p_tMin, p_tMax, nbBounce + 1, !isIn );
				float cosThetaI		 = glm::dot( p_ray.getDirection(), hitRecord._normal );
				float cosThetaT		 = glm::dot( direction2, hitRecord._normal );
				float rS			 = pow( ( n1 * cosThetaI - n2 * cosThetaT ) / ( n1 * cosThetaI + n2 * cosThetaT ), 2.f);
				float rP			 = pow( ( n1 * cosThetaT - n2 * cosThetaI ) / ( n1 * cosThetaT + n2 * cosThetaI ), 2.f);

				float R2 = 0.5 * ((long float)rS + rP);
				li += ( 1 - R2 ) * refractedColor + R2 * reflectedColor;
				

			}
			for ( auto i : p_scene.getLights() )
			{
				Vec3f lContrib		 = BLACK;
				int	  nbLightSamples = i->getIsSurface() ? _nbLightSamples : 1;
				for ( int j = 0; j < nbLightSamples; j++ )
				{
					LightSample light = i->sample( hitRecord._point );
					Ray			shadow( hitRecord._point, light._direction );
					shadow.offset( hitRecord._normal );
					if ( !p_scene.intersectAny( shadow, p_tMin, light._distance - SHADOW_EPSILON ) )
					{
						lContrib += hitRecord._object->getMaterial()->shade( p_ray, hitRecord, light ) * light._radiance
									* glm::max( 0.f, glm::dot( light._direction, hitRecord._normal ) );
					}
				}
				lContrib /= nbLightSamples;

				li += lContrib;
			}
			/// TODO ! cos theta...
			return li;
		}
		else if ( nbBounce > 0 )
		{
			return BLACK;
		}
		else
		{
			return _backgroundColor;
		}
		
	}

} // namespace RT_ISICG


#include "path_tracer_integrator.hpp"
#include "utils/random.hpp"
#include <cstdio>

namespace RT_ISICG
{
	Vec3f PathTracerIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		return recurs( p_scene, p_ray, p_tMin, p_tMax, 0, 0, false );
	}

	Vec3f PathTracerIntegrator::recurs( const Scene & p_scene,
									 const Ray &   p_ray,
									 const float   p_tMin,
									 const float   p_tMax,
int tracerBounces,		
									 const int	   nbBounce,
									 const bool	   isIn ) const
	{

		if ( tracerBounces > _maxBounces )
		{
			 return BLACK;
		}
		if ( nbBounce > _nbBounces ) { return BLACK; }
		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			
			Vec3f li = BLACK;
			if ( hitRecord._object->getMaterial()->isMirror() )
			{
				//Vec3f( 0, u1, 0 );
				Vec3f direction = glm::reflect( p_ray.getDirection(), hitRecord._normal );
				Ray	  bounce( hitRecord._point, direction );
				bounce.offset( hitRecord._normal );
				li += recurs( p_scene, bounce, p_tMin, p_tMax, tracerBounces, nbBounce + 1, false );
			}
			if ( hitRecord._object->getMaterial()->isTransparent() )
			{
				float ior = 0.f;
				float n1  = 0.f;
				float n2  = 0.f;

				n1				 = isIn ? hitRecord._object->getMaterial()->getIOR() : 1.f;
				n2				 = isIn ? 1.f : hitRecord._object->getMaterial()->getIOR();
				ior				 = n1 / n2;
				Vec3f direction1 = glm::reflect( p_ray.getDirection(), hitRecord._normal );
				Ray	  bounce( hitRecord._point, direction1 );
				bounce.offset( hitRecord._normal );
				Vec3f reflectedColor = recurs( p_scene, bounce, p_tMin, p_tMax, tracerBounces, nbBounce + 1, isIn );
				Vec3f direction2	 = glm::refract( p_ray.getDirection(), hitRecord._normal, ior );
				Ray	  refract( hitRecord._point, direction2 );
				refract.offset( -hitRecord._normal );
				Vec3f refractedColor
					= ( direction2 == BLACK ) ? BLACK : recurs( p_scene, refract, p_tMin, p_tMax, tracerBounces, nbBounce + 1, !isIn );

				float cosThetaI = glm::dot( p_ray.getDirection(), hitRecord._normal );
				float cosThetaT = glm::dot( direction2, hitRecord._normal );
				float rS		= pow( ( n1 * cosThetaI - n2 * cosThetaT ) / ( n1 * cosThetaI + n2 * cosThetaT ), 2.f );
				float rP		= pow( ( n1 * cosThetaT - n2 * cosThetaI ) / ( n1 * cosThetaT + n2 * cosThetaI ), 2.f );

				float R2 = 0.5 * ( (long float)rS + rP );
				li += ( 1 - R2 ) * refractedColor + R2 * reflectedColor;
			}
			
			for ( auto i : p_scene.getLights() )
			{
				Vec3f lContrib = BLACK;

				LightSample light = i->sample( hitRecord._point );
				Ray			shadow( hitRecord._point, light._direction );
				shadow.offset( hitRecord._normal );
				if ( !p_scene.intersectAny( shadow, p_tMin, light._distance - SHADOW_EPSILON ) )
				{
					lContrib += hitRecord._object->getMaterial()->shade( p_ray, hitRecord, light ) * light._radiance
								* glm::max( 0.f, glm::dot( light._direction, hitRecord._normal ) );
				}
				li += lContrib;


			}
			li += hitRecord._object->getMaterial()->emission();
			if (!hitRecord._object->getMaterial()->isTransparent()) {
				Vec3f vecx, vecz;
				// std::cout << tracerBounces << std::endl;
				coordonneesHemisphere( hitRecord._normal, vecx, vecz );
				float r1 = randomFloat();
				float r2 = randomFloat();

				Vec3f sampleDir		   = rayonAleatoire( r1, r2 );
				Vec3f sampleImageSpace = sampleDir.x * vecx + sampleDir.y * hitRecord._normal + sampleDir.z * vecz;

				Ray tracer( hitRecord._point, sampleImageSpace );
				tracer.offset( hitRecord._normal );
				li += recurs( p_scene, tracer, p_tMin, p_tMax, tracerBounces + 1, nbBounce, isIn )
						  * hitRecord._object->getMaterial()->getFlatColor();

			}
			
			/// TODO ! cos theta...
			return li;
		}
		else if ( nbBounce > 0 )
		{
			return _backgroundColor;
		}
		else
		{
			return _backgroundColor;
		}
	}


	void PathTracerIntegrator::coordonneesHemisphere(Vec3f &normale, Vec3f &vecx, Vec3f &vecz) const{ 
		if ( abs( normale.x ) > abs( normale.y ) )
			vecx = Vec3f( normale.z, 0, -normale.x ) / sqrt( normale.x / normale.x + normale.z * normale.z );
		else
			vecx = Vec3f( 0, -normale.z, normale.y ) / sqrt( normale.y * normale.y + normale.z * normale.z );

		vecz = glm::cross( normale, vecx );

		glm::normalize( vecx );
		glm::normalize( vecz );
	}

	Vec3f PathTracerIntegrator::rayonAleatoire( float r1, float r2 ) const
	{ 
		float sinThete = sqrt( 1 - r1 * r1 );
		float phi	   = 2 * glm::pi<float>() * r2;
		float x		   = sinThete * cos( phi );
		float z		   = sinThete * sin( phi );

		return glm::normalize(Vec3f( x, r1, z ));
	}



} // namespace RT_ISICG

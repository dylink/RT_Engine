#include "direct_light_integrator.hpp"

namespace RT_ISICG
{
	Vec3f DirectLightIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		HitRecord hitRecord;
		
		
		//std::cout << p_scene.getLights()[0]->getPower() << "\n";
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			Vec3f li = BLACK;
			for ( auto i : p_scene.getLights() ) {
				li += hitRecord._object->getMaterial()->getFlatColor()
					  * i->sample( hitRecord._point )._radiance
					  * glm::max( 0.f, glm::dot( -p_ray.getDirection(), hitRecord._normal ) );
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

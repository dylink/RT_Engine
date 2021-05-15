#ifndef __RT_ISICG_HEXAEDRA__
#define __RT_ISICG_HEXAEDRA__

#include "base_object.hpp"
#include "geometry/hexaedra_geometry.hpp"

namespace RT_ISICG
{
	class Hexaedra : public BaseObject
	{
	  public:
		Hexaedra()		  = delete;
		virtual ~Hexaedra() = default;

		Hexaedra( const std::string & p_name, const Vec3f & p_size, const Vec3f & p_position )
			: BaseObject( p_name ), _geometry( p_size, p_position )
		{
		}

		// Check for nearest intersection between p_tMin and p_tMax : if found fill p_hitRecord.
		virtual bool intersect( const Ray & p_ray,
								const float p_tMin,
								const float p_tMax,
								HitRecord & p_hitRecord ) const override;

		bool intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

	  private:
		HexaedraGeometry _geometry;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_HEXAEDRA__

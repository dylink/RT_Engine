#ifndef __RT_ISICG_HEXAEDRA_GEOMETRY__
#define __RT_ISICG_HEXAEDRA_GEOMETRY__

#include "base_geometry.hpp"

namespace RT_ISICG
{
	class HexaedraGeometry : public BaseGeometry
	{
	  public:
		HexaedraGeometry()		  = delete;
		virtual ~HexaedraGeometry() = default;

		HexaedraGeometry( const Vec3f & size, const Vec3f & position )
			: _min( Vec3f( position.x - ( size.x / 2 ), position.y - (size.y / 2), position.z - (size.z / 2 )) ),
			  _max( Vec3f( position.x + (size.x / 2 ), position.y + (size.y / 2), position.z + (size.z / 2) ) )
		{
		}

		inline const Vec3f & getMax() const { return _max; }
		inline const Vec3f & getMin() const { return _min; }

		bool intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const;

		inline Vec3f computeNormal( const Vec3f & p_point ) const
		{
			/// TODO !
			Vec3f c = ( _min + _max ) * 0.5f;
			Vec3f p = p_point - c;
			Vec3f d = ( _max - _min ) * 0.5f;
			float biais = 1.0001f;

			return glm::normalize( Vec3f( (float)((int)(( p.x ) / abs( d.x ) * biais) ),
										  (float)((int)(( p.y ) / abs( d.y ) * biais )),
										  (float)((int)(( p.z ) / abs( d.z ) * biais )) ));
			//return glm::normalize( p_point - _center );
		}

	  private:
		Vec3f _min = VEC3F_ZERO;
		Vec3f _max = BLACK;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_HEXAEDRA_GEOMETRY__

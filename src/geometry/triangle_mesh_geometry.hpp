#ifndef __RT_ISICG_TRIANGLE_GEOMETRY__
#define __RT_ISICG_TRIANGLE_GEOMETRY__

#include "base_geometry.hpp"

namespace RT_ISICG
{
	class MeshTriangle;

	class TriangleMeshGeometry : public BaseGeometry
	{
	  public:
		TriangleMeshGeometry()			= delete;
		virtual ~TriangleMeshGeometry() = default;

		TriangleMeshGeometry( const uint p_v0, const uint p_v1, const uint p_v2, MeshTriangle * p_refMesh );

		bool intersect( const Ray & p_ray, float & p_t, Vec2f & normal ) const;

		inline const Vec3f & getFaceNormal() const { return _faceNormal; }

		Vec3f interpolateNormal( Vec2f & uv ) const;

	  private:
		MeshTriangle * _refMesh;
		union
		{
			struct
			{
				uint _v0, _v1, _v2;
			};
			uint _v[ 3 ] = { 0, 0, 0 };
		};

		Vec3f _faceNormal;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_TRIANGLE_GEOMETRY__

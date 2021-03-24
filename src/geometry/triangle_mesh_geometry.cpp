#include "triangle_mesh_geometry.hpp"
#include "objects/triangle_mesh.hpp"

namespace RT_ISICG
{
	TriangleMeshGeometry::TriangleMeshGeometry( const uint	   p_v0,
												const uint	   p_v1,
												const uint	   p_v2,
												MeshTriangle * p_refMesh )
		: _v0( p_v0 ), _v1( p_v1 ), _v2( p_v2 ), _refMesh( p_refMesh )
	{
		_faceNormal = glm::normalize( glm::cross( _refMesh->_vertices[ p_v1 ] - _refMesh->_vertices[ p_v0 ],
												  _refMesh->_vertices[ p_v2 ] - _refMesh->_vertices[ p_v0 ] ) );
	}

	bool TriangleMeshGeometry::intersect( const Ray & p_ray, float & p_t ) const
	{
		const float	  EPSILON = 0.0000001;
		const Vec3f & o	 = p_ray.getOrigin();
		const Vec3f & d	 = p_ray.getDirection();
		const Vec3f & v0 = _refMesh->_vertices[ _v0 ];
		const Vec3f & v1 = _refMesh->_vertices[ _v1 ];
		const Vec3f & v2 = _refMesh->_vertices[ _v2 ];

		Vec3f edge1, edge2, h, s, q;

		float a, f, u, v;

		edge1 = v1 - v0;
		edge2 = v2 - v0;
		h	  = cross( d, edge2 );
		a	  = dot( edge1, h );
		if (a > -EPSILON && a < EPSILON) return false;
		f = 1.f / a;
		s = o - v0;
		u = f * dot( s, edge1 );
		if (u < 0.f || u > 1.f) return false;
		q = cross( s, edge1 ) ;
		v = f * dot( d, q );
		if (v < 0.f || u + v > 1.f) return false;
		float t = f * dot( edge2, q );
		if (t > EPSILON) { 
			p_t = glm::distance(o, o+d * t);
			return true;
		}
		else
			return false;
		/// TODO
	}

} // namespace RT_ISICG
 
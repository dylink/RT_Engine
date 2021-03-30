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

	bool TriangleMeshGeometry::intersect( const Ray & p_ray, float & p_t, Vec2f & uv ) const
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
		if ( a > -EPSILON && a < EPSILON ) {
			p_t = a;
			return false; // Le rayon est parallèle au triangle.
		}
		f = 1.f / a;
		s = o - v0;
		u = f * dot( s, h );
		if ( u < 0.f || u > 1.f ) {
			return false; 
		}
		q = cross( s, edge1 ) ;
		v = f * dot( d, q );
		if ( v < 0.f || u + v > 1.f ) {
			return false; 
		}
		// On calcule t pour savoir ou le point d'intersection se situe sur la ligne.
		float t = f * dot( edge2, q );
		p_t		= t;
		uv = Vec2f(u, v);
		if (t > EPSILON) { 
			return true;
		}
		else // On a bien une intersection de droite, mais pas de rayon.
		{
			return false;
		}
			
		/// TODO
	}

	Vec3f TriangleMeshGeometry::interpolateNormal(Vec2f & uv) const {
		Vec3f vec = ( 1 - uv.x - uv.y ) * _refMesh->_normals[ _v0 ] + uv.x * _refMesh->_normals[ _v1 ]
					+ uv.y * _refMesh->_normals[ _v2 ];
		return glm::normalize( vec );
	}

} // namespace RT_ISICG
 
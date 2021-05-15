#include "triangle_mesh.hpp"

namespace RT_ISICG
{
	bool MeshTriangle::intersect( const Ray & p_ray,
								  const float p_tMin,
								  const float p_tMax,
								  HitRecord & p_hitRecord ) const
	{
		HitRecord hitRecord;
		if ( _bvh.intersect( p_ray, p_tMin, p_tMax, p_hitRecord ) )
		{
			//p_hitRecord			= hitRecord;
			p_hitRecord._object = this;
			return true;
		}
		
		return false;
	}

	bool MeshTriangle::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		if (_bvh.intersectAny(p_ray, p_tMin, p_tMax)) { 
			return true;
		}
		return false;
	}

	void MeshTriangle::buildBVH() { 
		std::cout << _vertices[ 0 ][ 0 ] << " && " << _triangles[ 0 ].getVertices()[ 0 ][ 0 ] << std::endl;
		_bvh.build( &_triangles, _aabb );
	}
} // namespace RT_ISICG

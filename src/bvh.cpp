#include "bvh.hpp"
#include "geometry/triangle_mesh_geometry.hpp"
#include "utils/chrono.hpp"
#include <algorithm>

namespace RT_ISICG
{
	void BVH::build( std::vector<TriangleMeshGeometry> * p_triangles, AABB aabb )
	{
		std::cout << "Building BVH..." << std::endl;
		if ( p_triangles == nullptr || p_triangles->empty() )
		{
			throw std::exception( "BVH::build() error: no triangle provided" );
		}
		_triangles = p_triangles;

		Chrono chr;
		chr.start();

		/// TODO
		_root = new BVHNode( aabb, 0, ( *_triangles ).size() );
		_buildRec( _root, 0, 0, (*_triangles).size());

		chr.stop();

		std::cout << "[DONE]: " << chr.elapsedTime() << "s" << std::endl;
	}

	bool BVH::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		/// TODO

		return _intersectRec( _root, p_ray, p_tMin, p_tMax, p_hitRecord );
	}

	bool BVH::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{

		return _intersectAnyRec( _root, p_ray, p_tMin, p_tMax );
		/// TODO
	}

	void BVH::_partition(BVHNode * p_node, const uint axe, const float milieu, const uint firstID, const uint lastID) {
		AABB			   aabbLeft, aabbRight;
		uint			   i = firstID;
		uint			   j = lastID - 1;
		for (;i<=j;)
		{
			std::vector<Vec3f> _vertices = ( *_triangles )[ i ].getVertices();
			if ( ( *_triangles )[ i ].barycenter( axe ) < milieu )
			{
				aabbLeft.extend( _vertices[ 0 ] );
				aabbLeft.extend( _vertices[ 1 ] );
				aabbLeft.extend( _vertices[ 2 ] );
				i++;
				continue;
			}
			aabbRight.extend( _vertices[ 0 ] );
			aabbRight.extend( _vertices[ 1 ] );
			aabbRight.extend( _vertices[ 2 ] );
			std::iter_swap( ( *_triangles ).begin() + i, ( *_triangles ).begin() + j );
			j--;
		}

		p_node->_left  = new BVHNode( aabbLeft, firstID, i );
		p_node->_right = new BVHNode( aabbRight, i, lastID );
	}

	void BVH::_buildRec( BVHNode *	p_node,
						 const uint p_depth, uint a, uint b )
	{

		if ( p_depth == _maxDepth || b - a < _maxTrianglesPerLeaf ) return;

		uint axe	 = p_node->_aabb.largestAxis();
		const float	 axisVal = p_node->_aabb.centroid()[ axe ];

		const float longueur = ( p_node->_aabb.getMax()[ axe ] - p_node->_aabb.getMin()[ axe ] );



		_partition( p_node, axe, axisVal, a, b );

		_buildRec( p_node->_left, p_depth + 1, a, p_node->_left->_lastTriangleId );
		_buildRec( p_node->_right, p_depth + 1, p_node->_left->_lastTriangleId, b );
		/// TODO
	}

	bool BVH::_intersectRec( const BVHNode * p_node,
							 const Ray &	 p_ray,
							 const float	 p_tMin,
							 const float	 p_tMax,
							 HitRecord &	 p_hitRecord ) const
	{

		if ( p_node->_aabb.intersect( p_ray, p_tMin, p_tMax ) )
		{
			if ( p_node->isLeaf() )
			{
				Vec2f  uv;
				float  tClosest = p_tMax;				   // Hit distance.
				size_t hitTri	= p_node->_lastTriangleId; // Hit triangle id.
				Vec2f  uv2;
				for ( size_t i = p_node->_firstTriangleId; i < p_node->_lastTriangleId; i++ )
				{
					float t;
					if ( ( *_triangles )[ i ].intersect( p_ray, t, uv ) )
					{
						if ( t >= p_tMin && t <= tClosest )
						{
							uv2		 = uv;
							tClosest = t;
							hitTri	 = i;
						}
					}
				}
				if ( hitTri != p_node->_lastTriangleId ) // Intersection found.
				{
					p_hitRecord._point	= p_ray.pointAtT( tClosest );
					p_hitRecord._normal = ( *_triangles )[ hitTri ].interpolateNormal( uv2 );
					p_hitRecord.faceNormal( p_ray.getDirection() );
					p_hitRecord._distance = tClosest;

					return true;
				}
				return false;
			}
			else
			{
				HitRecord  left;
				HitRecord right;
				bool left_b = _intersectRec( p_node->_left, p_ray, p_tMin, p_tMax, left );
				
				bool right_b = _intersectRec( p_node->_right, p_ray, p_tMin, p_tMax, right );

				if ( left_b && right_b )
				{
					p_hitRecord = ( left._distance < right._distance ? left : right );
					return true;
				}
				else if ( left_b )
				{
					p_hitRecord = left;
					return true;
				}
				else if ( right_b )
				{
					p_hitRecord = right;
					return true;
				}
			}
		}
		return false;

		/// TODO
	}
	bool BVH::_intersectAnyRec( const BVHNode * p_node,
								const Ray &		p_ray,
								const float		p_tMin,
								const float		p_tMax ) const
	{
		if ( p_node->_aabb.intersect( p_ray, p_tMin, p_tMax ) )
		{
			if ( p_node->isLeaf() )
			{
				Vec2f  uv;
				float  tClosest = p_tMax;				   // Hit distance.
				size_t hitTri	= p_node->_lastTriangleId; // Hit triangle id.
				Vec2f  uv2;
				for ( size_t i = p_node->_firstTriangleId; i < p_node->_lastTriangleId; i++ )
				{
					float t;
					if ( ( *_triangles )[ i ].intersect( p_ray, t, uv ) )
					{
						if ( t >= p_tMin && t <= p_tMax ) return true; // No need to search for the nearest.
					}
				}
				return false;
			}
			else
			{
				return _intersectAnyRec( p_node->_left, p_ray, p_tMin, p_tMax )
					   || _intersectAnyRec( p_node->_right, p_ray, p_tMin, p_tMax );
			}
		}
			/// TODO
		return false;
	}
} // namespace RT_ISICG

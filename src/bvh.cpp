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
		_buildRec( _root, 0);

		chr.stop();

		std::cout << "[DONE]: " << chr.elapsedTime() << "s" << std::endl;
	}

	bool BVH::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		/// TODO

		if ( _intersectRec( _root, p_ray, p_tMin, p_tMax, p_hitRecord ) ) return true;
		return false;
	}

	bool BVH::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{

		if ( _intersectAnyRec( _root, p_ray, p_tMin, p_tMax ) ) return true;
		/// TODO
		return false;
	}

	uint BVH::_partition(const uint axe, const float milieu, const uint firstID, const uint lastID) {
		uint ind = 0;
		
		for ( uint i = firstID;  i< lastID; i++)
		{
			//std::cout << i << " == " << milieu << " && " << ( *_triangles )[ i ].barycenter( axe ) << "\n";
			if ( (*_triangles)[i].barycenter(axe) > milieu ) {

				return ind;
			}
			ind++;
		}
		return ind;
	}

	void BVH::_buildRec( BVHNode *	p_node,
						 const uint p_depth )
	{

		if ( p_depth == _maxDepth || p_node->_lastTriangleId - p_node->_firstTriangleId < _maxTrianglesPerLeaf ) return;

		uint axis	 = p_node->_aabb.largestAxis();
		const float	 axisVal = p_node->_aabb.centroid()[ axis ];

		AABB	aabbLeft, aabbRight;
		uint			   nextIdLeft  = p_node->_firstTriangleId;
		uint	nextIdRight = p_node->_lastTriangleId -1;
		std::vector<Vec3f> _vertices;
		while ( nextIdLeft <= nextIdRight )
		{
			_vertices = ( *_triangles )[ nextIdLeft ].getVertices();
			if ( ( *_triangles )[ nextIdLeft ].barycenter( axis ) < axisVal )
			{
				aabbLeft.extend( _vertices[ 0 ] );
				aabbLeft.extend( _vertices[ 1 ] );
				aabbLeft.extend( _vertices[ 2 ] );
				nextIdLeft++;
			}
			else
			{
				aabbRight.extend( _vertices[ 0 ] );
				aabbRight.extend( _vertices[ 1 ] );
				aabbRight.extend( _vertices[ 2 ] );
				TriangleMeshGeometry tmpSwap   = ( *_triangles )[ nextIdRight ];
				( *_triangles )[ nextIdRight ] = ( *_triangles )[ nextIdLeft ];
				( *_triangles )[ nextIdLeft ]  = tmpSwap;
				nextIdRight--;
			}
		}


		//std::cout << p_node->_firstTriangleId << " && " << p_node->_lastTriangleId << std::endl;
		p_node->_left  = new BVHNode( aabbLeft, p_node->_firstTriangleId, nextIdLeft );
		p_node->_right = new BVHNode( aabbRight, nextIdLeft, p_node->_lastTriangleId );

		_buildRec( p_node->_left, p_depth + 1 );
		_buildRec( p_node->_right, p_depth + 1 );
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
					p_hitRecord._object	  = nullptr;

					return true;
				}
				return false;
			}
			else
			{
				HitRecord  hitLeft;
				const bool intersectLeft = _intersectRec( p_node->_left, p_ray, p_tMin, p_tMax, hitLeft );
				HitRecord  hitRight;
				const bool intersectRight = _intersectRec( p_node->_right, p_ray, p_tMin, p_tMax, hitRight );

				if ( intersectLeft && intersectRight )
				{
					p_hitRecord = ( hitLeft._distance < hitRight._distance ? hitLeft : hitRight );
					return true;
				}
				else if ( intersectLeft )
				{
					p_hitRecord = hitLeft;
					return true;
				}
				else if ( intersectRight )
				{
					p_hitRecord = hitRight;
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

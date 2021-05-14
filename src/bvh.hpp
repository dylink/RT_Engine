#ifndef __RT_ISICG_BVH__
#define __RT_ISICG_BVH__

#include "aabb.hpp"
#include "hit_record.hpp"
#include <vector>

namespace RT_ISICG
{
	class TriangleMeshGeometry;

	struct BVHNode
	{
		BVHNode() = default;
		~BVHNode()
		{
			delete _left;
			delete _right;
		}

		BVHNode(AABB aabb, uint first, uint last) { 
			_aabb = aabb;
			_firstTriangleId = first;
			_lastTriangleId	 = last;
		}

		bool isLeaf() const { return ( _left == nullptr && _right == nullptr ); }

		AABB	  _aabb;
		BVHNode * _left			   = nullptr;
		BVHNode * _right		   = nullptr;
		uint	  _firstTriangleId = 0;
		uint	  _lastTriangleId  = 0;
	};

	class BVH
	{
	  public:
		BVH() = default;
		~BVH() { delete _root; }

		// Build the BVH from a list of triangles (call _buildRec).
		void build( std::vector<TriangleMeshGeometry> * p_triangles, AABB aabb );

		// Search for the nearest intersection with the ray (call _intersectRec).
		bool intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const;
		// Search for the any intersection with the ray (call _intersectRec).
		bool intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const;

	  private:
		void _buildRec( BVHNode * p_node, const uint p_firstTriangleId, const uint p_lastTriangleId, const uint p_depth );

		bool _intersectRec( const BVHNode * p_node,
							const Ray &		p_ray,
							const float		p_tMin,
							const float		p_tMax,
							HitRecord &		p_hitRecord ) const;

		bool _intersectAnyRec( const BVHNode * p_node,
							   const Ray &	   p_ray,
							   const float	   p_tMin,
							   const float	   p_tMax ) const;

		void _partition(BVHNode * node,  const uint axe, const float milieu, const uint firstID, const uint lastID );

	  private:
		std::vector<TriangleMeshGeometry> * _triangles = nullptr;
		BVHNode *							_root	   = nullptr;

		const uint _maxTrianglesPerLeaf = 8;
		const uint _maxDepth			= 32;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_BVH__

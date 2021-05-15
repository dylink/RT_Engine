#include "scene.hpp"
#include "materials/color_material.hpp"
#include "materials/lambert_material.hpp"
#include "materials/matte_material.hpp"
#include "materials/plastic_material.hpp"
#include "materials/microfacet_material.hpp"
#include "materials/mirror_material.hpp"
#include "materials/transparent_material.hpp"
#include "objects/sphere.hpp"
#include "objects/plane.hpp"
#include "objects/hexaedra.hpp"
#include "lights/point_light.hpp"
#include "lights/quad_light.hpp"
#include "lights/spherical_light.hpp"
#include <cstdio>
#include "objects/triangle_mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace RT_ISICG
{
	//Vec3f( 1, 0.85, 0.57 )
	Scene::Scene() { _addMaterial( new ColorMaterial( "default", WHITE ) ); }

	Scene::~Scene()
	{
		for ( const ObjectMapPair & object : _objectMap )
		{
			delete object.second;
		}
		for ( const MaterialMapPair & material : _materialMap )
		{
			delete material.second;
		}
		for ( const BaseLight * light : _lightList )
		{
			delete light;
		}
	}

	void Scene::init()
	{
		/*// Add objects.
		_addObject( new Sphere( "Sphere1", Vec3f( 0.f, 0.f, 3.f ), 1.f ) );

		// Add materials.
		_addMaterial( new MicrofacetMaterial( "Gold", Vec3f(1,0.85,0.57), 0.3, 0.5 ));

		// Link objects and materials.
		_attachMaterialToObject( "Gold", "Sphere1" );

		_addObject( new Plane( "Plane1", Vec3f( 0, -2, 0 ), Vec3f( 0, 1, 0 ) ) );

		_addMaterial( new LambertMaterial( "Red", RED ) );

		_attachMaterialToObject( "Red", "Plane1" );

		_addLight( new PointLight( Vec3f( 1, 1, 1 ), 60.f, Vec3f( 0, 0, -2 ) ) );

		//_addLight( new QuadLight( Vec3f( 1, 1, 1 ), 20.f, Vec3f( 1, 10, 2 ), Vec3f( -2, 0, 0 ), Vec3f( 0, 0, 2 ) ) );
		*/

		// ================================================================
		// Add materials .
		// ================================================================
		/*_addMaterial( new MatteMaterial( " WhiteMatte ", WHITE, 0.f ) );
		_addMaterial( new MatteMaterial( " RedMatte ", RED, 0.6f ) );
		_addMaterial( new MatteMaterial( " GreenMatte ", GREEN, 0.6f ) );
		_addMaterial( new MatteMaterial( " BlueMatte ", BLUE, 0.6f ) );
		_addMaterial( new MatteMaterial( " GreyMatte ", GREY, 0.6f ) );
		_addMaterial( new MatteMaterial( " MagentaMatte ", MAGENTA, 0.6f ) );
		_addMaterial( new LambertMaterial( " YellowMatte ", YELLOW) );
		_addMaterial( new MirrorMaterial( " Mirror "));
		_addMaterial( new TransparentMaterial( " Transparent " ) );
		// ================================================================
		// Add objects .
		// ================================================================
		// Spheres .
		_addObject( new Hexaedra( "Hexa", Vec3f( 2, 2, 2 ), Vec3f( 2, 0, 3 ) ) );
		_addObject( new Sphere( " Sphere1 ", Vec3f( -2.f, 0.f, 3.f ), 1.5f ) );
		_attachMaterialToObject( " YellowMatte ", " Sphere1 " );
		//printf( "isMirror %d\n", _objectMap[ " Sphere1 " ]->getMaterial()->isMirror() );
		//_addObject( new Sphere( " Sphere2 ", Vec3f( 2.f, 0.f, 3.f ), 1.5f ) );
		_attachMaterialToObject( " Transparent ", "Hexa" );
		// Pseudo Cornell box made with infinite planes .
		_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_attachMaterialToObject( " GreyMatte ", " PlaneGround " );
		_addObject( new Plane( " PlaneLeft ", Vec3f( 5.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( " RedMatte ", " PlaneLeft " );
		_addObject( new Plane( " PlaneCeiling ", Vec3f( 0.f, 7.f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
		_attachMaterialToObject( " GreenMatte ", " PlaneCeiling " );
		_addObject( new Plane( " PlaneRight ", Vec3f( -5.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( " BlueMatte ", " PlaneRight " );
		_addObject( new Plane( " PlaneFront ", Vec3f( 0.f, 0.f, 10.f ), Vec3f( 0.f, 0.f, -1.f ) ) );
		_attachMaterialToObject( " MagentaMatte ", " PlaneFront " );
		// ================================================================
		// Add lights .
		// ================================================================
		_addLight( new PointLight( WHITE, 120.f, Vec3f( 0.f, 5.f, 0.f ) ) );*/
		//_addLight(new QuadLight( WHITE, 40.f, Vec3f( 1.f, 5.f, -2.f ), Vec3f( -2.f, 0.f, 0.f ), Vec3f( 0.f, 1.f, 2.f )) );

		// ================================================================
		// Add materials .
		// ================================================================
		/*_addMaterial( new MatteMaterial( " RedMatte ", RED, 0.6f ) );
		_addMaterial( new MatteMaterial( " GreenMatte ", GREEN, 0.6f ) );
		_addMaterial( new MatteMaterial( " BlueMatte ", BLUE, 0.6f ) );
		_addMaterial( new MatteMaterial( " GreyMatte ", Vec3f(1., 0.5, 0.5), 0.6f ) );
		_addMaterial( new MatteMaterial( " MagentaMatte ", MAGENTA, 0.6f ) );
		_addMaterial( new MatteMaterial( " YellowMatte ", WHITE, 0.6f ) );
		_addMaterial( new MatteMaterial( " CyanMatte ", CYAN, 0.6f ) );
		_addMaterial( new TransparentMaterial( "Transparent" ) );
		_addMaterial( new MirrorMaterial( "Mirror" ) );*/
		// ================================================================
		// Add objects .
		// ================================================================
		// OBJ.
		//loadFileTriangleMesh( "Glass", DATA_PATH + "Glass.obj" , 0.2, Vec3f(2,2,3));
		//_objectMap[ "Glass" ]->resize( 0.2 );
		/*_addMaterial( new LambertMaterial( "grey", YELLOW ) );
		_materialMap[ "grey" ]->setEmissive(YELLOW, 30.f);*/
		/*_addMaterial( new MicrofacetMaterial( "GREY", GREY, 0.5, 0.8 ) );
		loadFileTriangleMesh( "table", DATA_PATH + "table.obj", 0.7, Vec3f( 0, -2, 0 ) );*/
		/*_addMaterial( new MatteMaterial( "RedGlow", RED, 0.6f ) );
		_materialMap[ "RedGlow" ]->setEmissive( YELLOW, 30.f );*/
		//_addObject( new Hexaedra( "Hexa", Vec3f( 1, 1, 1 ), Vec3f( 0.f, 0.f, 0.f ) ) );
		/*_addMaterial( new MicrofacetMaterial( "Gold", Vec3f( 1, 0.85, 0.57 ), 0.5, 0.9 ) );
		_attachMaterialToObject( "Gold", "table_Circle005_Mesh.003" );
		_attachMaterialToObject( "Gold", "table_Circle004_Mesh.004" );
		_attachMaterialToObject( "Gold", "table_Circle003_Mesh.005" );
		_attachMaterialToObject( "Transparent", "table_Circle012_Mesh.006" );*/
		/*_addObject( new Sphere( "Sphere1", Vec3f( -2.f, 0.f, 3.f ), 1.f ) );
		_attachMaterialToObject( "grey", "Sphere1" );*/
		/*_attachMaterialToObject( "Transparent", "bulb_#LMP0002_Glass(No_Refraction)" );
		_attachMaterialToObject( "GREY", "bulb_#LMP0002_Single_Light_Bulb(No_Refraction)_Circle.003" );*/
		/*_addObject( new Sphere( "Sphere2", Vec3f( -1.f, 0.f, 3.f ), 1.f ) );
		_attachMaterialToObject( "Transparent", "Sphere2" );*/
		// Pseudo Cornell box made with infinite planes .

		/*_addObject( new Hexaedra( "Hexa", Vec3f( 0.3, 0.3, 0.3 ), Vec3f( 1.f, -0.65, 4.f ) ) );
		_addMaterial( new LambertMaterial( "grey", YELLOW ) );
		_materialMap[ "grey" ]->setEmissive( YELLOW, 30.f );
		_attachMaterialToObject( "grey", "Hexa" );*/

		/*loadFileTriangleMesh( "table", DATA_PATH + "table.obj", 1, Vec3f( 0, -2.5, 5 ) );
		_addMaterial( new MicrofacetMaterial( "Gold", Vec3f( 1, 0.85, 0.57 ), 0.5, 0.9 ) );
		_attachMaterialToObject( "Gold", "table_Circle005_Mesh.003" );
		_attachMaterialToObject( "Gold", "table_Circle004_Mesh.004" );
		_attachMaterialToObject( "Gold", "table_Circle003_Mesh.005" );
		_attachMaterialToObject( "Transparent", "table_Circle012_Mesh.006" );




		_addMaterial( new MicrofacetMaterial( "Gold", Vec3f(0.30, 0.20, 0.00), 0.3, 0.5 ) );
		loadFileTriangleMesh( "mirror", DATA_PATH + "mirror.obj", 1, Vec3f( 0, -2.5, 5 ) );
		_addMaterial( new MicrofacetMaterial( "Brown", Vec3f( 0.30, 0.20, 0.00 ), 0.5, 0.9 ) );
		_attachMaterialToObject( "Mirror", "mirror_Box002_meshId0_name" );
		//_attachMaterialToObject( "Brown", "mirror_Box002.001_meshId1_name" );

		loadFileTriangleMesh( "glass", DATA_PATH + "glass.obj", 1, Vec3f( 0, -2.5, 5 ) );
		_attachMaterialToObject( "Transparent", "glass_Circle" );
		

		_addMaterial( new MicrofacetMaterial( "Beige", Vec3f( 0.27, 0.00, 0.40 ), 1, 0.1 ) );

		_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_attachMaterialToObject( " YellowMatte ", " PlaneGround " );
		_addObject( new Plane( " PlaneLeft ", Vec3f( 10.f, 0.f, 0.f ), Vec3f( -1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( "Beige", " PlaneLeft " );
		_addObject( new Plane( " PlaneCeiling ", Vec3f( 0.f, 7.f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
		_attachMaterialToObject( " YellowMatte ", " PlaneCeiling " );
		_addObject( new Plane( " PlaneRight ", Vec3f( -10.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( " BlueMatte ", " PlaneRight " );
		_addObject( new Plane( " PlaneFront ", Vec3f( 0.f, 0.f, 15.f ), Vec3f( 0.f, 0.f, -1.f ) ) );
		_attachMaterialToObject( "Mirror", " PlaneFront " );
		_addObject( new Plane( " PlaneRear ", Vec3f( 0.f, 0.f, -10.f ), Vec3f( 0.f, 0.f, 1.f ) ) );
		_attachMaterialToObject( " BlueMatte ", " PlaneRear " );
		// ================================================================
		// Add lights .
		// ================================================================
		//_addLight( new SphericalLight( MAGENTA, 150.f, Vec3f( -3.f, 3.f, 2.f ) ) );
		_addLight( new PointLight( YELLOW, 80.f, Vec3f( 5.f, 6.f, 10.f ) ) );*/
		//_addLight(new QuadLight( WHITE, 40.f, Vec3f( 0.f, 3.f, -5.f ), Vec3f( -2.f, 0.f, 0.f ), Vec3f( 0.f, 1.f, 2.f )) );
		/*_addMaterial( new MirrorMaterial( "Transparent" ) );
		_addMaterial( new MicrofacetMaterial( "Gold", Vec3f( 1, 0.85, 0.57 ), 0.0, 0.8 ) );
		_addMaterial( new MatteMaterial( " RedMatte ", Vec3f( 1, .3, .3 ), 0.f ) );
		_addMaterial( new MatteMaterial( " WhiteMatte ", Vec3f( 1 ), 0.f ) );

		_addObject( new Sphere( "Sphere1", Vec3f( 0.f, 1.f, 0.f ), 1.f ) );
		_attachMaterialToObject( "Transparent", "Sphere1" );

		_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, 0.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_attachMaterialToObject( " RedMatte ", " PlaneGround " );

		_addLight( new PointLight( WHITE, 80.f, Vec3f( 0.f, 3.f, -1.f ) ) );*/

		_addMaterial( new MicrofacetMaterial( "Yellow", Vec3f( 0.92f, 1.f, 0.5f ), 0.7f, 0.4f ) );


		_addObject( new Plane( " PlaneFront ", Vec3f( 0.f, 0.f, 12.f ), Vec3f( 0.f, 0.f, -1.f ) ) );


		_attachMaterialToObject( "Yellow", " PlaneFront " );

		_addMaterial( new TransparentMaterial( "Transparent" ) );
		_addMaterial( new MirrorMaterial( "Mirror" ) );
		_addMaterial( new MicrofacetMaterial( "Gold", Vec3f( 0.3f, 0.2f, 0.f ), 0.3f, 0.5f ) );
		loadFileTriangleMesh( "mirror2", DATA_PATH + "mirror2.obj", 4.f, Vec3f( 0.f, 2.f, 8.f ) );
		_addMaterial( new MicrofacetMaterial( "Brown", Vec3f( 0.3f, 0.2f, 0.f ), 0.2f, 0.9f ) );
		_attachMaterialToObject( "Mirror", "mirror2_Box002_meshId0_name" );
		_attachMaterialToObject( "Brown", "mirror2_Box002.001_meshId1_name" );


		_addObject( new Sphere( "Sphere4", Vec3f( 0.f, 2.5f, -9.f ), 1.f ) );
		_attachMaterialToObject( "Mirror", "Sphere4" );
		loadFileTriangleMesh( "glass", DATA_PATH + "glass.obj", 4.f, Vec3f( 6.f, -6.7f, -1.f ) );
		_attachMaterialToObject( "Transparent", "glass_Circle" );

		_addObject( new Hexaedra( "Hexa", Vec3f( 1.f, 8.f, 1.f ), Vec3f( -4.f, 0.f, 1.f ) ) );
		
		_attachMaterialToObject( "Transparent", "Hexa" );

		

		_addObject( new Sphere( "Sphere2", Vec3f( 12.f, 0.f, 8.f ), .7f ) );
		_addObject( new Sphere( "Sphere3", Vec3f( -12.f, 0.f, 8.f ), .7f ) );
		_addMaterial( new LambertMaterial( "grey", YELLOW ) );
		_materialMap[ "grey" ]->setEmissive( YELLOW, 10.f );
		_attachMaterialToObject( "grey", "Sphere2" );
		_attachMaterialToObject( "grey", "Sphere3" );


		_addMaterial( new LambertMaterial( " RedMatte ", Vec3f( 1.f, .3f, .3f ) ) );
		_addMaterial( new PlasticMaterial( " WhiteMatte ", Vec3f( 1.f ), Vec3f( 0.f, 0.f, 1.f ), 0.8f ) );
		_addObject( new Sphere( "Sphere1", Vec3f( 0.f, 0.7f, 0.f ), .7f ) );
		_attachMaterialToObject( " WhiteMatte ", "Sphere1" );

		_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, 0.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_attachMaterialToObject( " RedMatte ", " PlaneGround " );

		_addObject( new Plane( " PlaneRear ", Vec3f( 0.f, 0.f, -10.f ), Vec3f( 0.f, 0.f, 1.f ) ) );
		_attachMaterialToObject( " RedMatte ", " PlaneRear " );

		_addLight( new SphericalLight( WHITE, 100.f, Vec3f( 0.f, 3.f, 1.f ) ) );
		//_addLight( new PointLight( WHITE, 60.f, Vec3f( 0.f, 3.f, -1.f ) ) );
	}

	void Scene::loadFileTriangleMesh( const std::string & p_name, const std::string & p_path, float size, Vec3f position )
	{
		std::cout << "Loading: " << p_path << std::endl;
		Assimp::Importer importer;
		// Read scene and triangulate meshes
		const aiScene * const scene
			= importer.ReadFile( p_path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_GenUVCoords );
		if ( scene == nullptr ) { throw std::runtime_error( "Fail to load file: " + p_path ); }
		uint cptTriangles = 0;
		uint cptVertices  = 0;
		for ( uint m = 0; m < scene->mNumMeshes; ++m )
		{
			const aiMesh * const mesh = scene->mMeshes[ m ];
			if ( mesh == nullptr ) { throw std::runtime_error( "Fail to load file: " + p_path + ": mesh is null" ); }
			const std::string meshName = p_name + "_" + std::string( mesh->mName.C_Str() );
			std::cout << "NAME == " << meshName << std::endl;
			std::cout << "-- Load mesh " << m + 1 << "/" << scene->mNumMeshes << ": " << meshName << std::endl;
			cptTriangles += mesh->mNumFaces;
			cptVertices += mesh->mNumVertices;
			const bool	   hasUV   = mesh->HasTextureCoords( 0 );
			MeshTriangle * triMesh = new MeshTriangle( meshName );
			// Vertices before faces otherwise face normals cannot be computed.
			for ( uint v = 0; v < mesh->mNumVertices; ++v )
			{
				triMesh->addVertex( mesh->mVertices[ v ].x*size+position.x, mesh->mVertices[ v ].y*size+position.y, mesh->mVertices[ v ].z*size+position.z );
				triMesh->addNormal( mesh->mNormals[ v ].x, mesh->mNormals[ v ].y, mesh->mNormals[ v ].z );
				if ( hasUV ) triMesh->addUV( mesh->mTextureCoords[ 0 ][ v ].x, mesh->mTextureCoords[ 0 ][ v ].y );
			}
			for ( uint f = 0; f < mesh->mNumFaces; ++f )
			{
				const aiFace & face = mesh->mFaces[ f ];
				triMesh->addTriangle( face.mIndices[ 0 ], face.mIndices[ 1 ], face.mIndices[ 2 ] );
			}
			triMesh->buildBVH();
			_addObject( triMesh );
			const aiMaterial * const mtl = scene->mMaterials[ mesh->mMaterialIndex ];
			if ( mtl == nullptr )
			{ std::cerr << "Material undefined," << meshName << " assigned to default material" << std::endl; }
			else
			{
				Vec3f	  kd = WHITE;
				Vec3f	  ks = BLACK;
				float	  s	 = 0.f;
				aiColor3D aiKd;
				if ( mtl->Get( AI_MATKEY_COLOR_DIFFUSE, aiKd ) == AI_SUCCESS ) kd = Vec3f( aiKd.r, aiKd.g, aiKd.b );
				aiColor3D aiKs;
				if ( mtl->Get( AI_MATKEY_COLOR_SPECULAR, aiKs ) == AI_SUCCESS ) ks = Vec3f( aiKs.r, aiKs.g, aiKs.b );
				float aiS = 0.f;
				if ( mtl->Get( AI_MATKEY_SHININESS, aiS ) == AI_SUCCESS ) s = aiS;
				aiString mtlName;
				mtl->Get( AI_MATKEY_NAME, mtlName );
				//_addMaterial( new PlasticMaterial( std::string( mtlName.C_Str() ), kd, ks, s ) );
				//_attachMaterialToObject( mtlName.C_Str(), meshName );
			}
			std::cout << "-- [DONE] " << triMesh->getNbTriangles() << " triangles, " << triMesh->getNbVertices()
					  << " vertices." << std::endl;
		}
		std::cout << "[DONE] " << scene->mNumMeshes << " meshes, " << cptTriangles << " triangles, " << cptVertices
				  << " vertices." << std::endl;
		
	}

	bool Scene::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		float tMax = p_tMax;
		bool  hit  = false;
		for ( const ObjectMapPair & object : _objectMap )
		{
			if ( object.second->intersect( p_ray, p_tMin, tMax, p_hitRecord ) )
			{
				tMax = p_hitRecord._distance; // update tMax to conserve the nearest hit
				hit	 = true;
			}
		}
		return hit;
	}

	bool Scene::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax) const
	{
		float tMax = p_tMax;
		bool  hit  = false;
		for ( const ObjectMapPair & object : _objectMap )
		{
			if ( object.second->intersectAny( p_ray, p_tMin, tMax) )
			{
				hit	 = true;
			}
		}
		return hit;
	}

	void Scene::_addObject( BaseObject * p_object )
	{
		const std::string & name = p_object->getName();
		if ( _objectMap.find( name ) != _objectMap.end() )
		{
			std::cout << "[Scene::addObject] Object \'" << name << "\' already exists" << std::endl;
			delete p_object;
		}
		else
		{
			_objectMap[ name ] = p_object;
			_objectMap[ name ]->setMaterial( _materialMap[ "default" ] );
		}
	}

	void Scene::_addMaterial( BaseMaterial * p_material )
	{
		const std::string & name = p_material->getName();
		if ( _materialMap.find( name ) != _materialMap.end() )
		{
			std::cout << "[Scene::addMaterial] Material \'" << name << "\' already exists" << std::endl;
			delete p_material;
		}
		else
		{
			_materialMap[ name ] = p_material;
		}
	}

	void Scene::_addLight( BaseLight * p_light ) { _lightList.emplace_back( p_light ); }

	void Scene::_attachMaterialToObject( const std::string & p_materialName, const std::string & p_objectName )
	{
		if ( _objectMap.find( p_objectName ) == _objectMap.end() )
		{
			std::cout << "[Scene::attachMaterialToObject] Object \'" << p_objectName << "\' does not exist"
					  << std::endl;
		}
		else if ( _materialMap.find( p_materialName ) == _materialMap.end() )
		{
			std::cout << "[Scene::attachMaterialToObject] Material \'" << p_materialName << "\' does not exist, "
					  << "object \'" << p_objectName << "\' keeps its material \'"
					  << _objectMap[ p_objectName ]->getMaterial()->getName() << "\'" << std::endl;
		}
		else
		{
			_objectMap[ p_objectName ]->setMaterial( _materialMap[ p_materialName ] );
		}
	}

} // namespace RT_ISICG

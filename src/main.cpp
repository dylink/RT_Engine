#include "cameras/perspective_camera.hpp"
#include "defines.hpp"
#include "renderer.hpp"

namespace RT_ISICG
{ 
	int main( int argc, char ** argv )
	{
		const int imgWidth	= 1920;
		const int imgHeight = 1080;

		// Create a texture to render the scene.
		Texture img = Texture( imgWidth, imgHeight );

		// Create and init scene.
		Scene scene;
		scene.init();

		// Create a perspective camera.
		//PerspectiveCamera camera( float( imgWidth ) / imgHeight );
		PerspectiveCamera camera(
			Vec3f( 0, 2, -6 ), Vec3f( 0, 2, 1 ), Vec3f( 0., 1., 0. ), 60.f, float( imgWidth ) / imgHeight );

		//PerspectiveCamera camera(Vec3f( -0.9, 0.4, 0.9 ), Vec3f( -0.87, 0.4, 1 ), Vec3f( 0., 1., 0. ), 60.f, float( imgWidth ) / imgHeight );

		// Create and setup the renderer.
		Renderer renderer;
		renderer.setIntegrator( IntegratorType::PATH_TRACER);
		renderer.setBackgroundColor( Vec3f( 0.00, 0.40, 0.60 ) );
		renderer.setNbPixelSamples( 256 );

		// Launch rendering.
		std::cout << "Rendering..." << std::endl;
		std::cout << "- Image size: " << imgWidth << "x" << imgHeight << std::endl;

		float renderingTime = renderer.renderImage( scene, &camera, img );

		std::cout << "-> Done in " << renderingTime << "ms" << std::endl;

		// Save rendered image.
		const std::string imgName = "image.jpg";
		img.saveJPG( RESULTS_PATH + imgName );

		return EXIT_SUCCESS;
	}
} // namespace RT_ISICG

int main( int argc, char ** argv )
{
	try
	{
		return RT_ISICG::main( argc, argv );
	}
	catch ( const std::exception & e )
	{
		std::cerr << "Exception caught:" << std::endl << e.what() << std::endl;
	}
}

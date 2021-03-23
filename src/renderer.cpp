#include "renderer.hpp"
#include "integrators/ray_cast_integrator.hpp"
#include "integrators/direct_light_integrator.hpp"
#include "integrators/whitted_integrator.hpp"
#include "utils/console_progress_bar.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	Renderer::Renderer() { _integrator = new RayCastIntegrator(); }

	void Renderer::setIntegrator( const IntegratorType p_integratorType )
	{
		if ( _integrator != nullptr ) { delete _integrator; }

		switch ( p_integratorType )
		{
		case IntegratorType::RAY_CAST:
		default:
		{
			_integrator = new RayCastIntegrator();
			break;
		}
		case IntegratorType::DIRECT_LIGHT:
			_integrator = new DirectLightIntegrator();
			break;
		case IntegratorType::WHITTED: 
			_integrator = new WhittedIntegrator(); 
			break;
		}
	}

	void Renderer::setBackgroundColor( const Vec3f & p_color )
	{
		if ( _integrator == nullptr ) { std::cout << "[Renderer::setBackgroundColor] Integrator is null" << std::endl; }
		else
		{
			_integrator->setBackgroundColor( p_color );
		}
	}

	float Renderer::renderImage( const Scene & p_scene, const BaseCamera * p_camera, Texture & p_texture )
	{
		const int width	 = p_texture.getWidth();
		const int height = p_texture.getHeight();

		Chrono			   chrono;
		ConsoleProgressBar progressBar;

		progressBar.start( height, 50 );
		chrono.start();
		
		for ( int j = 0; j < height; j++ )
		{
			#pragma omp parallel for
			for ( int i = 0; i < width; i++ )
			{

				if (_nbPixelSamples > 1) {
					Vec3f color( 0.f, 0.f, 0.f );
					for ( int g = 0; g < _nbPixelSamples; g++ )
					{
						float x	  = ( (float)i + randomFloat() ) / ( width - 1 );
						float y	  = ( (float)j + randomFloat() ) / ( height - 1 );
						Ray	  ray = p_camera->generateRay( x, y );
						color += _integrator->Li( p_scene, ray, 0, 50000 );
					}
					color /= _nbPixelSamples;
					p_texture.setPixel( i, j, glm::clamp(color, 0.f, 1.f) );
				}
				else
				{
					Ray ray = p_camera->generateRay( (float)i / width, (float)j / height );
					p_texture.setPixel( i, j, glm::clamp(_integrator->Li( p_scene, ray, 0, 50000 ), 0.f, 1.f) );
				}
				

				
				//Ray	ray = p_camera->generateRay( (float)i / width, (float)j / height );
				//p_texture.setPixel( i, j, _integrator->Li( p_scene, ray, 0, 50000 ) );
				//_integrator->Li( p_scene, ray, 0, 50000);
				//Vec3f color( (float)i / width, (float)j / height, 0. );
				
				//p_texture.setPixel( i, j, _integrator->Li( p_scene, ray, 0, 50000));
				/// TODO !
			}
			progressBar.next();
		}

		chrono.stop();
		progressBar.stop();

		return chrono.elapsedTime();
	}
} // namespace RT_ISICG

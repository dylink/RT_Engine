#include "perspective_camera.hpp"
#include <glm/gtx/string_cast.hpp>

namespace RT_ISICG
{
	PerspectiveCamera::PerspectiveCamera( const float p_aspectRatio ) : _aspectRatio( p_aspectRatio )
	{
		_updateViewport();
	}

	PerspectiveCamera::PerspectiveCamera( const Vec3f & p_position,
										  const Vec3f & p_lookAt,
										  const Vec3f & p_up,
										  const float	p_fovy,
										  const float	p_aspectRatio )
		: BaseCamera( p_position ), _fovy( p_fovy ), _aspectRatio( p_aspectRatio )
	{	
		/// TODO ! _u ? _v ? _w ?

		_w = glm::normalize( p_position - p_lookAt );
		_u = glm::normalize( -cross( _w, p_up ) );
		_v = glm::normalize( cross( _u, _w ) );
		printf( "Vec (%f, %f, %f)\n", _w.x, _w.y, _w.z );
		_updateViewport();
	}

	void PerspectiveCamera::_updateViewport()
	{
		float h = tan( glm::radians( _fovy / 2 ) ) * _focalDistance;
		_viewportV = _v * (h * 2);
		float l	   = ( h * 2 ) * _aspectRatio;
		_viewportU = _u * l;
		_viewportTopLeftCorner = -_w * _focalDistance + _viewportV * .5f - _viewportU * .5f;
		printf( "(%f, %f, %f)\n", _viewportTopLeftCorner.x, _viewportTopLeftCorner.y, _viewportTopLeftCorner.z );
		/// TODO ! _viewportTopLeftCorner ?	_viewportU ? _viewportV ?
	}

} // namespace RT_ISICG

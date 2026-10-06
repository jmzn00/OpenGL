#ifndef RENDER_QUEUE_H
#define RENDER_QUEUE_H

#include <eng/camera/camera.h>
#include<vector>
#include <eng/renderer/mesh.h>
#include <eng/graphics/graphics_api.h>

namespace eng
{
	struct RenderCommand
	{
		Mesh* mesh = nullptr;
	};
	struct CameraData
	{
		// viewMatrix
		// projectionMatrix
	};
	class RenderQueue
	{
	public:
		void Submit(const RenderCommand& cmd);
		void Draw(GraphicsAPI& gapi, const Camera& camera);	
	};
}
#endif // !RENDER_QUEUE_H
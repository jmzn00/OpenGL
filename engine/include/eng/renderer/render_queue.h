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
	struct RenderQueue
	{
		std::vector<DrawCommand> opaque;
		std::vector<DrawCommand> masked;
		std::vector<DrawCommand> transparent;

		void Clear()
		{
			opaque.clear();
			masked.clear();
			transparent.clear();
		}
		void Submit(const DrawCommand& cmd)
		{
			switch (cmd.material->GetAlphaMode())
			{
			case AlphaMode::Opaque:
				opaque.push_back(cmd);
				break;
			case AlphaMode::Mask:
				masked.push_back(cmd);
				break;
			case AlphaMode::Blend:
				transparent.push_back(cmd);
				break;
			}
		}
	};
}
#endif // !RENDER_QUEUE_H
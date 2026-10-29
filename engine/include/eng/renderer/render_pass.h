#ifndef RENDER_PASS_H
#define RENDER_PASS_H
#include <vector>
#include <string>
namespace eng
{
	class Camera;
	class GraphicsAPI;
	struct DrawCommand;
	struct RenderLight;	

	struct RenderContext
	{
		GraphicsAPI& graphicsAPI;
		Camera& camera;
		std::vector<DrawCommand>& commands;

		std::vector<RenderLight>& pointLights;
		std::vector<RenderLight>& directionalLights;
		std::vector<RenderLight>& spotLights;
	};
	class RenderPass
	{
	public:
		virtual ~RenderPass() = default;

		virtual void Init() {}
		virtual void Execute(RenderContext& context) = 0;
		virtual const char* Name() const = 0;
	};
}
#endif // !RENDER_PASS_H

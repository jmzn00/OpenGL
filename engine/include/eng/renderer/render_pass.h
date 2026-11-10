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
	struct RenderQueue;
	class Framebuffer;
	class CubemapTexture;

	enum class RenderStage : std::uint8_t
	{
		PreGeometry,
		Opaque,
		Masked,
		Transparent,
		PostProcess,
		PostPostProcess,
	};

	struct RenderContext
	{
		GraphicsAPI& graphicsAPI;
		Camera& camera;

		RenderQueue& renderQueue;

		Framebuffer& sceneTarget;
		Framebuffer& outputTarget;
		CubemapTexture& skybox;

		std::vector<RenderLight>& pointLights;
		std::vector<RenderLight>& directionalLights;
		std::vector<RenderLight>& spotLights;
	};
	class RenderPass
	{
	public:
		virtual ~RenderPass() = default;

		virtual RenderStage Stage() const = 0;
		virtual void Init() {}
		virtual void Execute(RenderContext& context) = 0;
		virtual const char* Name() const = 0;
	};
}
#endif // !RENDER_PASS_H

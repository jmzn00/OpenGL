#ifndef RENDER_QUEUE_H
#define RENDER_QUEUE_H
#include<vector>

namespace eng
{
	class Mesh;
	class Material;
	class GraphicsAPI;

	struct RenderCommand
	{
		Mesh* mesh = nullptr;
		Material* material = nullptr;
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
		void Draw(GraphicsAPI& gapi, const CameraData& cameraData);
	private:
		std::vector<RenderCommand> m_commands;
	};
}
#endif // !RENDER_QUEUE_H
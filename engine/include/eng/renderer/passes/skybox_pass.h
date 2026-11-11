#ifndef SKYBOX_PASS_H
#define SKYBOX_PASS_H
#include <eng/renderer/render_pass.h>
#include <eng/graphics/texture/cubemap_texture.h>
#include <eng/graphics/shader_program.h>
#include <eng/renderer/mesh.h>
#include <eng/renderer/mesh_library.h>
#include <eng/graphics/graphics_api.h>
#include <eng/camera/camera.h>
#include <eng/profiler/profiler.h>
#include <memory>
#include <vector>
#include <string>

#include <eng/asset/asset_manager.h>

namespace eng
{
	class SkyboxPass : public RenderPass
	{
	public:
		const char* Name() const override
		{
			return "Skybox";
		}
		RenderStage Stage() const override
		{
			return RenderStage::PreGeometry;
		}
		void Init() override
		{
			m_shader = std::make_unique<ShaderProgram>(ENGINE_ASSET_DIR"/shaders/skybox/skybox.vert",
				ENGINE_ASSET_DIR"/shaders/skybox/skybox.frag");

			m_mesh = AssetManager::Get().Meshes().Create("primitives::cube");
		}
		void Execute(RenderContext& context) override
		{			
			glDepthMask(GL_FALSE);
			glDepthFunc(GL_LEQUAL);

			context.graphicsAPI.BindShaderProgram(m_shader.get());
			glm::mat4 view = glm::mat4(glm::mat3(context.camera.GetView()));

			m_shader->SetMat4("view", view);
			m_shader->SetMat4("projection", context.camera.GetProjection());

			constexpr int skyboxUnit = 10;
			m_shader->SetInt("skybox", skyboxUnit);
			context.skybox.Bind(skyboxUnit);

			m_mesh->Bind();
			m_mesh->Draw();

			glDepthFunc(GL_LESS);
			glDepthMask(GL_TRUE);

			Profiler::Get().IncrementDrawCalls();
			Profiler::Get().AddTriangles(static_cast<uint32_t>(m_mesh->GetVertexCount()));
		}
	private:
		std::unique_ptr<ShaderProgram> m_shader;
		std::shared_ptr<Mesh> m_mesh;
	};
}
#endif // !SKYBOX_PASS_H

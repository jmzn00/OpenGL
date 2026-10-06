#ifndef RENDERER_H
#define RENDERER_H

#include <eng/debug/assert.h>
#include <eng/graphics/graphics_api.h>
#include <eng/renderer/mesh.h>
#include <eng/camera/camera.h>
#include <eng/graphics/shader_program.h>
#include <eng/entity/components.h>

#include <vector>

namespace eng
{
	struct DrawCommand
	{
		Mesh* mesh;
		ShaderProgram* shader;
		TransformComponent* transform;
	};
	class Renderer
	{
	public:
		Renderer(GraphicsAPI& gapi)
			: m_graphicsAPI { gapi }
		{
			ENG_ASSERT(m_instance == nullptr, "Renderer instance exists");
			m_instance = this;
		}
		static Renderer& Get() { return *m_instance; }
		void Submit(const DrawCommand& cmd)
		{
			m_commands.push_back(cmd);
		}
		void BeginScene(Camera& camera)
		{
			m_currentCamera = &camera;
		}
		void EndScene()
		{
			m_currentCamera = nullptr;
		}
		void Render()
		{
			ENG_ASSERT(m_currentCamera != nullptr,
				"No active scene");

			for (auto& cmd : m_commands)
			{
				ENG_ASSERT(cmd.mesh != nullptr, "MESH NULL");
				ENG_ASSERT(cmd.shader != nullptr, "SHADER NULL");

				m_graphicsAPI.BindShaderProgram(cmd.shader);

				cmd.shader->SetMat4(
					"view",
					m_currentCamera->GetView());

				cmd.shader->SetMat4(
					"projection",
					m_currentCamera->GetProjection());

				cmd.shader->SetVec3(
					"viewPos",
					m_currentCamera->GetPosition());

				cmd.shader->SetMat4(
					"model",
					cmd.transform->GetTransform());


				cmd.mesh->Bind();
				cmd.mesh->Draw();
			}
			m_commands.clear();
		}
	private:
		std::vector<DrawCommand> m_commands;
		Camera* m_currentCamera = nullptr;
		GraphicsAPI& m_graphicsAPI;
		inline static Renderer* m_instance = nullptr;
	};
}
#endif // !RENDERER_H

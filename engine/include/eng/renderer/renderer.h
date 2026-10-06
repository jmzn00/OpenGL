#ifndef RENDERER_H
#define RENDERER_H

#include <eng/debug/assert.h>
#include <eng/graphics/graphics_api.h>
#include <eng/renderer/mesh.h>
#include <eng/camera/camera.h>
#include <eng/graphics/shader_program.h>
#include <eng/entity/components.h>
#include <eng/graphics/material/material.h>
#include <eng/entity/entity.h>

#include <vector>

namespace eng
{
	struct DrawCommand
	{
		Mesh* mesh;
		Material* material;
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

			m_commands.clear();
			m_lights.clear();
		}
		void EndScene()
		{
			m_currentCamera = nullptr;
		}
		void SubmitLight(const Entity& lightEntity)
		{
			LightComponent& light = lightEntity.GetComponent<LightComponent>();
			const TransformComponent& transform{ lightEntity.Transform() };
			m_lights.push_back({ 
				transform.Translation,
				light.ambient,
				light.diffuse,
				light.specular
				});
		}
		void Render()
		{
			ENG_ASSERT(m_currentCamera != nullptr,
				"No active scene");

			for (auto& cmd : m_commands)
			{
				const ShaderProgram& shader{ cmd.material->GetShaderProgram() };

				ENG_ASSERT(cmd.mesh != nullptr, "MESH NULL");												

				cmd.material->Bind(m_graphicsAPI);

				shader.SetMat4(
					"view",
					m_currentCamera->GetView());

				shader.SetMat4(
					"projection",
					m_currentCamera->GetProjection());

				shader.SetVec3(
					"viewPos",
					m_currentCamera->GetPosition());

				shader.SetMat4(
					"model",
					cmd.transform->GetTransform());

				if (!m_lights.empty())
				{
					shader.SetLight(m_lights[0]);
				}


				cmd.mesh->Bind();
				cmd.mesh->Draw();
			}
		}
	private:
		std::vector<DrawCommand> m_commands;
		std::vector<RenderLight> m_lights;

		Camera* m_currentCamera = nullptr;
		GraphicsAPI& m_graphicsAPI;
		inline static Renderer* m_instance = nullptr;
	};
}
#endif // !RENDERER_H

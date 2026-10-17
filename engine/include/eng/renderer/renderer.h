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
#include <eng/profiler/profiler.h>

#include <vector>
#include <iostream>

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

			m_pointLights.clear();
			m_directionalLights.clear();
			m_spotLights.clear();
		}
		void EndScene()
		{
			m_currentCamera = nullptr;
		}
		void SubmitLight(const Entity& lightEntity)
		{
			LightComponent& light = lightEntity.GetComponent<LightComponent>();
			const TransformComponent& transform{ lightEntity.Transform() };

			RenderLight renderLight{
				light.type,
				transform.Translation,
				transform.GetForward(),
				light.ambient,
				light.diffuse,
				light.specular,
				light.constant,
				light.linear,
				light.quadratic,
				light.innerCutoff,
				light.outerCutoff
			};

			switch (renderLight.type)
			{
			case LightType::Point:
				m_pointLights.push_back(renderLight);
				break;
			case LightType::Direction:
				m_directionalLights.push_back(renderLight);
				break;
			case LightType::Spot:
				m_spotLights.push_back(renderLight);
				break;
			}
		}		
		void RenderLights(const ShaderProgram& shader)
		{
			if (!m_pointLights.empty())
			{
				shader.SetPointLights(m_pointLights);
			}
			if (!m_directionalLights.empty())
			{
				shader.SetDirectionalLights(m_directionalLights);
			}
			if (!m_spotLights.empty())
			{
				shader.SetSpotLights(m_spotLights);
			}
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
				
				RenderLights(shader);

				cmd.mesh->Bind();
				cmd.mesh->Draw();

				Profiler::Get().IncrementDrawCalls();
				Profiler::Get().AddTriangles(cmd.mesh->GetVertexCount());
			}
		}
	private:
		std::vector<DrawCommand> m_commands;
		std::vector<RenderLight> m_lights;
		
		std::vector<RenderLight> m_pointLights;
		std::vector<RenderLight> m_directionalLights;
		std::vector<RenderLight> m_spotLights;

		Camera* m_currentCamera = nullptr;
		GraphicsAPI& m_graphicsAPI;
		inline static Renderer* m_instance = nullptr;
	};
}
#endif // !RENDERER_H

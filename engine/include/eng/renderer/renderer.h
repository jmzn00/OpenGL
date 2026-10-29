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
#include <eng/renderer/render_pass.h>
#include <eng/renderer/draw_command.h>

#include <eng/renderer/passes/geometry_pass.h>

#include <vector>
#include <iostream>
#include <memory>
#include <utility>

namespace eng
{
	
	class Renderer
	{		
	public:
		Renderer(GraphicsAPI& gapi)
			: m_graphicsAPI { gapi }
		{
			ENG_ASSERT(m_instance == nullptr, "Renderer instance exists");
			m_instance = this;

			AddPass<GeometryPass>();			
		}
		static Renderer& Get() { return *m_instance; }

		template<typename T, typename... Args>
		T& AddPass(Args&&... args)
		{
			static_assert(
				std::is_base_of_v<RenderPass, T>,
				"T must derive from RenderPass");

			auto pass = std::make_unique<T>(
				std::forward<Args>(args)...);

			pass->Init();

			T& ref = *pass;

			m_passes.push_back(std::move(pass));

			return ref;
		}
		
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
		void Render()
		{
			ENG_ASSERT(m_currentCamera != nullptr,
				"No active scene");

			RenderContext context
			{
				m_graphicsAPI,
				*m_currentCamera,
				m_commands,
				m_pointLights,
				m_directionalLights,
				m_spotLights
			};

			for (auto& pass : m_passes)
			{
				pass->Execute(context);
			}
		}
	private:
		std::vector<DrawCommand> m_commands;
		
		std::vector<RenderLight> m_pointLights;
		std::vector<RenderLight> m_directionalLights;
		std::vector<RenderLight> m_spotLights;

		Camera* m_currentCamera = nullptr;
		GraphicsAPI& m_graphicsAPI;
		inline static Renderer* m_instance = nullptr;

		std::vector<std::unique_ptr<RenderPass>> m_passes;
	};
}
#endif // !RENDERER_H

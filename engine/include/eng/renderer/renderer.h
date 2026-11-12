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
#include <eng/graphics/framebuffer.h>

#include <eng/renderer/passes/opaque_pass.h>
#include <eng/renderer/passes/transparent_pass.h>
#include <eng/renderer/passes/masked_pass.h>
#include <eng/renderer/passes/post_process_pass.h>
#include <eng/renderer/passes/skybox_pass.h>
#include <eng/renderer/passes/debug_pass.h>

#include <eng/graphics/texture/cubemap_texture.h>

#include <vector>
#include <string>
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

			AddPass<SkyboxPass>();
			AddPass<OpaquePass>();
			AddPass<TransparentPass>();
			AddPass<MaskedPass>();
			AddPass<PostProcessPass>();
			//AddPass<DebugPass>();

			std::vector<std::string> faces{
			ENGINE_ASSET_DIR"/textures/skybox/right.jpg", // right -
			ENGINE_ASSET_DIR"/textures/skybox/left.jpg", // left - 
			ENGINE_ASSET_DIR"/textures/skybox/top.jpg", // top
			ENGINE_ASSET_DIR"/textures/skybox/bottom.jpg", // bottom
			ENGINE_ASSET_DIR"/textures/skybox/front.jpg", // front
			ENGINE_ASSET_DIR"/textures/skybox/back.jpg" }; // back

			m_skybox = std::make_unique<CubemapTexture>(faces);

			glGenBuffers(1, &m_cameraUbo);
			glBindBuffer(GL_UNIFORM_BUFFER, m_cameraUbo);
			glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);
			glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_cameraUbo);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
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

			auto it = std::find_if(
				m_passes.begin(),
				m_passes.end(),
				[&](const auto& other)
				{
					return static_cast<int>(pass->Stage()) <
						static_cast<int>(other->Stage());
				});

			m_passes.insert(it, std::move(pass));

			return ref;
		}
		template<typename T>
		bool HasPass()
		{
			static_assert(
				std::is_base_of_v<RenderPass, T>,
				"T must derive from RenderPass");

			return std::any_of(
				m_passes.begin(),
				m_passes.end(),
				[](const auto& pass)
				{
					return dynamic_cast<T*>(pass.get()) != nullptr;
				});
		}
		template<typename T>
		T* GetPass()
		{
			static_assert(std::is_base_of_v<RenderPass, T>);

			for (auto& pass : m_passes)
			{
				if (auto* p = dynamic_cast<T*>(pass.get()))
					return p;
			}

			return nullptr;
		}
		
		void Submit(const DrawCommand& cmd)
		{
			m_commands.push_back(cmd);
		}
		void BeginScene(Camera& camera)
		{
			m_currentCamera = &camera;

			m_renderQueue.Clear();
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
		void Render(Framebuffer& sceneTarget, Framebuffer& outputTarget)
		{
			ENG_ASSERT(m_currentCamera != nullptr,
				"No active scene");

			BuildRenderQueue(*m_currentCamera);
			constexpr int skyboxUnit = 10;

			RenderContext context
			{
				m_graphicsAPI,
				*m_currentCamera,
				m_renderQueue,
				sceneTarget,
				outputTarget,
				*m_skybox,
				skyboxUnit,
				m_pointLights,
				m_directionalLights,
				m_spotLights
			};
			
			Framebuffer::Bind(sceneTarget);
			m_graphicsAPI.ClearBuffers();

			glBindBuffer(GL_UNIFORM_BUFFER, m_cameraUbo);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(m_currentCamera->GetProjection()));
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4),sizeof(glm::mat4), glm::value_ptr(m_currentCamera->GetView()));
							
			m_skybox->Bind(skyboxUnit);

			for (auto& pass : m_passes)
			{
				pass->Execute(context);
			}
			Framebuffer::BindDefault();
		}		
	private:
		void BuildRenderQueue(Camera& camera)
		{
			m_renderQueue.Clear();

			m_renderQueue.commands = m_commands;
			for (const DrawCommand& cmd : m_commands)
			{
				ENG_ASSERT(cmd.material != nullptr, "MATERIAL NULL");

				switch (cmd.material->GetAlphaMode())
				{
					case AlphaMode::Opaque:
						m_renderQueue.opaque.push_back(cmd);
						break;
					case AlphaMode::Mask:
						m_renderQueue.masked.push_back(cmd);
						break;
					case AlphaMode::Blend:
						m_renderQueue.transparent.push_back(cmd);
						break;
				}
			}
			std::sort(
				m_renderQueue.opaque.begin(),
				m_renderQueue.opaque.end(),
				[&](const DrawCommand& a, const DrawCommand& b)
				{
					const glm::vec4 aView =
						camera.GetView() *
						glm::vec4(a.transform->Translation, 1.0f);
					const glm::vec4 bView =
						camera.GetView() *
						glm::vec4(b.transform->Translation, 1.0f);

					return aView.z < bView.z;
				}
			);
			std::sort(
				m_renderQueue.transparent.begin(),
				m_renderQueue.transparent.end(),
				[&](const DrawCommand& a, const DrawCommand& b)
				{
					const glm::vec4 aView =
						camera.GetView() *
						glm::vec4(a.transform->Translation, 1.0f);
					const glm::vec4 bView =
						camera.GetView() *
						glm::vec4(b.transform->Translation, 1.0f);

					return aView.z < bView.z;
				}
			);
		}
		inline static Renderer* m_instance = nullptr;

		std::vector<std::unique_ptr<RenderPass>> m_passes;

		std::vector<DrawCommand> m_commands;		
		std::vector<RenderLight> m_pointLights;
		std::vector<RenderLight> m_directionalLights;
		std::vector<RenderLight> m_spotLights;
		std::unique_ptr<CubemapTexture> m_skybox;

		Camera* m_currentCamera = nullptr;
		GraphicsAPI& m_graphicsAPI;		

		RenderQueue m_renderQueue;

		GLuint m_cameraUbo{0};
	};
}
#endif // !RENDERER_H

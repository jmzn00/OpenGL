#include "editor_layer.h"
#include <eng/core/application.h>
#include <eng/math/math.h>

namespace eng
{
	EditorLayer::EditorLayer(EngineContext& ctx)
		: Layer("EditorLayer"), m_engineContext{ctx}
	{
		ctx.GetLogger().Info("[EditorLayer] Initialized");
		m_input = &ctx.GetInput();
	}
	void EditorLayer::OnAttach()
	{	
		Window& window = m_engineContext.GetWindow();
		m_editorCamera.SetViewportSize(window.GetWidth(), window.GetHeight());	

		m_editorCamera.Pitch = -90.0f;
		m_editorCamera.Yaw = 0.0f;

		m_engineContext.WindowResizeEvents().Subscribe(
			[this]
			(const WindowResizeEvent & e)
			{
				m_editorCamera.SetViewportSize(
					e.Width,
					e.Height);
			});

		m_currentScene = std::make_unique<Scene>(m_engineContext, "Test Scene");

		m_shaderLibrary.Init();

		m_commands.RegisterAll(m_engineContext, *m_currentScene);
		m_commandContext = std::make_unique<CommandContext>(m_engineContext.GetLogger(), *m_currentScene);
		m_commandExecutor = std::make_unique<CommandExecutor>(m_commands, *m_commandContext);

		m_components.push_back(std::make_unique<Console>(*m_commandExecutor));
		m_components.push_back(std::make_unique<Inspector>(*m_currentScene, m_editorContext, *m_commandExecutor));
		m_components.push_back(std::make_unique<PropertiesPanel>(*m_currentScene, m_editorContext));

		for (auto& component : m_components)
		{
			if (!component->Init(m_engineContext))
			{
				m_engineContext.GetLogger().Error("[Editor] Component failed to init");
			}
		}		
	}
	void EditorLayer::OnDetach()
	{
		for (auto& component : m_components)
		{
			component->Destroy();
		}
		m_components.clear();
	}
	void EditorLayer::Update(float dt)
	{
		for (auto& component : m_components)
		{
			component->Update(dt);
		}	

		//const float sensitivity = 0.1;
		//glm::vec2 mouseDelta = m_input->MouseDelta();
		//m_editorCamera.Yaw += mouseDelta.x * sensitivity;
		//m_editorCamera.Pitch -= mouseDelta.y * sensitivity;
		//m_editorCamera.Pitch = math::clamp(m_editorCamera.Pitch, -89.0f, 89.0f);
		//
		//
		//m_editorCamera.Look(m_editorCamera.Pitch, m_editorCamera.Yaw);		

		float cameraSpeed = 1 * dt;
		glm::vec3 cameraPos = m_editorCamera.GetPosition();

		if (m_input->IsKeyPressed(GLFW_KEY_W))
			cameraPos += cameraSpeed * m_editorCamera.GetFlatForward();
		if (m_input->IsKeyPressed(GLFW_KEY_S))
			cameraPos -= cameraSpeed * m_editorCamera.GetFlatForward();
		if (m_input->IsKeyPressed(GLFW_KEY_D))
			cameraPos += cameraSpeed * m_editorCamera.GetRight();
		if (m_input->IsKeyPressed(GLFW_KEY_A))
			cameraPos -= cameraSpeed * m_editorCamera.GetRight();
		m_editorCamera.MoveTo(cameraPos);

		m_currentScene->Update(dt);
		m_currentScene->Render(m_editorCamera);
	}
	void EditorLayer::OnImGuiRender()
	{
		for (auto& component : m_components)
		{
			component->Draw();
		}
	}	
}
#include "editor_layer.h"
#include <eng/core/application.h>
#include <eng/math/math.h>
#include <eng/renderer/renderer.h>

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
		m_components.push_back(std::make_unique<Toolbar>(*m_commandExecutor));
		m_components.push_back(std::make_unique<ProfilerPanel>());

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
	void EditorLayer::BuildDefaultDockLayout(ImGuiID dockspaceId, const ImVec2& dockspaceSize)
	{
		ImGui::DockBuilderRemoveNode(dockspaceId);

		ImGui::DockBuilderAddNode(
			dockspaceId,
			ImGuiDockNodeFlags_DockSpace
		);
		ImGui::DockBuilderSetNodeSize(
			dockspaceId,
			dockspaceSize
		);

		ImGuiID mainNode = dockspaceId;
		ImGuiID leftNode = 0;
		ImGuiID rightNode = 0;
		ImGuiID bottomNode = 0;

		ImGui::DockBuilderSplitNode(
			mainNode,
			ImGuiDir_Left,
			0.20f,
			&leftNode,
			&mainNode
		);
		ImGui::DockBuilderSplitNode(
			mainNode,
			ImGuiDir_Right,
			0.25f,
			&rightNode,
			&mainNode
		);
		ImGui::DockBuilderSplitNode(
			mainNode,
			ImGuiDir_Down,
			0.25f,
			&bottomNode,
			&mainNode
		);

		ImGui::DockBuilderDockWindow("Inspector", leftNode);
		ImGui::DockBuilderDockWindow("Properties", rightNode);
		ImGui::DockBuilderDockWindow("Profiler", rightNode);
		ImGui::DockBuilderDockWindow("Console", bottomNode);

		ImGui::DockBuilderFinish(dockspaceId);
	}
	void EditorLayer::OnImGuiRender()
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		const float toolbarHeight = 48.0f;

		ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + toolbarHeight));
		ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y - toolbarHeight));
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGuiWindowFlags hostFlags =
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoBringToFrontOnFocus |
			ImGuiWindowFlags_NoNavFocus |
			ImGuiWindowFlags_NoDocking |
			ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

		ImGui::Begin("EditorDockspaceHost", nullptr, hostFlags);

		ImGui::PopStyleVar(2);
		
		ImGuiID dockspaceId = ImGui::GetID("EditorDockspace");
		ImVec2 dockspaceSize = ImGui::GetContentRegionAvail();

		ImGui::DockSpace(
			dockspaceId,
			ImVec2(0.0f, 0.0f),
			ImGuiDockNodeFlags_PassthruCentralNode
		);

		if (!m_dockLayoutBuilt)
		{
			BuildDefaultDockLayout(dockspaceId, dockspaceSize);
			m_dockLayoutBuilt = true;
		}

		ImGui::End();

		for (auto& component : m_components)
		{
			component->Draw();
		}		
	}	
}
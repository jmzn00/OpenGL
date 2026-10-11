#include "editor_layer.h"

namespace eng
{
	EditorLayer::EditorLayer(EngineContext& ctx, EditorContext& editorContext)
		: Layer("EditorLayer"), m_engineContext{ctx}, m_editorContext{editorContext}
	{
		ctx.GetLogger().Info("[EditorLayer] Initialized");
	}
	void EditorLayer::OnAttach()
	{	
		CommandExecutor& commandExecutor = m_editorContext.GetCommandExecutor();
		Scene& currentScene = m_editorContext.GetCurrentScene();

		m_components.push_back(std::make_unique<Console>(commandExecutor));
		m_components.push_back(std::make_unique<Inspector>(currentScene, m_editorContext, commandExecutor));
		m_components.push_back(std::make_unique<PropertiesPanel>(currentScene, m_editorContext));
		m_components.push_back(std::make_unique<Toolbar>(commandExecutor));
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
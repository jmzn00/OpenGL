#include "toolbar.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <filesystem>
namespace
{
	const std::filesystem::path ScenesDirectory =
		std::filesystem::path{ ENGINE_ASSET_DIR } / "scenes";

	std::filesystem::path SceneFilePath(const std::string& name)
	{
		return ScenesDirectory / (name + ".scene.json");
	}
}
namespace eng
{
	Toolbar::Toolbar(CommandExecutor& commandExecutor, SceneSerializer& sceneSerializer, Scene& scene)
		: m_commandExecutor{commandExecutor}, m_sceneSerialzier {sceneSerializer}, m_scene{scene}
	{
	}
	bool Toolbar::Init(EngineContext& engineContext)
	{
		m_logger = &engineContext.GetLogger();

		return true;
	}
	void Toolbar::Destroy()
	{
	}
	void Toolbar::Draw()
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();

		const float toolbarHeight = 48.0f;

		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, toolbarHeight));

		ImGuiWindowFlags flags =
			ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoDocking;

		ImGui::Begin("Toolbar", nullptr, flags);

		if (ImGui::Button("File"))
		{	
			ImGui::OpenPopup("FileOpenPopup");
		}
		if (ImGui::BeginPopup("FileOpenPopup"))
		{
			if (ImGui::BeginMenu("Scene"))
			{
				if (ImGui::MenuItem("New"))
					m_showNewScenePopup = true;
				if (ImGui::MenuItem("Open"))
					m_showOpenScenePopup = true;
				if (ImGui::MenuItem("Save"))
					m_sceneSerialzier.Save(SceneFilePath(m_scene.GetName()));

				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}
		
		if (m_showNewScenePopup)
		{
			ImGui::OpenPopup("New Scene");
			m_showNewScenePopup = false;
		}
		if (m_showOpenScenePopup)
		{
			ImGui::OpenPopup("Open Scene");
			m_showOpenScenePopup = false;
		}
		DrawNewScenePopup();
		DrawOpenScenePopup();

		ImGui::SameLine();
		if (ImGui::Button("Edit"))
		{
			ImGui::OpenPopup("EditOpenPopup");
		}
		if (ImGui::BeginPopup("EditOpenPopup"))
		{

			ImGui::EndPopup();
		}
		ImGui::End();
	}
	void Toolbar::DrawNewScenePopup()
	{
		if (!ImGui::BeginPopupModal("New Scene", nullptr,
			ImGuiWindowFlags_AlwaysAutoResize))
			return;

		ImGui::InputText("Name", m_newSceneName, sizeof(m_newSceneName));
		if (ImGui::Button("Create"))
		{
			const std::string name = m_newSceneName;

			if (!name.empty())
			{
				m_scene.ClearEntities();
				m_scene.SetName(name);
				m_sceneSerialzier.Save(SceneFilePath(name));

				m_newSceneName[0] = '\0';
				ImGui::CloseCurrentPopup();
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
			ImGui::CloseCurrentPopup();

		ImGui::EndPopup();
	}
	void Toolbar::DrawOpenScenePopup()
	{
		if (!ImGui::BeginPopup("Open Scene"))
			return;

		std::error_code error;
		for (const auto& entry : std::filesystem::directory_iterator(ScenesDirectory, error))
		{
			if (entry.path().extension() != ".json" ||
				!entry.path().filename().string().ends_with(".scene.json"))
				continue;
			const std::string label = entry.path().stem().stem().string();

			if (ImGui::MenuItem(label.c_str()))
			{
				if (m_sceneSerialzier.Load(entry.path()))
				{
					m_scene.SetName(label);
				}
			}
		}

		ImGui::EndPopup();
	}

	void Toolbar::Update(float)
	{

	}
}

#include "toolbar.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <filesystem>

namespace eng
{
	Toolbar::Toolbar(CommandExecutor& commandExecutor, SceneSerializer& sceneSerializer)
		: m_commandExecutor{commandExecutor}, m_sceneSerialzier {sceneSerializer}
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
				const std::filesystem::path scenePath =
					std::filesystem::path{ ENGINE_ASSET_DIR } / "scenes/current.scene.json";

				if (ImGui::MenuItem("Save"))
				{
					if (!m_sceneSerialzier.Save(scenePath))
						m_logger->Error("Failed to save scene");
						
				}
				if (ImGui::MenuItem("Load"))
				{
					if (!m_sceneSerialzier.Load(scenePath))
						m_logger->Error("Failed to load scene");
				}
				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}

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
	void Toolbar::Update(float dt)
	{
	}
}
